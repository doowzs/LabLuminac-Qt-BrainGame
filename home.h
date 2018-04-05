#ifndef HOME_AND_GAME_H
#define HOME_AND_GAME_H

#include "game.h"
#include <QMainWindow>
#include <QtMultimedia>

namespace Ui {
  class Home;
}

class Home : public QMainWindow
{
  Q_OBJECT

public:
  explicit Home(QWidget *parent = 0);
  bool init();
  ~Home();

public slots:
  void playGame();
  void endGame();

private:
  Ui::Home *ui;
  bool gameOn = false;
  Game gayme;
  QMediaPlayer *music;
};

#endif // HOME_AND_GAME_H
