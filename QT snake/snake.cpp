#include "snake.h"
#include "ui_snake.h"

#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QRadioButton>
#include <QSize>
#include <QLabel>
#include <QStringList>
#include <QRandomGenerator>
#include <QInputDialog>

Snake::Snake(QWidget *parent) : QWidget(parent) {

    QLabel *lbl = new QLabel(this);
    lbl->setGeometry(400, 0, 200, 400);
    QPixmap pix(":/new/prefix1/images/background.png");
    lbl->setPixmap(pix);

    QSize size1(400, 370);
    QPixmap bkgnd(":/new/prefix1/images/background_1.png");
    bkgnd = bkgnd.scaled(size1, Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QLabel *curtain = new QLabel(this);
    curtain->setGeometry(0, 370, 400, 30);
    curtain->setStyleSheet("background-color:white;");

    QLabel *lbl_apple = new QLabel(this);
    lbl_apple->setGeometry(10, 370, 15, 30);
    lbl_apple->setStyleSheet("background-color:white;");
    QPixmap pix_apple(":/new/prefix1/images/apple.png");
    lbl_apple->setPixmap(pix_apple);

    lbl_text = new QLabel(this);
    lbl_text->setGeometry(30, 370, 60, 30);
    lbl_text->setStyleSheet("background-color:white;");

    lbl_pause = new QLabel(this);

    QPushButton *pb_1 = new QPushButton(this);
    pb_1->setText("start");
    pb_1->setGeometry(450, 40, 101, 30);
    QPushButton *pb_2 = new QPushButton(this);
    pb_2->setText("restart");
    pb_2->setGeometry(450, 90, 101, 30);
    QPushButton *pb_3 = new QPushButton(this);
    pb_3->setText("color");
    pb_3->setGeometry(450, 140, 101, 30);
    QPushButton *pb_4 = new QPushButton(this);
    pb_4->setText("pause");
    pb_4->setGeometry(450, 190, 101, 30);
    QPushButton *pb_5 = new QPushButton(this);
    pb_5->setText("exit");
    pb_5->setGeometry(450, 240, 101, 30);

    connect(pb_1, &QPushButton::clicked, this, &Snake::start_game);
    connect(pb_2, &QPushButton::clicked, this, &Snake::restart);
    connect(pb_3, &QPushButton::clicked, this, &Snake::change_snake);
    connect(pb_4, &QPushButton::clicked, this, &Snake::pause);
    connect(pb_5, &QPushButton::clicked, this, &Snake::app_exit);

    left_direction = false;
    right_direction = true;
    up_direction = false;
    down_direction = false;
    in_game = true;
    isPaused = false;
    isStarted = false;

    point = 0;

    setFixedSize(600, 400);

}

void Snake::pause(){

    if (!isStarted)
        return;
    if (isPaused)
        resume();

    else {

        pause_();
        timer.stop();
        isPaused = true;
    }
}

void Snake::resume(){

        lbl_pause->clear();
        timer.start(DELAY, this);
        isPaused = false;
}

void Snake::points(){
    lbl_text->setText(QString::number(point++));
}

void Snake::change_snake(){

    if (!isPaused) pause();
    load_images();

    dot_0=dot;
    head_0=head;

    dot_1.load(":/new/prefix1/images/dot_1.png");
    head_1.load(":/new/prefix1/images/head_1.png");

    dot_2.load(":/new/prefix1/images/dot_2.png");
    head_2.load(":/new/prefix1/images/head_2.png");

    QStringList items;
    items << tr("red") << tr("blue") << tr("purple");
    bool ok;
    QString item = QInputDialog::getItem(
                this, tr("QInputDialog::getItem()"),
                tr("<p align='center'>choose color:"), items, 0, false, &ok, Qt::Popup);
    if (ok && !item.isEmpty()){

        if (item == "red"){

            dot=dot_0;
            head=head_0;
        }

        if (item == "blue"){

            dot=dot_1;
            head=head_1;
        }

        if (item == "purple"){

            dot=dot_2;
            head=head_2;
        }
    }

    snake_color = 1;

    resume();
}

void Snake::start_game(){

    if (snake_color == 0) load_images();
    isStarted = true;

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    create_apple();
    create_skull();

    timer.start(DELAY, this);
}

void Snake::restart(){

    killTimer(this->timerId);
    this->timerId = 0;

    for(int i = 0; i < ALL_DOTS; i++){
        x[i] = 0;
        y[i] = 0;
    }

    left_direction = false;
    right_direction = true;
    up_direction = false;
    down_direction = false;
    in_game = true;

    start_game();
}

void Snake::app_exit(){

    close();
}

void Snake::load_images() {

    dot.load(":/new/prefix1/images/dot.png");
    head.load(":/new/prefix1/images/head.png");
    apple.load(":/new/prefix1/images/apple.png");
    game_over.load(":/new/prefix1/images/gameover.png");
    skull.load(":/new/prefix1/images/skull.png");
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    do_drawing();

}

void Snake::do_drawing() {

    QPainter qp(this);

    if (!in_game) {

        gameover(qp);
        killTimer(this->timerId);
        this->timerId = 0;
    }

    else {

        for(int count = 0; count < 15; count++){
            qp.drawImage(s_x[count], s_y[count], skull);
        }

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }
    }

}

void Snake::gameover(QPainter &qp) {

    qp.drawPixmap(100, 125, QPixmap(":/new/prefix1/images/gameover.png"));
}

void Snake::pause_(){

    lbl_pause->setGeometry(100, 125, 200, 106);
    QPixmap pix_pause(":/new/prefix1/images/pause.png");
    lbl_pause->setPixmap(pix_pause);
}

void Snake::check_apple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        create_apple();
    }
}

void Snake::check_skull(){

    for (int i = 0; i < 15; i++){
        if ((x[0] == s_x[i]) && (y[0] == s_y[i])) {
            in_game = false;
        }
    }
}

void Snake::moving() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (left_direction) {
        x[0] -= DOT_SIZE;
    }

    if (right_direction) {
        x[0] += DOT_SIZE;
    }

    if (up_direction) {
        y[0] -= DOT_SIZE;
    }

    if (down_direction) {
        y[0] += DOT_SIZE;
    }
}

void Snake::check_collision() {

    if (y[0] >= B_HEIGHT) {
        in_game = false;
    }

    if (y[0] < 0) {
        in_game = false;
    }

    if (x[0] >= B_WIDTH) {
        in_game = false;
    }

    if (x[0] < 0) {
        in_game = false;
    }

    if(!in_game) {
       killTimer(this->timerId);
       this->timerId = 0;
    }
}

void Snake::create_apple() {

    qsrand(QTime::currentTime().msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);

    points();
}

int Snake::random_xy(){

    return (QRandomGenerator::global()->bounded(0, RAND_POS) * DOT_SIZE);
}

void Snake::create_skull(){

    for (int i = 0; i < 15; i++){
        s_x[i] = random_xy();
        for (int z = 0; z < 3; z++){
        if (s_x[i] == x[z])
            s_x[i] = random_xy();
        }
        s_y[i] = random_xy();
        for (int z = 0; z < 3; z++){
        if (s_x[i] == y[i])
            s_x[i] = random_xy();
        }
    }
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e); 

    if (in_game) {

        check_apple();
        check_skull();
        check_collision();
        moving();
        repaint();
    }


}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_4 || key == Qt::Key_A) && (!right_direction)) {
        left_direction = true;
        up_direction = false;
        down_direction = false;
    }

    if ((key == Qt::Key_6 || key == Qt::Key_D) && (!left_direction)) {
        right_direction = true;
        up_direction = false;
        down_direction = false;
    }

    if ((key == Qt::Key_8 || key == Qt::Key_W) && (!down_direction)) {
        up_direction = true;
        right_direction = false;
        left_direction = false;
    }

    if ((key == Qt::Key_2 || key == Qt::Key_S) && (!up_direction)) {
        down_direction = true;
        right_direction = false;
        left_direction = false;
    }

    QWidget::keyPressEvent(e);
}
