#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QBrush>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
private:
    Ui::MainWindow *ui;
};

class buttons : public QMainWindow
{
    Q_OBJECT
public:
    buttons(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent * event);
private:
    void change();
    void changeBrush();
    int size=20;
    int a=qrand() % 256, b=qrand() % 256, c=qrand() % 256;
    bool state_b2;
};

#endif // MAINWINDOW_H
