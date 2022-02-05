#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class lineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit lineEdit(const int size, QWidget* parent = nullptr);

protected:

private:
    QFont font;
};

#endif // LINEEDIT_H
