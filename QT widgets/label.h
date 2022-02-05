#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QScrollArea>

class label : public QLabel
{
    Q_OBJECT

public:
    explicit label(const QString& text = "", QWidget* parent = nullptr);

signals:
    void doubleClickedLabel(QMouseEvent *);
    void clickedLabel(QMouseEvent *);

protected:
    void mouseDoubleClickEvent (QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void resizeEvent(QResizeEvent *);

private:
    QFont font;
    QScrollArea scrollArea;
};

#endif // LABEL_H
