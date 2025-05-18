#include "MaskEditorView.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <opencv2/imgproc.hpp>
#include "ResizableEllipseItem.h"
#include <QGraphicsView>

MaskEditorView::MaskEditorView(QWidget* p)
    : QGraphicsView(p), scene(new QGraphicsScene(this)), backgroundItem(nullptr),
    maskItem(nullptr), dragMode(DragMode::None)
{
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::Antialiasing);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignCenter);
}

// Подгрузка изображения в редактор маски
void MaskEditorView::setBackground(const QImage& img) {
    scene->clear();
    backgroundItem = scene->addPixmap(QPixmap::fromImage(img));
    backgroundItem->setZValue(0);
    QRectF imgRect = backgroundItem->boundingRect();
    scene->setSceneRect(imgRect);
    setScene(scene);
    maskItem = nullptr;
    resetTransform();
    fitInView(backgroundItem, Qt::KeepAspectRatio);
}

// Очистка редактора маски
void MaskEditorView::clear() {
    scene->clear();
    backgroundItem = nullptr;
    maskItem = nullptr;
    resetTransform();
}

void MaskEditorView::resizeEvent(QResizeEvent* ev) {
    QGraphicsView::resizeEvent(ev);
    if (backgroundItem) {
        resetTransform();
        fitInView(backgroundItem, Qt::KeepAspectRatio);
    }
}

void MaskEditorView::toggleMaskVisible() {
    if (!backgroundItem)
        return;
    if (!maskItem) {
        QRectF imgRect = backgroundItem->boundingRect();
        qreal r = 40.0;
        maskItem = new ResizableEllipseItem(QRectF(-r, -r, 2*r, 2*r));
        maskItem->setFlag(QGraphicsItem::ItemIsMovable);
        maskItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        maskItem->setImageRect(imgRect);
        maskItem->setPos(imgRect.center());
        maskItem->setZValue(1);
        scene->addItem(maskItem);
        maskItem->show();
        return;
    }
    if (maskItem->isVisible()) {
        maskItem->hide();
        return;
    }
    else {
        maskItem->show();
        QRectF imgRect = backgroundItem->boundingRect();
        maskItem->setImageRect(imgRect);
        maskItem->repositionHandles();
        maskItem->setZValue(1);
    }
    {
        const QRectF imgRect = backgroundItem->boundingRect();
        QRectF ellipseLocal = maskItem->boundingRect();
        QPointF center = maskItem->pos();
        bool needMirrorX = (center.x() + ellipseLocal.width()  / 2.0 > imgRect.width());
        bool needMirrorY = (center.y() + ellipseLocal.height() / 2.0 > imgRect.height());
        maskItem->setMirrorX(needMirrorX);
        maskItem->setMirrorY(needMirrorY);
    }
}

// Сохранение маски
cv::Mat MaskEditorView::exportMaskMat() const {
    if (!backgroundItem || !maskItem || !maskItem->isVisible())
        return cv::Mat();

    QRectF imgRect = backgroundItem->boundingRect();
    QImage maskImg(imgRect.size().toSize(), QImage::Format_Grayscale8);
    maskImg.fill(0);

    QPainter p(&maskImg);
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    QRectF ellipseScene = maskItem->sceneBoundingRect();
    p.drawEllipse(ellipseScene.translated(-imgRect.topLeft()));
    p.end();

    cv::Mat mat(maskImg.height(), maskImg.width(), CV_8UC1,
                const_cast<uchar*>(maskImg.bits()),
                static_cast<size_t>(maskImg.bytesPerLine()));
    return mat.clone();
}

void MaskEditorView::mousePressEvent(QMouseEvent* ev) {
    QGraphicsView::mousePressEvent(ev);

}
void MaskEditorView::mouseMoveEvent(QMouseEvent* ev) {
    QGraphicsView::mouseMoveEvent(ev);
}
void MaskEditorView::mouseReleaseEvent(QMouseEvent* ev) {
    QGraphicsView::mouseReleaseEvent(ev);
}
