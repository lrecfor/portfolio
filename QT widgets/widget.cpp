#include "widget.h"
#include "ui_widget.h"

#include <QFont>
#include <QLineEdit>
#include <QTimer>
#include <QPoint>

widget::widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);

    statusBar()->showMessage(tr("Ready..."));

    m_labelClicked = false;
    m_resizeLabel = false;
    m_resizeButton = false;
    l_move = false;
    b_move = false;

    m_reg1 = false;
    m_reg2 = false;
    m_reg3 = false;
    m_reg4 = false;

    m_reg5 = false;
    m_reg6 = false;
    m_reg7 = false;
    m_reg8 = false;

    reg = "none";


    lbl = new label (tr("movable resizable label"), this);
    lbl->setGeometry(400, 80, 241, 51);

    size = lbl->width() / 12;
    old_widthLabel = lbl->width();

    connect(lbl, SIGNAL(doubleClickedLabel(QMouseEvent*)), this, SLOT(labelDoubleClicked(QMouseEvent*)));
    connect(lbl, SIGNAL(clickedLabel(QMouseEvent*)), this, SLOT(labelClicked(QMouseEvent*)));

    butt = new button (tr("movable resizable button"), this);
    butt->setGeometry(400, 200, 241, 61);

    connect(butt, SIGNAL(doubleClickedButton(QMouseEvent*)), this, SLOT(buttonDoubleClicked(QMouseEvent*)));
    connect(butt, SIGNAL(clickedButton(QMouseEvent*)), this, SLOT(buttonClicked(QMouseEvent*)));
    connect(butt, SIGNAL(clickedButtonCtrl(QMouseEvent *)), this, SLOT(buttonClickedCtrl(QMouseEvent*)));

    QFont font("Arial", 16);
    ui->lLabel->setFont(font);
    ui->buttonLabel->setFont(font);
    ui->lLabel->setText("<p align='center'>400, 80");
    ui->buttonLabel->setText("<p align='center'>400, 130");
}

widget::~widget()
{
    delete ui;
}

void widget::changeText()
{
    statusBar()->showMessage(tr("Label updated..."));
    QTimer::singleShot(1500, this, [this] () { statusBar()->showMessage(tr("Ready...")); });

    edit->hide();
    edit->deleteLater();

    lbl->setAlignment(Qt::AlignCenter);
    lbl->setText(edit->text());

    m_labelClicked = false;
}

void widget::labelDoubleClicked(QMouseEvent*)
{
    statusBar()->showMessage(tr("Label clicked..."));
    QTimer::singleShot(1500, this, [this] () { statusBar()->showMessage(tr("Editing text...")); });

    textLabel = lbl->text();

    if (lbl->width() != old_widthLabel)
        size = lbl->width() / 12;
    lbl->clear();
    m_labelClicked = true;

    edit = new lineEdit (size, this);
    edit->setGeometry(lbl->geometry());
    edit->setText(textLabel);
    edit->show();

    old_widthLabel = lbl->width();

    connect(edit, &QLineEdit::editingFinished, this, &widget::changeText);
}

void widget::buttonDoubleClicked(QMouseEvent*)
{
    statusBar()->showMessage(tr("Button clicked..."));
    QTimer::singleShot(1500, this, [this] () { statusBar()->showMessage(tr("Ready...")); });
}

void widget::buttonClickedCtrl(QMouseEvent *)
{
    statusBar()->showMessage(tr("Button clicked with ctrl..."));
    QTimer::singleShot(1500, this, [this] () { statusBar()->showMessage(tr("Ready...")); });
}

void widget::labelClicked(QMouseEvent *event)
{
    m_resizeLabel = true;
    m_resizeButton = false;
    l_move = true;
    b_move = false;
    offset = event->pos();
    repaint();
}

void widget::buttonClicked(QMouseEvent *event)
{
    m_resizeButton = true;
    m_resizeLabel = false;
    b_move = true;
    l_move = false;
    offset = event->pos();
    repaint();
}

void widget::mousePressEvent(QMouseEvent *event)
{
    m_resizeLabel = false;
    m_resizeButton = false;
    repaint();

    QRegion reg1(lbl->x() - 5, lbl->y() - 5, 5, 5);
    QRegion reg2(lbl->x() + lbl->width(), lbl->y() - 5, 5, 5);
    QRegion reg3(lbl->x() - 5, lbl->y() + lbl->height(), 5, 5);
    QRegion reg4(lbl->x() + lbl->width(), lbl->y() + lbl->height(), 5, 5);

    QRegion reg5(butt->x() - 5, butt->y() - 5, 5, 5);
    QRegion reg6(butt->x() + butt->width(), butt->y() - 5, 5, 5);
    QRegion reg7(butt->x() - 5, butt->y() + butt->height(), 5, 5);
    QRegion reg8(butt->x() + butt->width(), butt->y() + butt->height(), 5, 5);

    if (reg1.contains(event->pos())
            || reg2.contains(event->pos())
            || reg3.contains(event->pos())
            || reg4.contains(event->pos()))
    {
        labelClicked(event);
        if (reg1.contains(event->pos())) { m_reg1 = true; reg = m_reg1; }
        if (reg2.contains(event->pos())) { m_reg2 = true; reg = m_reg2; }
        if (reg3.contains(event->pos())) { m_reg3 = true; reg = m_reg3; }
        if (reg4.contains(event->pos())) { m_reg4 = true; reg = m_reg4; }
    }

    if (reg5.contains(event->pos())
                || reg6.contains(event->pos())
                || reg7.contains(event->pos())
                || reg8.contains(event->pos()))
    {
        buttonClicked(event);
        if (reg5.contains(event->pos())) { m_reg5 = true; reg = m_reg5; }
        if (reg6.contains(event->pos())) { m_reg6 = true; reg = m_reg6; }
        if (reg7.contains(event->pos())) { m_reg7 = true; reg = m_reg7; }
        if (reg8.contains(event->pos())) { m_reg8 = true; reg = m_reg8; }
    }
}

void widget::mouseMoveEvent(QMouseEvent *event)
{
    labelMove(event->pos());
    buttonMove(event->pos());

    labelResize(event->pos(), reg);
    buttonResize(event->pos(), reg);
}

void widget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));

    if (event->button() == Qt::LeftButton && b_move) {
        b_move = false;
    }

    QTimer::singleShot(1500, this, [this] () { statusBar()->showMessage(tr("Ready...")); });

    reg = "none";

    m_reg1 = false;
    m_reg2 = false;
    m_reg3 = false;
    m_reg4 = false;

    m_reg5 = false;
    m_reg6 = false;
    m_reg7 = false;
    m_reg8 = false;

    l_move = false;
    b_move = false;
}

void widget::labelMove(QPoint point)
{
    statusBar()->showMessage(tr("Label moving..."));
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    QFont font("Arial", 16);
    ui->lLabel->setFont(font);

    if (reg == "none" && l_move == true)
    {
        lbl->move((point.x() - offset.x()), (point.y() - offset.y()));
        QRect geometry = lbl->geometry();
        ui->lLabel->setText(QString("<p align='center'>%1, %2").arg(geometry.x()).arg(geometry.y()));
    }

}

void widget::buttonMove(QPoint point)
{
    statusBar()->showMessage(tr("Button moving..."));
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    QFont font("Arial", 16);
    ui->buttonLabel->setFont(font);

    if (reg == "none" && b_move == true)
    {
        butt->move((point.x() - offset.x()), (point.y() - offset.y()));
        QRect geometry = butt->geometry();
        ui->buttonLabel->setText(QString("<p align='center'>%1, %2").arg(geometry.x()).arg(geometry.y()));
    }
}

void widget::labelResize(QPoint point, QString reg)
{
    statusBar()->showMessage(tr("Label resizing..."));

    if (reg != "none")
    {
        if (reg == m_reg1)
            lbl->setGeometry(point.x(), point.y(), (lbl->x() + lbl->width()) - point.x(), (lbl->y() + lbl->height()) - point.y());
        if (reg == m_reg2)
            lbl->setGeometry(lbl->x(), point.y(), point.x() - lbl->x(), (lbl->y() + lbl->height()) - point.y());
        if (reg == m_reg3)
            lbl->setGeometry(point.x(), lbl->y(), (lbl->x() + lbl->width()) - point.x(), point.y() - lbl->y());
        if (reg == m_reg4)
            lbl->setGeometry(lbl->x(), lbl->y(), point.x() - lbl->x(), point.y() - lbl->y());
    }
    update();
}

void widget::buttonResize(QPoint point, QString reg)
{
    statusBar()->showMessage(tr("Button resizing..."));

    if (reg != "none")
    {
        if (reg == m_reg5)
            butt->setGeometry(point.x(), point.y(), (butt->x() + butt->width()) - point.x(), (butt->y() + butt->height()) - point.y());
        if (reg == m_reg6)
            butt->setGeometry(butt->x(), point.y(), point.x() - butt->x(), (butt->y() + butt->height()) - point.y());
        if (reg == m_reg7)
            butt->setGeometry(point.x(), butt->y(), (butt->x() + butt->width()) - point.x(), point.y() - butt->y());
        if (reg == m_reg8)
            butt->setGeometry(butt->x(), butt->y(), point.x() - butt->x(), point.y() - butt->y());
    }
}

void widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    doPainting();
}

void widget::doPainting()
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::black));

    if (m_resizeLabel == true)
    {
        painter.drawRect(lbl->x() - 5, lbl->y() - 5, 5, 5);
        painter.drawRect(lbl->x() + lbl->width(), lbl->y() - 5, 5, 5);
        painter.drawRect(lbl->x() - 5, lbl->y() + lbl->height(), 5, 5);
        painter.drawRect(lbl->x() + lbl->width(), lbl->y() + lbl->height(), 5, 5);
    }

    if (m_resizeButton == true)
    {
        painter.drawRect(butt->x() - 5, butt->y() - 5, 5, 5);
        painter.drawRect(butt->x() + butt->width(), butt->y() - 5, 5, 5);
        painter.drawRect(butt->x() - 5, butt->y() + butt->height(), 5, 5);
        painter.drawRect(butt->x() + butt->width(), butt->y() + butt->height(), 5, 5);
    }
}
