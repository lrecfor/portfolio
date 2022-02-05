#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class edge;
class graphWidget;
class QGraphicsSceneMouseEvent;

class node : public QGraphicsItem
{
public:
    node(graphWidget *graphWidget);

    void addEdge(edge *edge);
    QList<edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool pressed;

    int count;

    QList<edge *> edgeList;
    QPointF newPos;
    graphWidget *graph;
};
#endif // NODE_H
