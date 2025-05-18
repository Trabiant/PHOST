#pragma once
#include <QGraphicsEllipseItem>
#include <QTransform>
#include "HandleItem.h"

class ResizableEllipseItem : public QGraphicsEllipseItem {
public:
    explicit ResizableEllipseItem(const QRectF& rect, QGraphicsItem* parent = nullptr);
    void handleMoved(HandleItem::HandleCorner corner, const QPointF& localPos);
    bool isUpdating() const { return m_updating; }
    void setImageRect(const QRectF& imgRect) { m_imageRect = imgRect; }
    void repositionHandles();
    void setMirrorX(bool shouldMirror);
    void setMirrorY(bool shouldMirror);
    static constexpr qreal minSize = 5.0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    HandleItem* tl;
    HandleItem* tr;
    HandleItem* bl;
    HandleItem* br;
    bool m_updating = false;
    QRectF m_imageRect;
    bool mirrorX = false;
    bool mirrorY = false;
    void updateTransform();
};
