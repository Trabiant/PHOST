#pragma once
#include "Worker.h"
#include "Config.h"
#include "ImageData.h"
#include "MaskEditorView.h"
#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QMainWindow>
#include <QQuickWidget>
#include <QCloseEvent>
#include <QTimer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSystemTrayIcon>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    Window(Ui::Window *ui, MaskEditorView *maskView, Config currentConfig,
           QString rcDir, QPoint mDragPos,
           std::vector<std::vector<ImageData>> packages, cv::Mat mask,
           bool rcSelected, bool maskSaved)
        : ui(ui), maskView(maskView), currentConfig(std::move(currentConfig)),
        rcDir(std::move(rcDir)), mDragPos(mDragPos),
        packages(std::move(packages)), mask(std::move(mask)),
        rcSelected(rcSelected), maskSaved(maskSaved) {}
    ~Window();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_Start_clicked();
    void on_Close_clicked();
    void on_creatProject_clicked();
    void onProjectConfigLink(const Config& cfg);
    void on_rcLink_clicked();
    void on_four_clicked();
    void on_eight_clicked();
    void on_twelve_clicked();
    void on_sixteen_clicked();
    void on_DirectX_clicked();
    void on_OpenGL_clicked();
    void on_Hide_clicked();
    void onPackageSelected(QListWidgetItem* item);
    void onThumbnailClicked(QListWidgetItem* thumbItem);
    void on_Workflow_clicked();
    void on_Editor_clicked();

private:
    Ui::Window *ui;
    MaskEditorView* maskView;
    Config currentConfig;
    QString rcDir;
    bool mDragging = false;
    QPoint mDragPos;
    std::vector<std::vector<ImageData>> packages;
    void populatePackageList(const std::vector<std::vector<ImageData>>& packages);
    cv::Mat mask;
    bool rcSelected;
    bool maskSaved;
    void updateStartEnabled();
    bool maskEditorActive = false;
    QThread* m_thread = nullptr;
    Worker* m_worker = nullptr;
    bool m_workerRunning = false;
    QRect m_startRect;
    QRect m_endRect;
    QSystemTrayIcon *trayIcon = nullptr;
};
