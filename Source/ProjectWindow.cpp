#include "ProjectWindow.h"
#include "ui_ProjectWindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <spdlog/spdlog.h>
#include "DatasetManager.h"
#include "RainbowText.h"
#include "Worker.h"

ProjectWindow::ProjectWindow(const Config& initialConfig, QWidget *parent)
    : QDialog(parent), ui(new Ui::ProjectWindow), cfg(initialConfig)
{
    ui->setupUi(this);
    new RainbowFilter(ui->text);
    ui->Name->installEventFilter(this);
    this->setFixedSize(300, 200);
    this->setWindowFlags(window()->windowFlags() | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(this, &ProjectWindow::packagesReady,
            this, &ProjectWindow::startProcessing);
}

ProjectWindow::~ProjectWindow() {
    delete ui;
}

void ProjectWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->position().y() <= 16) {
        mDragging = true;
        QPointF globalPosF = event->globalPosition();
        mDragPos = globalPosF.toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void ProjectWindow::mouseMoveEvent(QMouseEvent *event) {
    if (mDragging) {
        QPointF globalPosF = event->globalPosition();
        move(globalPosF.toPoint() - mDragPos);
        event->accept();
    }
}

void ProjectWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && mDragging) {
        mDragging = false;
        event->accept();
    }
}


bool ProjectWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->Name) {
        if (event->type() == QEvent::KeyPress) {
            auto *keyEv = static_cast<QKeyEvent*>(event);
            if (keyEv->key() == Qt::Key_Return ||
                keyEv->key() == Qt::Key_Enter) {
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void ProjectWindow::on_Cancel_clicked() {
    this->close();
}

void ProjectWindow::on_Confirm_clicked() {
    QString projectName = ui->Name->text();
    if (projectName.isEmpty()) {
        QMessageBox::critical(this, tr("PHOST"), tr("Enter correct project name."));
        return;
    }
    if (dir.isEmpty()) {
        QMessageBox::critical(this, tr("PHOST"), tr("Enter correct dataset path."));
        return;
    }
    cfg.projectName = projectName.toStdString();
    emit configLink(cfg);
    try {
        DatasetManager dm(
            std::filesystem::path(cfg.datasetPath),
            cfg.baseCount,
            cfg.psImageCount
                );
        auto packages = dm.ManageDataset();
        emit packagesReady(packages);
        accept();
        }
    catch (const std::exception &ex) {
            QString dirStr = QString::fromStdWString(
                std::filesystem::path(cfg.datasetPath).wstring()
                );
        QString msg = tr("Error: %1")
                       .arg(QString::fromUtf8(ex.what()));
        QMessageBox::critical(this, tr("PHOST"), msg);
        return;
        }
}


void ProjectWindow::on_folderPicker_clicked() {
    dir = QFileDialog::getExistingDirectory(
        this,
        QStringLiteral("Select dataset path"),
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    if (!dir.isEmpty())
        cfg.datasetPath = dir.toStdString();
}


void ProjectWindow::startProcessing(const std::vector<std::vector<ImageData>>& packages) {
    ui->Confirm->setEnabled(false);
    ui->Cancel->setEnabled(false);

    workerThread = new QThread(this);
    Worker* worker = new Worker(cv::Mat(), cfg, packages);
    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::started, worker, &Worker::process);
    connect(worker, &Worker::error, this, &ProjectWindow::handleError);
    connect(worker, &Worker::finished, this, &ProjectWindow::processingFinished);

    connect(worker, &Worker::finished, workerThread, &QThread::quit);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);
}


void ProjectWindow::handleError(const QString& what) {
    QMessageBox::warning(this, tr("PHOST Error"), what);
}

void ProjectWindow::processingFinished() {
    ui->Confirm->setEnabled(true);
    ui->Cancel->setEnabled(true);
    workerThread = nullptr;
}

void ProjectWindow::on_Close_clicked() {
    this->close();
}

