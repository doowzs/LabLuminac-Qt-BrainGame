#include "game.h"
#include "ui_game.h"
#include <ctime>
#include <QMessageBox>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QtMultimedia>
#include <windows.h>

Game::Game(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  connect(ui->answer, SIGNAL(returnPressed()), this, SLOT(submitAnswer()));
  connect(ui->submit, SIGNAL(clicked(bool)), this, SLOT(submitAnswer()));
  generateQuestion();
}

Game::~Game()
{
  delete ui;
}

void Game::submitAnswer(){
  if(ui->answer->text().isEmpty()) return;
  if(ui->answer->text().toInt() == ans){
      //QMessageBox::information(this, QString("吔！"), QString("恭喜你答对了！"));
  } else {
      QMediaPlayer *music = new QMediaPlayer();
      music->setMedia(QUrl("qrc:/Resources/FAQ.wav"));
      music->setVolume(50);
      music->play();
      //QMessageBox::warning(this, QString("谢！"), QString("这么简单都答错！"));
  }
  ui->answer->clear();
  generateQuestion();
}

void Game::generateQuestion() {
  srand(time(0));
  num1 = rand()%10;
  num2 = rand()%10;
  isAdd = rand()%2;
  ui->number1->move(ui->number1->x(),rand()%170+10);
  ui->number2->move(ui->number2->x(),rand()%170+10);
  ui->operation->move(ui->operation->x(),rand()%170+10);
  ui->number1->setText(QString::number(num1));
  ui->number2->setText(QString::number(num2));
  if (isAdd) {
      ui->operation->setText(QString("+"));
      ans = num1 + num2;
    } else {
      ui->operation->setText(QString("×"));
      ans = num1 * num2;
    }
}
