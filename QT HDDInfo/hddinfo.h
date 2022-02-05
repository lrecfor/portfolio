#ifndef HDDINFO_H
#define HDDINFO_H

#include <QWidget>
#include <QStorageInfo>

namespace Ui {
class hddinfo;
}

class hddinfo : public QWidget
{
    Q_OBJECT

public:
    explicit hddinfo(QWidget *parent = nullptr);
    ~hddinfo();

private:
    Ui::hddinfo *ui;
    void HDDinfo();
    void HDDsize();
};

#endif // HDDINFO_H
