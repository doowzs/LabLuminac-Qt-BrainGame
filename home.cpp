#include "home.h"
#include "game.h"
#include "init.h"
#include "ui_home.h"
#include <QMessageBox>
#include <QtMultimedia>

Home::Home(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Home)
{
  ui->setupUi(this);
  ui->pushButton->setFocus();
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(playGame()));
  connect(&gayme, SIGNAL(gameOver()), this, SLOT(endGame()));

  music = new QMediaPlayer();
  music->setMedia(QUrl("qrc:/Resources/homemenu.mp3"));
  music->setVolume(5);
}

bool Home::init(){
    Init *x = new Init;
    x->show();
    if (x->init()) {
        delete x;
        music->play();
        return true;
    }
    music->play();
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
    music->stop();
    this->close();
    gayme.show();
    gayme.gameStart();
  }
}

void Home::endGame() {
    if (this->init()){
        this->show();
        this->music->play();
    }
    gameOn = false;
}
