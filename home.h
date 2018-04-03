#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

namespace Ui {
  class Home;
}

class Home : public QMainWindow
{
  Q_OBJECT

public:
  explicit Home(QWidget *parent = 0);
  ~Home();

public slots:
  void playGame();

private:
  Ui::Home *ui;
  bool gameOn = false;
};

#endif // HOME_H
