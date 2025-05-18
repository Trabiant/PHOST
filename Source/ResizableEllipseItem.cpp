#include "ResizableEllipseItem.h"
#include "HandleItem.h"
#include <QPen>
#include <QVariant>
#include <QGraphicsScene>

ResizableEllipseItem::ResizableEllipseItem(const QRectF& rect, QGraphicsItem* parent)
    : QGraphicsEllipseItem(rect, parent)
{
    setPen(QPen(Qt::white, 10));
    setBrush(Qt::NoBrush);
    setFlags(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setZValue(1);
    tl = new HandleItem(HandleItem::TopLeft,     this);
    tl->setParentItem(this);
    tr = new HandleItem(HandleItem::TopRight,    this);
    tr->setParentItem(this);
    bl = new HandleItem(HandleItem::BottomLeft,  this);
    bl->setParentItem(this);
    br = new HandleItem(HandleItem::BottomRight, this);
    br->setParentItem(this);
    repositionHandles();
}

QVariant ResizableEllipseItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        const QRectF bounds = scene()->sceneRect();
        const QRectF r = rect();
        qreal xMin = bounds.left()   - r.left();
        qreal xMax = bounds.right()  - r.right();
        qreal yMin = bounds.top()    - r.top();
        qreal yMax = bounds.bottom() - r.bottom();
        newPos.setX(qBound(xMin, newPos.x(), xMax));
        newPos.setY(qBound(yMin, newPos.y(), yMax));

        return newPos;
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void ResizableEllipseItem::repositionHandles() {
    m_updating = true;
    QRectF r = rect();
    tl->setPos(r.topLeft());
    tr->setPos(r.topRight());
    bl->setPos(r.bottomLeft());
    br->setPos(r.bottomRight());
    m_updating = false;
}

void ResizableEllipseItem::handleMoved(HandleItem::HandleCorner corner, const QPointF& localPos) {
    if (m_updating)
        return;
    QPointF scenePos = mapToScene(localPos);
    QRectF bounds = scene()->sceneRect();
    scenePos.setX(qBound(bounds.left(),  scenePos.x(), bounds.right()));
    scenePos.setY(qBound(bounds.top(),   scenePos.y(), bounds.bottom()));
    QPointF clampedLocal = mapFromScene(scenePos);
    QRectF r = rect();
    qreal left   = r.left();
    qreal right  = r.right();
    qreal top    = r.top();
    qreal bottom = r.bottom();
    switch (corner) {
    case HandleItem::TopLeft:
        left   = qMin(clampedLocal.x(), right  - minSize);
        top    = qMin(clampedLocal.y(), bottom - minSize);
        break;
    case HandleItem::TopRight:
        right  = qMax(clampedLocal.x(), left   + minSize);
        top    = qMin(clampedLocal.y(), bottom - minSize);
        break;
    case HandleItem::BottomLeft:
        left   = qMin(clampedLocal.x(), right  - minSize);
        bottom = qMax(clampedLocal.y(), top    + minSize);
        break;
    case HandleItem::BottomRight:
        right  = qMax(clampedLocal.x(), left   + minSize);
        bottom = qMax(clampedLocal.y(), top    + minSize);
        break;
    }
    m_updating = true;
    setRect(QRectF(QPointF(left, top), QPointF(right, bottom)));
    repositionHandles();
    m_updating = false;
}

void ResizableEllipseItem::setMirrorX(bool shouldMirror) {
    if (mirrorX != shouldMirror) {
        mirrorX = shouldMirror;
        updateTransform();
    }
}

void ResizableEllipseItem::setMirrorY(bool shouldMirror) {
    if (mirrorY != shouldMirror) {
        mirrorY = shouldMirror;
        updateTransform();
    }
}

void ResizableEllipseItem::updateTransform() {
    QTransform transform;
    if (mirrorX)
        transform.scale(-1, 1);
    if (mirrorY)
        transform.scale(1, -1);
    setTransform(transform);
}
