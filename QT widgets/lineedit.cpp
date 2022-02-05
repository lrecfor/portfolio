#include "lineedit.h"

#include <QDebug>

lineEdit::lineEdit(const int size, QWidget* parent) :
    QLineEdit(parent)
{
    setStyleSheet("border: none;"
                        "background-color: transparent;"
                        "color: red;");

    font.setPixelSize(size);
    setFont(font);
    setAlignment(Qt::AlignCenter);
}
