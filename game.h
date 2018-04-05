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
  void gameOver();

public slots:
  void submitAnswer();
  void countDown();

public:
  explicit Game(QWidget *parent = 0);
  void gameStart();
  ~Game();

private:
  Ui::Game *ui;
  int score = 0;
  int combo = 0;
  int totalTime = 0;
  int problemCount = 0;
  int level = 2;
  int tmp1 = 0, tmp2 = 0;
  bool tmp3 = false;
  bool inGame = false;
  QQueue<int> num1;
  QQueue<int> num2;
  QQueue<bool> isAdd;
  QQueue<int> ans;
  void generateQuestion();
};

#endif // GAME_H
