#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

buttons::buttons(QWidget *parent):QMainWindow(parent)
{
    state_b2=false;
    QPushButton *b1= new QPushButton("&change", this);
    QPushButton *b2= new QPushButton("&brush color", this);

    b1->setGeometry(650,200,100,80);
    b2->setGeometry(650,300,100,80);

    connect(b1, &QPushButton::clicked, this, &buttons::change);
    connect(b2, &QPushButton::clicked, this, &buttons::changeBrush);
}

void buttons::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setBrush(QBrush (QColor(a, b, c)));
    painter.setPen(QPen (Qt::black, 1.0));
    painter.setRenderHint(QPainter::Antialiasing);

    if (state_b2==1){
        a=qrand() % 256;
        b=qrand() % 256;
        c=qrand() % 256;
        painter.setBrush(QBrush(QColor(a, b, c)));
    }

    int h = height();
    int w = width();

    painter.translate(QPoint(w/3, h/2));

    for (qreal rot=0; rot < 360.0; rot+=5.0 ) {
         painter.drawEllipse(-125, -40, 250, 80);
         painter.rotate(size);
    }
}

void buttons::change()
{
    size=qrand()%(((25)-5)+5);
    repaint();
}

void buttons::changeBrush()
{
    state_b2=1;
    repaint();
    state_b2=0;
}
