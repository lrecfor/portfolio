#include "button.h"

button::button(const QString& text, QWidget* parent) :
    QPushButton(parent)
{
    setText (text);
    font.setPixelSize((width() / (this->text().size())) * 5);
    setFont(font);
    setStyleSheet("color: blue");

    ctrlIsPressed = false;
}

void button::mouseDoubleClickEvent (QMouseEvent *event)
{
    emit doubleClickedButton(event);
}

void button::keyPressEvent (QKeyEvent *)
{
    if (Qt::Key_Control)
        ctrlIsPressed = true;
}

void button::mousePressEvent(QMouseEvent *event)
{
    if (ctrlIsPressed)
        emit clickedButtonCtrl(event);
    emit clickedButton(event);
}

void button::resizeEvent(QResizeEvent *)
{
    font.setPixelSize((width() / (this->text().size())) * 2);
    setFont(font);
}
