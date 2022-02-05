#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <QMainWindow>
#include <QTimer>
#include <windows.h>

namespace Ui {
class MainWindow;
}

struct Process
{
    QString name;
    DWORD PID;
    DWORD parentPID;
    DWORD privateUsage;
    DWORD threads;
    LONG priority;
    QString priorityClass;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int countProcesses();
    void getProcessList();
    void display();
    void setCursor();

private slots:
    void sortName();
    void sortPID();
    void sortParentPID();
    void sortPrivateUsage();
    void sortThreads();
    void sortPriority();
    void sortPriorityClass();
    void clearBrowsers();
    void startRealTime();
    void update();
    void stopRealTime();

private:
    Ui::MainWindow *ui;

    Process *process;
    int countProc;
    QTimer timer;

    bool button_pressed;
};

#endif // PROCESSLIST_H
