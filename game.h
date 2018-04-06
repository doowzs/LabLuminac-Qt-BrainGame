#ifndef GAME_H
#define GAME_H

#include <QQueue>
#include <QObject>
#include <QMainWindow>

namespace Ui {
  class Game;
}

class Game : public QMainWindow
{
  Q_OBJECT

signals:
  void sGameOver();

public slots:
  void gameStart();
  void submitAnswer();
  void countDown();
  void giveUp();

public:
  explicit Game(QWidget *parent = 0);
  ~Game();

private:
  Ui::Game *ui;
  int score = 0;
  int combo = 0;
  double totalTime = 0;
  int problemCount = 0;
  int level = 2;
  int difficulty = 1;
  int tmp1 = 0;
  bool tmp2 = 0;
  int tmp3 = 0;
  bool inGame = false;
  QQueue<int> num1;
  QQueue<int> num2;
  QQueue<bool> isAdd;
  QQueue<int> ans;
  void generateQuestion();
  void gameOver();
};

#endif // GAME_H
