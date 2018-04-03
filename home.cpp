#include "home.h"
#include "game.h"
#include "ui_home.h"
#include <QMessageBox>

Home::Home(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Home)
{
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(playGame()));
}

Home::~Home()
{
  delete ui;
}

void Home::playGame(){
  if(gameOn){
    QMessageBox::information(this,QString("错误"),QString("游戏已经开始"));
  } else {
    Game gayme(this);
    gayme.show();
    gameOn = true;
    gayme.exec();
    gameOn = false;
  }
}
