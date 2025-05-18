#pragma once
#include <QWidget>
#include <QDialog>
#include "Config.h"
#include <QThread>
#include <QMouseEvent>
#include "ImageData.h"

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QDialog {
    Q_OBJECT

signals:
    void configLink(const Config& cfg);
    void packagesReady(const std::vector<std::vector<ImageData>>& packages);

public:
    explicit ProjectWindow(const Config& initialConfig, QWidget *parent = nullptr);
    ~ProjectWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_Cancel_clicked();
    void on_Confirm_clicked();
    void on_folderPicker_clicked();
    void startProcessing(const std::vector<std::vector<ImageData>>& packages);
    void handleError(const QString& what);
    void processingFinished();
    void on_Close_clicked();

private:
    Ui::ProjectWindow *ui;
    QString dir;
    Config cfg;
    QThread* workerThread = nullptr;
    bool mDragging = false;
    QPoint mDragPos;
};
