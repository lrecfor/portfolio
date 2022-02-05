#include "label.h"

#include <QPainter>
#include <QFont>

label::label(const QString& text, QWidget* parent) :
    QLabel(parent)
{
    setText (text);
    setStyleSheet("color: red;");
    setAlignment(Qt::AlignCenter);
}

void label::mouseDoubleClickEvent (QMouseEvent *event)
{
    emit doubleClickedLabel(event);
}

void label::mousePressEvent(QMouseEvent *event)
{
    emit clickedLabel(event);
}

void label::resizeEvent(QResizeEvent *)
{
    font.setPixelSize(width() / 12);
    setFont(font);
}
