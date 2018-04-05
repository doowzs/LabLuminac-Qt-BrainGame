#include "home.h"
#include "game.h"
#include "init.h"
#include "ui_home.h"
#include <QMessageBox>

Home::Home(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Home)
{
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(playGame()));
}

bool Home::init(){
    Init *x = new Init;
    x->show();
    if (x->init()) {
        delete x;
        return true;
    }
    return false;
}

Home::~Home()
{
  delete ui;
}

void Home::playGame(){
  if(gameOn){
    QMessageBox::information(this,QString("错误"),QString("游戏已经开始"));
  } else {
    gameOn = true;
    this->close();
    gayme.show();
    gayme.gameStart();
  }
}
