#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class graphWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setValue();

private:
    Ui::MainWindow *ui;

    graphWidget *widget;
};

#endif // MAINWINDOW_H
