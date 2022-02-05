#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{
    Q_OBJECT

public:
    explicit button(const QString& text = "", QWidget* parent = nullptr);

signals:
    void doubleClickedButton(QMouseEvent*);
    void clickedButton(QMouseEvent *);
    void clickedButtonCtrl(QMouseEvent *);

protected:
    void mouseDoubleClickEvent (QMouseEvent *event);
    void keyPressEvent (QKeyEvent *);
    void mousePressEvent (QMouseEvent *event);
    void resizeEvent(QResizeEvent *);

private:
    QFont font;
    bool ctrlIsPressed;
};

#endif // BUTTON_H
