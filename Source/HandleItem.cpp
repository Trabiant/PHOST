#include "HandleItem.h"
#include "ResizableEllipseItem.h"
#include "QBrush"
#include <QVariant>
#include <qgraphicsscene.h>

HandleItem::HandleItem(HandleCorner c, ResizableEllipseItem* e)
    : QGraphicsRectItem(-4, -4, 8, 8), corner(c), ellipse(e) {
    setBrush(Qt::white);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIgnoresTransformations);
    setZValue(2);
}

QVariant HandleItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && ellipse && !ellipse->isUpdating()) {
        QPointF newLocal = value.toPointF();
        QRectF imgLocalRect = ellipse->mapRectFromScene(ellipse->scene()->sceneRect());
        QRectF r = ellipse->rect();
        qreal minSize = ResizableEllipseItem::minSize;
        qreal left   = r.left(),   right  = r.right();
        qreal top    = r.top(),    bottom = r.bottom();
        switch (corner) {
        case HandleItem::TopLeft:
            newLocal.setX(qBound(imgLocalRect.left(),  newLocal.x(), right  - minSize));
            newLocal.setY(qBound(imgLocalRect.top(),   newLocal.y(), bottom - minSize));
            break;
        case HandleItem::TopRight:
            newLocal.setX(qBound(left + minSize,       newLocal.x(), imgLocalRect.right()));
            newLocal.setY(qBound(imgLocalRect.top(),   newLocal.y(), bottom - minSize));
            break;
        case HandleItem::BottomLeft:
            newLocal.setX(qBound(imgLocalRect.left(),  newLocal.x(), right  - minSize));
            newLocal.setY(qBound(top + minSize,        newLocal.y(), imgLocalRect.bottom()));
            break;
        case HandleItem::BottomRight:
            newLocal.setX(qBound(left + minSize,       newLocal.x(), imgLocalRect.right()));
            newLocal.setY(qBound(top + minSize,        newLocal.y(), imgLocalRect.bottom()));
            break;
        }
        ellipse->handleMoved(corner, newLocal);
        return QVariant::fromValue(newLocal);
    }
    return QGraphicsRectItem::itemChange(change, value);
}
