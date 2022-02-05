#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

node::node(graphWidget *graphWidget)
    : graph(graphWidget)
{
    pressed = false;
    count = 1;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void node::addEdge(edge *_edge)
{
    edgeList << _edge;
    _edge->adjust();
}

QList<edge *> node::edges() const
{
    return edgeList;
}

void node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }

    qreal xvel = 0;
    qreal yvel = 0;
    foreach (QGraphicsItem *item, scene()->items()) {
        node *_node = qgraphicsitem_cast<node *>(item);
        if (!_node)
            continue;

        QPointF vec = mapToItem(_node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 2.0 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }

    double weight = (edgeList.size() + 1) * 10;
    foreach (edge *edge, edgeList) {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

bool node::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    if (pressed)
        painter->setBrush(QBrush(Qt::white));
    else if (count == 1)
        painter->setBrush(QBrush(Qt::yellow));

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (edge *_edge, edgeList)
            _edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
