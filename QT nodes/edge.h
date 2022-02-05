#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class node;

class edge : public QGraphicsItem
{
public:
    edge(node *sourceNode, node *destNode);

    node *sourceNode() const;
    node *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // EDGE_H
