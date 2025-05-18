#include "Window.h"
#include "Worker.h"
#include "ProjectWindow.h"
#include "Config.h"
#include "SlidingIndicatorWidget.h"
#include "ui_Window.h"
#include <spdlog/spdlog.h>
#include <opencv2/imgproc.hpp>
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>
#include <QQmlContext>
#include <QQmlEngine>
#include <QStandardPaths>
#include <QQuickItem>
#include <QLibraryInfo>
#include <QFile>
#include <QDebug>
#include <QQuickWidget>
#include <QQmlError>
#include <QCloseEvent>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QSystemTrayIcon>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPalette>


Window::Window(QWidget *parent)
    : QWidget(parent), ui(new Ui::Window), maskView(nullptr),
    maskSaved(false), rcSelected(false), maskEditorActive(false)

{
    // Подготовка окна программы
    ui->setupUi(this);
    ui->saveMask->setEnabled(false);
    ui->drawMask->setEnabled(false);
    ui->drawMask->setVisible(false);
    ui->saveMask->setVisible(false);
    SlidingIndicatorWidget *slider = new SlidingIndicatorWidget({ui->Workflow, ui->Editor}, this);
    slider->setGeometry(this->rect());
    slider->show();
    this->setWindowFlags(window()->windowFlags() | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->thumbList->setStyleSheet(R"(
    QScrollBar:vertical {
        background: #1b1b1b;
        width: 4px;
        margin: 4px 0 4px 0;
        border-radius: 1px;
    }
    QScrollBar::handle:vertical {
        background: qlineargradient(
            x1:0, y1:0, x2:0, y2:1,
            stop:0 #8C8C8C,
            stop:1 #262626
        );
        min-height: 20px;
        width: 4px;
        border-radius: 1px;
    }
    QScrollBar::handle:vertical:hover {
        background: qlineargradient(
            x1:0, y1:0, x2:0, y2:1,
            stop:0 #b3b3b3,
            stop:1 #262626
        );
    }
    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        height: 0;
    }
    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none;
    QListView::item { background: transparent; }
    }
    QListView::item:selected {
        background: transparent;
        border: 1px solid white;
        border-radius: 2px;
    }
)");
    // Подхватывание пути движка фотограмметрии
    const QString defaultRc =
        QStringLiteral("C:/Program Files/Capturing Reality/RealityCapture/RealityCapture.exe");
    QFileInfo rcInfo(defaultRc);
    if (rcInfo.exists() && rcInfo.isFile()) {
        currentConfig.rcPath = defaultRc.toStdString();
        rcSelected = true;
        ui->frameRcStatus->setStyleSheet(
            "border:0px; border-radius:3px; background-color: #3870A5;"
            );
        updateStartEnabled();
    }
    ui->progressBar->hide();
    ui->Start->setEnabled(false);
    connect(ui->Workflow, &QPushButton::clicked,
            this, &Window::on_Workflow_clicked);
    connect(ui->Editor, &QPushButton::clicked,
            this, &Window::on_Editor_clicked);

    ui->stackedWidget->setCurrentIndex(0);
    ui->Workflow->setEnabled(false);
    ui->Editor->setEnabled(true);

    QWidget* editorPage = ui->stackedWidget->widget(1);
    if (!editorPage->layout()) {
        auto* vlay = new QVBoxLayout(editorPage);
        vlay->setContentsMargins(0,0,0,0);
        editorPage->setLayout(vlay);
    }
    connect(ui->listPackages,
            &QListWidget::itemClicked,
            this,
            &Window::onPackageSelected);
    maskView = new MaskEditorView(this);
    editorPage->layout()->addWidget(maskView);
    connect(ui->drawMask, &QPushButton::clicked, this, [&](){
        maskView->toggleMaskVisible();
        maskEditorActive = !maskEditorActive;
        ui->saveMask->setEnabled(maskEditorActive);
    });
    connect(ui->saveMask, &QPushButton::clicked, this, [&](){
        mask = maskView->exportMaskMat();
        maskSaved = true;
        updateStartEnabled();
    });
    connect(ui->thumbList, &QListWidget::itemClicked, this, [&](QListWidgetItem* it){
        int idx = it->data(Qt::UserRole).toInt();
        int pkgIdx = ui->listPackages->currentRow();
        if (pkgIdx<0||pkgIdx>=packages.size()) return;
        const auto& mat = packages[pkgIdx][idx].image;
        cv::Mat rgb; cv::cvtColor(mat,rgb,cv::COLOR_BGR2RGB);
        QImage img(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
        maskView->setBackground(img);
        ui->drawMask->setEnabled(true);
    });

    this->setFixedSize(981, 654);
    setWindowFlags(Qt::FramelessWindowHint);
    QRect screenGeo = QGuiApplication::primaryScreen()->geometry();
    int w = width(), h = height();
    m_endRect = QRect(
        (screenGeo.width() - w) / 2,
        (screenGeo.height() - h) / 2,
        w, h
        );
    connect(ui->Hide,  &QPushButton::clicked, this, &Window::on_Hide_clicked);
    connect(ui->Close, &QPushButton::clicked, this, &Window::on_Close_clicked);
}

Window::~Window() {
    delete ui;
}

void Window::updateStartEnabled() {
    ui->Start->setEnabled(rcSelected == true && maskSaved == true);
}

// Запуск обработки датасета
void Window::on_Start_clicked() {
    ui->Start->setEnabled(false);
    ui->creatProject->setEnabled(false);
    ui->rcLink->setEnabled(false);
    ui->four->setEnabled(false);
    ui->eight->setEnabled(false);
    ui->twelve->setEnabled(false);
    ui->sixteen->setEnabled(false);
    ui->DirectX->setEnabled(false);
    ui->OpenGL->setEnabled(false);
    ui->drawMask->setEnabled(false);
    ui->saveMask->setEnabled(false);

    m_thread = new QThread(this);
    m_worker = new Worker(mask, currentConfig, packages);
    m_worker->moveToThread(m_thread);

    connect(m_thread, &QThread::started, m_worker, &Worker::process);

    connect(m_worker, &Worker::statusUpdate, ui->statusText, &QLabel::setText);
    connect(m_worker, &Worker::estimationUpdate, ui->estimationText, &QLabel::setText);
    connect(m_worker, &Worker::progressBarShow,    ui->progressBar, &QProgressBar::show);
    connect(m_worker, &Worker::progressBarUpdate,  ui->progressBar, &QProgressBar::setValue);
    connect(m_worker, &Worker::progressBarHide,    ui->progressBar, &QProgressBar::hide);

    connect(m_worker, &Worker::error, this, [=](const QString &msg){
        QMessageBox::critical(this, tr("PHOST"), msg);

    });

    connect(m_worker, &Worker::finished, this, [this](){
        ui->statusText->clear();
        ui->estimationText->clear();
        ui->Start->setEnabled(true);
        ui->creatProject->setEnabled(true);
        ui->rcLink->setEnabled(true);
        ui->four->setEnabled(true);
        ui->eight->setEnabled(true);
        ui->twelve->setEnabled(true);
        ui->sixteen->setEnabled(true);
        ui->DirectX->setEnabled(true);
        ui->OpenGL->setEnabled(true);
        ui->drawMask->setEnabled(true);
        ui->saveMask->setEnabled(true);
        maskSaved = false;
        m_workerRunning = false;

        m_thread->quit();
    });

    connect(m_worker, &Worker::finished, m_worker, &QObject::deleteLater);
    connect(m_thread, &QThread::finished, m_thread, &QObject::deleteLater);

    m_workerRunning = true;
    m_thread->start();
}

// Вывод датасета в виде списка пакетов
void Window::populatePackageList(
    const std::vector<std::vector<ImageData>>& packages) {
    ui->listPackages->clear();
    ui->listPackages->setStyleSheet(R"(
    QListWidget {
        border: none;
        background: transparent;
        outline: none;
    }
    QListWidget::item:selected {
        background: transparent;
    }
    QListWidget::item:selected QWidget#pkgItem {
        background-color: #808080;
    }
    QScrollBar:vertical {
        background: #1b1b1b;
        width: 4px;
        margin: 4px 0 4px 0;
        border-radius: 1px;
    }
    QScrollBar::handle:vertical {
        background: qlineargradient(
            x1:0, y1:0, x2:0, y2:1,
            stop:0 #8C8C8C,
            stop:1 #262626
        );
        min-height: 20px;
        width: 4px;
        border-radius: 1px;
    }
    QScrollBar::handle:vertical:hover {
        background: qlineargradient(
            x1:0, y1:0, x2:0, y2:1,
            stop:0 #b3b3b3,
            stop:1 #262626
        );
    }
    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        height: 0;
    }
    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none;
    }
)");

    for (int i = 0; i < packages.size(); ++i) {
        const auto& pack = packages[i];
        if (pack.empty()) continue;

        QWidget* itemWidget = new QWidget;
        itemWidget->setObjectName("pkgItem");
        itemWidget->setStyleSheet(R"(
            QWidget#pkgItem {
                background-color: #262626;
                border-radius: 4px;
                padding: 8px;
                margin: 2px 0;
            }
            QWidget#pkgItem:hover {
                background: qlineargradient(
                    x1:0, y1:0, x2:1, y2:0,
                    stop:0 #262626,
                    stop:1 #8C8C8C
                );
                border: none;
            }
            QLabel#pkgTitle {
                color: #FFFFFF;
                font-family: "Inter";
                font-size: 12px;
                font-weight: bold;
                background-color: transparent;
            }
            QLabel#pkgCount {
                color: #BBBBBB;
                font-family: "Inter";
                font-size: 8px;
                font-weight: light;
                background-color: transparent;
                margin-top: -12px;
            }
            QLabel#pkgIndex {
                color: #555555;
                font-family: "Inter";
                font-size: 22px;
                font-weight: bold;
                background-color: transparent;
            }
        )");

        QHBoxLayout* hlay = new QHBoxLayout(itemWidget);
        hlay->setContentsMargins(8, 8, 8, 8);
        hlay->setSpacing(12);

        QLabel* thumb = new QLabel;
        thumb->setFixedSize(50, 39);
        thumb->setObjectName("pkgThumb");
        thumb->setStyleSheet(R"(
            QLabel#pkgThumb {
                border: none;
                border-radius: 2px;
            }
        )");
        cv::Mat rgb;
        cv::cvtColor(pack[0].image, rgb, cv::COLOR_BGR2RGB);
        QImage qim(rgb.data, rgb.cols, rgb.rows,
                   static_cast<int>(rgb.step), QImage::Format_RGB888);
        QPixmap pix = QPixmap::fromImage(qim).scaled(
            thumb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        thumb->setPixmap(pix);
        hlay->addWidget(thumb);
        QVBoxLayout* vlay = new QVBoxLayout;
        vlay->setContentsMargins(0, 0, 0, 0);
        vlay->setSpacing(0);
        QString baseName = QFileInfo(
                               QString::fromStdString(pack[0].filename)
                               ).completeBaseName();
        QLabel* title = new QLabel(QString("Package %1").arg(baseName));
        title->setObjectName("pkgTitle");
        vlay->addWidget(title);
        QLabel* count = new QLabel(QString("%1 Images").arg(pack.size()));
        count->setObjectName("pkgCount");
        vlay->addWidget(count);
        hlay->addLayout(vlay, 1);

        QLabel* index = new QLabel(QString("%1")
                                       .arg(i+1, 2, 10, QChar('0')));
        index->setObjectName("pkgIndex");
        index->setAlignment(Qt::AlignCenter);
        hlay->addWidget(index);

        QListWidgetItem* item = new QListWidgetItem(ui->listPackages);
        item->setSizeHint(itemWidget->sizeHint());
        ui->listPackages->setItemWidget(item, itemWidget);
    }
}

// Вывод снимков при нажатии на пакет
void Window::onPackageSelected(QListWidgetItem* item) {
    int row = ui->listPackages->row(item);
    if (row < 0 || row >= packages.size())
        return;
    const auto& pack = packages[row];

    ui->thumbList->clear();
    ui->thumbList->setViewMode(QListView::IconMode);
    ui->thumbList->setFlow(QListView::LeftToRight);
    ui->thumbList->setWrapping(true);
    ui->thumbList->setResizeMode(QListView::Adjust);
    ui->thumbList->setUniformItemSizes(true);
    ui->thumbList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->thumbList->setFocusPolicy(Qt::NoFocus);
    ui->thumbList->setContentsMargins(0, 0, 0, 0);

    const int spacing = 2;
    ui->thumbList->setSpacing(spacing);

    ui->thumbList->setWordWrap(true);
    ui->thumbList->setTextElideMode(Qt::ElideNone);
    ui->thumbList->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < pack.size(); ++i) {
        const auto& imgData = pack[i];

        cv::Mat rgb;
        cv::cvtColor(imgData.image, rgb, cv::COLOR_BGR2RGB);
        QImage qim(rgb.data, rgb.cols, rgb.rows, int(rgb.step), QImage::Format_RGB888);
        QPixmap pix = QPixmap::fromImage(qim);

        const int targetW = 117;
        const int targetH = (117LL * rgb.rows) / rgb.cols;
        QPixmap thumb = pix.scaled(targetW, targetH,
                                   Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);

        QPixmap rounded(thumb.size());
        rounded.fill(Qt::transparent);
        {
            QPainter p(&rounded);
            p.setRenderHint(QPainter::Antialiasing);
            QPainterPath path;
            const int radius = 2;
            path.addRoundedRect(rounded.rect(), radius, radius);
            p.setClipPath(path);
            p.drawPixmap(0, 0, thumb);

            QString name = QFileInfo(QString::fromStdString(imgData.filename)).fileName();

            QFont font("Inter", 7, QFont::ExtraBold);
            p.setFont(font);
            QFontMetrics fm(font);

            int textH = fm.height() + 4;
            int textMargin = 4;

            QRect textRect(
                textMargin,
                rounded.height() - textH - textMargin,
                rounded.width() - 2*textMargin,
                textH);

            p.setClipping(false);

            p.setPen(Qt::white);
            p.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, name);
        }

        if (i == 0) {
            ui->thumbList->setIconSize(rounded.size());

            int cellW = rounded.width()  + spacing * 2;
            int cellH = rounded.height() + spacing * 2;
            ui->thumbList->setGridSize(QSize(cellW, cellH));

            ui->mainView->setPixmap(pix.scaled(
                ui->mainView->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
        }

        QListWidgetItem* listItem = new QListWidgetItem;
        listItem->setIcon(QIcon(rounded));
        listItem->setData(Qt::UserRole, i);
        listItem->setText(QString());
        ui->thumbList->addItem(listItem);
    }

    connect(ui->thumbList,
            &QListWidget::itemClicked,
            this,
            &Window::onThumbnailClicked,
            Qt::UniqueConnection);
}





void Window::onThumbnailClicked(QListWidgetItem* thumbItem) {
    int idx = thumbItem->data(Qt::UserRole).toInt();
    int pkgIndex = ui->listPackages->currentRow();
    if (pkgIndex < 0 || pkgIndex >= packages.size()) return;
    const auto& mat = packages[pkgIndex][idx].image;

    cv::Mat rgb;
    cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
    QImage qim(
        rgb.data, rgb.cols, rgb.rows,
        static_cast<int>(rgb.step),
        QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(qim);
    ui->mainView->setPixmap(
        pix.scaled(ui->mainView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void Window::on_Close_clicked() {
    this->close();
}


void Window::on_creatProject_clicked() {
    ProjectWindow *pW = new ProjectWindow(currentConfig, this);
    connect(pW, &ProjectWindow::configLink,
            this, &Window::onProjectConfigLink);
    connect(pW, &ProjectWindow::packagesReady, this, [&](auto pkgs){
        this->packages = pkgs;
        populatePackageList(this->packages);
        ui->thumbList->clear();
        ui->mainView->clear();
        maskView->clear();
        maskSaved        = false;
        maskEditorActive = false;
        ui->drawMask->setEnabled(false);
        ui->saveMask->setEnabled(false);
        updateStartEnabled();
    });
    pW->setModal(true);
    pW->exec();
}

void Window::onProjectConfigLink(const Config& cfg) {
    this->currentConfig = cfg;
}


void Window::on_rcLink_clicked() {
    rcDir = QFileDialog::getOpenFileName(this, QStringLiteral("Select RealityCapture.exe file"), QDir::homePath(), QStringLiteral("Executables (*.exe)"));
    if (rcDir.isEmpty())
        return;
    QFileInfo info(rcDir);
    qDebug() << info.fileName();
    if (info.fileName() != QStringLiteral("RealityCapture.exe")) {
        QMessageBox::critical(this, QStringLiteral("Invalid File"), QStringLiteral("Please select the RealityCapture executable."));
        return;
    }
    else{
        currentConfig.rcPath = rcDir.toStdString();
        ui->frameRcStatus->setStyleSheet(
            "border: 0px; background-color: #3870A5; border-radius: 3px;"
            );
        rcSelected = true;
        updateStartEnabled();
    }
    spdlog::info(currentConfig.rcPath.string());
}


void Window::on_four_clicked() {
    currentConfig.psImageCount = 4;
    ui->eight->setEnabled(true);
    ui->twelve->setEnabled(true);
    ui->sixteen->setEnabled(true);
    ui->eight->setChecked(false);
    ui->twelve->setChecked(false);
    ui->sixteen->setChecked(false);
    if(ui->four->isChecked()){
        ui->four->setEnabled(false);
    }
    spdlog::info(currentConfig.psImageCount);
}


void Window::on_eight_clicked() {
    currentConfig.psImageCount = 8;
    ui->four->setEnabled(true);
    ui->twelve->setEnabled(true);
    ui->sixteen->setEnabled(true);
    ui->four->setChecked(false);
    ui->twelve->setChecked(false);
    ui->sixteen->setChecked(false);
    if(ui->eight->isChecked()){
        ui->eight->setEnabled(false);
    }
    spdlog::info(currentConfig.psImageCount);
}


void Window::on_twelve_clicked() {
    currentConfig.psImageCount = 12;
    ui->four->setEnabled(true);
    ui->eight->setEnabled(true);
    ui->sixteen->setEnabled(true);
    ui->four->setChecked(false);
    ui->eight->setChecked(false);
    ui->sixteen->setChecked(false);
    if(ui->twelve->isChecked()){
        ui->twelve->setEnabled(false);
    }
    spdlog::info(currentConfig.psImageCount);
}


void Window::on_sixteen_clicked() {
    currentConfig.psImageCount = 16;
    ui->four->setEnabled(true);
    ui->twelve->setEnabled(true);
    ui->eight->setEnabled(true);
    ui->four->setChecked(false);
    ui->twelve->setChecked(false);
    ui->eight->setChecked(false);
    if(ui->sixteen->isChecked()){
        ui->sixteen->setEnabled(false);
    }
    spdlog::info(currentConfig.psImageCount);
}


void Window::on_DirectX_clicked() {
    currentConfig.useDirectX_NormalMap = true;
    ui->OpenGL->setEnabled(true);
    ui->OpenGL->setChecked(false);
    if(ui->DirectX->isChecked()){
        ui->DirectX->setEnabled(false);
    }
    spdlog::info(currentConfig.useDirectX_NormalMap);
}


void Window::on_OpenGL_clicked() {
    currentConfig.useDirectX_NormalMap = false;
    ui->DirectX->setEnabled(true);
    ui->DirectX->setChecked(false);
    if(ui->OpenGL->isChecked()){
        ui->OpenGL->setEnabled(false);
    }
    spdlog::info(currentConfig.useDirectX_NormalMap);
}

void Window::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->position().y() <= 16) {
        mDragging = true;
        QPointF globalPosF = event->globalPosition();
        mDragPos = globalPosF.toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void Window::mouseMoveEvent(QMouseEvent *event) {
    if (mDragging) {
        QPointF globalPosF = event->globalPosition();
        move(globalPosF.toPoint() - mDragPos);
        event->accept();
    }
}

void Window::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && mDragging) {
        mDragging = false;
        event->accept();
    }
}


void Window::on_Hide_clicked() {
    this->showMinimized();
}


void Window::on_Workflow_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->Workflow->setEnabled(false);
    ui->Editor->setEnabled(true);
    ui->drawMask->setVisible(false);
    ui->saveMask->setVisible(false);
}


void Window::on_Editor_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->Workflow->setEnabled(true);
    ui->Editor->setEnabled(false);
    ui->drawMask->setVisible(true);
    ui->saveMask->setVisible(true);
}

