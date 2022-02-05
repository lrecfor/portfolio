#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class node;

class graphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    graphWidget(QWidget *parent = nullptr);

    void itemMoved();
    void setValue (QPoint p);

    QPoint point1;
    QPoint point2;
    QPoint pointCentral;
    QPoint point3;
    QPoint point4;
    QPoint point5;
    QPoint point6;
    QPoint point7;

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

signals:
    void valueChanged();

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event);
#endif
    void drawBackground(QPainter *painter, const QRectF &rect);
    void scaleView(qreal scaleFactor);

private:

    node *node1;
    node *node2;
    node *node3;
    node *node4;
    node *node5;
    node *node6;
    node *node7;

    int timerId;
    node *centerNode;
};

#endif // GRAPHWIDGET_H
