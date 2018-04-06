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
  connect(&gayme, SIGNAL(sGameOver()), this, SLOT(endGame()));

  music = new QMediaPlayer();
  list = new QMediaPlaylist();
  list->addMedia(QUrl("qrc:/Resources/kaoshimusic.wav"));
  list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  music->setPlaylist(list);
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
    QMessageBox::information(this,QString("错误"),QString("尻♂试已经开始！"));
  } else {
    gameOn = true;
    music->stop();
    this->close();
    gayme.show();
  }
}

void Home::endGame() {
    if (this->init()){
        this->show();
        this->music->play();
    }
    gameOn = false;
}
