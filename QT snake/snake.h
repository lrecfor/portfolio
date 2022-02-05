#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QBasicTimer>
#include <QMdiArea>

class Snake : public QWidget {

  public:
      Snake(QWidget *parent = nullptr);

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
      QImage dot;
      QImage head;
      QImage apple;
      QImage game_over;
      QImage skull;
      QImage pause_png;

      QImage dot_0;
      QImage head_0;
      QImage dot_1;
      QImage head_1;
      QImage dot_2;
      QImage head_2;

      QBasicTimer timer;
      QLabel *lbl_text;
      QLabel *lbl_pause;

      static const int B_WIDTH = 400;
      static const int B_HEIGHT = 370;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 1480;
      static const int RAND_POS = 29;
      static const int DELAY = 140;

      int timerId;
      bool isStarted;
      bool isPaused;

      int dots;
      int point = 0;
      int apple_x;
      int apple_y; 

      int snake_color = 0;

      int x[ALL_DOTS];
      int y[ALL_DOTS];
      int s_x[15];
      int s_y[15];

      bool left_direction;
      bool right_direction;
      bool up_direction;
      bool down_direction;
      bool in_game;

      void load_images();
      void create_apple();
      void create_skull();
      void check_apple();
      void check_skull();
      void check_collision();
      void moving();
      void do_drawing();
      void gameover(QPainter &);
      void pause_();

      void pause();
      void resume();
      void app_exit();
      void start_game();
      void restart();
      void restart_game();
      void change_snake();
      void points();
      int random_xy();

};
#endif // SNAKE_H
