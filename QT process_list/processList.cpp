#include "processList.h"
#include "ui_processList.h"

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <algorithm>

#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button_pressed = false;
    countProc = 0;

    process = new Process[countProcesses()];

    connect(ui->displayButton, &QPushButton::clicked, this, &MainWindow::getProcessList);
    connect(ui->startRealTimeButton, &QPushButton::clicked, this, &MainWindow::startRealTime);
    connect(ui->stopRealTimeButton, &QPushButton::clicked, this, &MainWindow::stopRealTime);
    connect(ui->nameButton, &QPushButton::clicked, this, &MainWindow::sortName);
    connect(ui->PIDButton, &QPushButton::clicked, this, &MainWindow::sortPID);
    connect(ui->parentPIDButton, &QPushButton::clicked, this, &MainWindow::sortParentPID);
    connect(ui->privateUsageButton, &QPushButton::clicked, this, &MainWindow::sortPrivateUsage);
    connect(ui->threadsButton, &QPushButton::clicked, this, &MainWindow::sortThreads);
    connect(ui->priorityButton, &QPushButton::clicked, this, &MainWindow::sortPriority);
    connect(ui->priorityClassButton, &QPushButton::clicked, this, &MainWindow::sortPriorityClass);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::countProcesses()
{
    PROCESSENTRY32 Process;
    HANDLE hProcess;
    Process.dwSize = sizeof(PROCESSENTRY32);

    hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(Process32First(hProcess, &Process))
    {
        do
        {
             countProc++;
        }
        while(Process32Next(hProcess, &Process));
     }
    return countProc;
}

void MainWindow::startRealTime()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(1500);
}

void MainWindow::update()
{
    if (button_pressed)
    {
        timer.stop();
        button_pressed = false;
    }
    clearBrowsers();
    getProcessList();
}

void MainWindow::stopRealTime()
{
    button_pressed = true;
}

void MainWindow::sortName()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.name < b.name; });
    display();
    setCursor();
}

void MainWindow::sortPID()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.PID < b.PID; });
    display();
    setCursor();
}

void MainWindow::sortParentPID()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.parentPID < b.parentPID; });
    display();
    setCursor();
}

void MainWindow::sortPrivateUsage()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.privateUsage < b.privateUsage; });
    display();
    setCursor();
}

void MainWindow::sortThreads()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.threads < b.threads; });
    display();
    setCursor();
}

void MainWindow::sortPriority()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.priority < b.priority; });
    display();
    setCursor();
}

void MainWindow::sortPriorityClass()
{
    clearBrowsers();
    std::sort(process, process+countProc, [](Process const &a, Process const &b){ return a.priorityClass < b.priorityClass; });
    display();
    setCursor();
}

void MainWindow::getProcessList()
{
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    DWORD dwPriorityClass;
    PROCESS_MEMORY_COUNTERS_EX pmc;
    ZeroMemory(&pmc, sizeof(PROCESS_MEMORY_COUNTERS_EX));

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof (PROCESSENTRY32);
    HANDLE hProcess;

    if(snap == INVALID_HANDLE_VALUE)
        return;

    dwPriorityClass = 0;

    if(! Process32First(snap, &pe)){
        CloseHandle(snap);
        return;
    }

    int i = 0;

    unsigned long history = 0;

    do {
        if(pe.th32ProcessID != 0)
        {
            process[i].name = QString::fromWCharArray(pe.szExeFile);
            process[i].PID = pe.th32ProcessID;
            process[i].parentPID = pe.th32ParentProcessID;
            process[i].threads = pe.cntThreads;
            process[i].priority = pe.pcPriClassBase;

            hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ProcessID);
            dwPriorityClass = GetPriorityClass(hProcess);

            ZeroMemory(&pmc, sizeof(PROCESS_MEMORY_COUNTERS_EX));
            GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
            if(pmc.PrivateUsage != 0)
                history = pmc.PrivateUsage;
            process[i].privateUsage = history;
            CloseHandle(hProcess);

            if (dwPriorityClass == ABOVE_NORMAL_PRIORITY_CLASS)
                process[i].priorityClass = "Above normal";
            if (dwPriorityClass == NORMAL_PRIORITY_CLASS)
                process[i].priorityClass = "Normal";
            if (dwPriorityClass == BELOW_NORMAL_PRIORITY_CLASS)
                process[i].priorityClass = "Low";
            if (dwPriorityClass == IDLE_PRIORITY_CLASS)
                process[i].priorityClass = "Idle";
            if (dwPriorityClass == HIGH_PRIORITY_CLASS)
                process[i].priorityClass = "High";
            if (dwPriorityClass == REALTIME_PRIORITY_CLASS)
                process[i].priorityClass = "Realtime";
            i++;
        }
    } while(Process32Next(snap, &pe));
    display();
    setCursor();
    CloseHandle(snap);
}

void MainWindow::display()
{
    for (int i = 0; i < countProc; i++)
    {
    ui->nameBrowser->append(process[i].name);
    ui->PIDBrowser->append(QString::number(process[i].PID));
    ui->parentPIDBrowser->append(QString::number(process[i].parentPID));
    ui->privateUsageBrowser->append(QString::number(process[i].privateUsage));
    ui->threadsBrowser->append(QString::number(process[i].threads));
    ui->priorityBrowser->append(QString::number(process[i].priority));
    ui->priorityClassBrowser->append(process[i].priorityClass);
    }
}

void MainWindow::clearBrowsers()
{
    ui->nameBrowser->clear();
    ui->PIDBrowser->clear();
    ui->parentPIDBrowser->clear();
    ui->privateUsageBrowser->clear();
    ui->threadsBrowser->clear();
    ui->priorityBrowser->clear();
    ui->priorityClassBrowser->clear();
}

void MainWindow::setCursor()
{
    QTextCursor cursor = ui->nameBrowser->textCursor();

    cursor = ui->nameBrowser->textCursor();
    cursor.setPosition(0);
    ui->nameBrowser->setTextCursor(cursor);

    cursor = ui->PIDBrowser->textCursor();
    cursor.setPosition(0);
    ui->PIDBrowser->setTextCursor(cursor);

    cursor = ui->parentPIDBrowser->textCursor();
    cursor.setPosition(0);
    ui->parentPIDBrowser->setTextCursor(cursor);

    cursor = ui->privateUsageBrowser->textCursor();
    cursor.setPosition(0);
    ui->privateUsageBrowser->setTextCursor(cursor);

    cursor = ui->threadsBrowser->textCursor();
    cursor.setPosition(0);
    ui->threadsBrowser->setTextCursor(cursor);

    cursor = ui->priorityBrowser->textCursor();
    cursor.setPosition(0);
    ui->priorityBrowser->setTextCursor(cursor);

    cursor = ui->priorityClassBrowser->textCursor();
    cursor.setPosition(0);
    ui->priorityClassBrowser->setTextCursor(cursor);
}
