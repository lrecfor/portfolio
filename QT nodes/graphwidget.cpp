#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>

graphWidget::graphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    setStyleSheet("background-color: blue");
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setWindowTitle(tr("Elastic Nodes"));

    node1 = new node(this);
    node2 = new node(this);
    node3 = new node(this);
    node4 = new node(this);
    node5 = new node(this);
    node6 = new node(this);
    node7 = new node(this);
    centerNode = new node(this);

    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(centerNode);

    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(node5);

    scene->addItem(node6);
    scene->addItem(node7);

    scene->addItem(new edge(node1, node2));
    scene->addItem(new edge(node1, centerNode));
    scene->addItem(new edge(node2, centerNode));

    scene->addItem(new edge(node3, centerNode));
    scene->addItem(new edge(centerNode, node3));
    scene->addItem(new edge(node4, centerNode));

    scene->addItem(new edge(node4, node6));
    scene->addItem(new edge(node3, node5));

    scene->addItem(new edge(node5, node6));
    scene->addItem(new edge(node5, node7));
    scene->addItem(new edge(node7, node6));
    scene->addItem(new edge(node3, node4));

    node1->setPos(-50, -50);
    node2->setPos(-50, 50);
    centerNode->setPos(0, 0);

    node3->setPos(100, 100);
    node4->setPos(100, -100);
    node5->setPos(150, 50);

    node6->setPos(150, -50);
    node7->setPos(200, 0);
}

void graphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void graphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void graphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (node *_node = qgraphicsitem_cast<node *>(item))
            nodes << _node;
    }

    foreach (node *_node, nodes)
        _node->calculateForces();

    bool itemsMoved = false;
    foreach (node *_node, nodes) {
        if (_node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }

    point1.setX(static_cast<int>(node1->x()));
    point1.setY(static_cast<int>(node1->y()));
    point2.setX(static_cast<int>(node2->x()));
    point2.setY(static_cast<int>(node2->y()));
    pointCentral.setX(static_cast<int>(centerNode->x()));
    pointCentral.setY(static_cast<int>(centerNode->y()));
    point3.setX(static_cast<int>(node3->x()));;
    point3.setY(static_cast<int>(node3->y()));
    point4.setX(static_cast<int>(node4->x()));;
    point4.setY(static_cast<int>(node4->y()));
    point5.setX(static_cast<int>(node5->x()));;
    point5.setY(static_cast<int>(node5->y()));
    point6.setX(static_cast<int>(node6->x()));;
    point6.setY(static_cast<int>(node6->y()));
    point7.setX(static_cast<int>(node7->x()));;
    point7.setY(static_cast<int>(node7->y()));

    emit valueChanged();
}

void graphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QPixmap pix(":/new/prefix1/background.png");
    painter->drawPixmap(-300, -300, 600, 600, pix);
}

void graphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

#if QT_CONFIG(wheelevent)
void graphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(static_cast<double>(2), -event->delta() / 240.0));
}
#endif

void graphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}


void graphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void graphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
