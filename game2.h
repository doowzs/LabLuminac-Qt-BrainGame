#ifndef GAME_H
#define GAME_H

#include <QDialog>

namespace Ui {
  class Game;
}

class Game : public QDialog
{
  Q_OBJECT

public slots:
  void submitAnswer();

public:
  explicit Game(QWidget *parent = 0);
  ~Game();

private:
  Ui::Game *ui;
  void generateQuestion();
  int num1 = 0;
  int num2 = 0;
  bool isAdd = false;
  int ans = 0;
};

#endif // GAME_H
