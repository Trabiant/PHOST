#pragma once
#include <QGraphicsRectItem>

class ResizableEllipseItem;

class HandleItem : public QGraphicsRectItem {
public:
    enum HandleCorner { TopLeft, TopRight, BottomLeft, BottomRight };
    HandleItem(HandleCorner corner, ResizableEllipseItem* parent);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    HandleCorner corner;
    ResizableEllipseItem* ellipse;
};
