#pragma once
#include <QGraphicsView>
#include "ResizableEllipseItem.h"
#include <opencv2/opencv.hpp>

class ResizableEllipseItem;
class QGraphicsPixmapItem;
class QGraphicsScene;
class QResizeEvent;
class MaskEditorView : public QGraphicsView {
    Q_OBJECT
public:
    explicit MaskEditorView(QWidget* parent=nullptr);
    void setBackground(const QImage& img);
    void toggleMaskVisible();
    cv::Mat exportMaskMat() const;
    void clear();

protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent (QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* backgroundItem;
    ResizableEllipseItem* maskItem;
    enum class DragMode { None, MoveMask, ResizeTL, ResizeTR, ResizeBL, ResizeBR } dragMode;
    QPointF dragStartScenePos;
};
