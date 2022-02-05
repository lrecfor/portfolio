#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("goldenFish");

    widget = new graphWidget;
    ui->graphicSceneLayout->addWidget(widget);

    setFixedSize(429, 652);

    connect(widget, SIGNAL(valueChanged()), this, SLOT(setValue()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValue()
{
    ui->firstCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point1.x()).arg(widget->point1.y()));
    ui->secondCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point2.x()).arg(widget->point2.y()));
    ui->thirdCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->pointCentral.x()).arg(widget->pointCentral.y()));
    ui->forthCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point3.x()).arg(widget->point3.y()));
    ui->fifthCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point4.x()).arg(widget->point4.y()));
    ui->sixthCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point5.x()).arg(widget->point5.y()));
    ui->seventhCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point6.x()).arg(widget->point6.y()));
    ui->eigthCoordLabel->setText(QString("<p align='center'>%1, %2").arg(widget->point7.x()).arg(widget->point7.y()));
}
