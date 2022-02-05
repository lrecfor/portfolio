#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QtWidgets>
#include <QResizeEvent>

#include "button.h"
#include "label.h"
#include "lineedit.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

public slots:
    void changeText();

private slots:
    void labelDoubleClicked(QMouseEvent*);
    void buttonDoubleClicked(QMouseEvent*);

    void labelClicked(QMouseEvent *event);
    void buttonClicked(QMouseEvent *event);

    void buttonClickedCtrl(QMouseEvent *);

    void labelMove(QPoint point);
    void buttonMove(QPoint point);

    void labelResize(QPoint point, QString reg);
    void buttonResize(QPoint point, QString reg);

protected:
    void paintEvent(QPaintEvent *event);
    void doPainting();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::widget *ui;

    label *lbl;
    button *butt;
    lineEdit *edit;

    bool m_labelClicked;
    bool m_resizeLabel;
    bool m_resizeButton;

    QString textLabel;
    QString reg;

    bool m_reg1;
    bool m_reg2;
    bool m_reg3;
    bool m_reg4;

    bool m_reg5;
    bool m_reg6;
    bool m_reg7;
    bool m_reg8;

    QPoint offset;
    bool l_move;
    bool b_move;

    int size;
    int old_widthLabel;
};

#endif // WIDGET_H
