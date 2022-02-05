#include "hddinfo.h"
#include "ui_hddinfo.h"

hddinfo::hddinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hddinfo)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    connect(ui->pushButton, &QPushButton::clicked, this, &hddinfo::HDDinfo);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &hddinfo::HDDsize);
}

hddinfo::~hddinfo()
{
    delete ui;
}

void hddinfo::HDDinfo()
{
    QString text;
    QStorageInfo storage = QStorageInfo::root();
    text="name: " + storage.name() + "\n";
    text+="fileSystemType: " + storage.fileSystemType();
    ui->textEdit->setText(text);
}

void hddinfo::HDDsize()
{
    QStorageInfo storage = QStorageInfo::root();
    long long bytesTotal = storage.bytesTotal()/1024/1024/1024,
            bytesAvailable = storage.bytesAvailable()/1024/1024/1024;
    QString text = "size: " +
            QString::number(bytesTotal)
            + "\navailable size: " +
            QString::number(bytesAvailable);
    ui->textEdit_2->setText(text);
    ui->progressBar->setValue(100-(static_cast<int>(bytesAvailable*100/bytesTotal)));
}
