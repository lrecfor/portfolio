#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget w;
    w.show();

    return a.exec();
}

/*2.Реализовать аналог QtMovableResizableWidgets.exe
 * дополнить функционал:
- двойной клик (или клик с ctrl) - делает привычное
нажатие на кнопку, добавить обработку такого события
- двойной клик на label позволяет изменять текст
(содержимое label)*/
