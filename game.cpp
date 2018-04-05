#include "home.h"
#include "game.h"
#include "ui_game.h"
#include <ctime>
#include <QMessageBox>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QtMultimedia>
#include <QTimer>

QTimer *mainTimer, *problemTimer;

Game::Game(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  connect(ui->answer, SIGNAL(returnPressed()), this, SLOT(submitAnswer()));

  mainTimer = new QTimer();
  problemTimer = new QTimer();
  connect(mainTimer, SIGNAL(timeout()), this, SLOT(countDown()));
}

Game::~Game()
{
  delete mainTimer;
  delete problemTimer;
  delete ui;
}

void Game::gameStart() {
    problemCount = 0;
    totalTime = 60 + 2 * level;
    mainTimer->setInterval(1000);
    mainTimer->start();
    ui->timeleft->display((int)totalTime);
    for (int i = 0; i < level; i++) {
        generateQuestion();

        QTime reachTime = QTime::currentTime().addMSecs(2000);
        while(QTime::currentTime()<reachTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    generateQuestion();
    ui->answer->setEnabled(true);
    ui->answer->setPlaceholderText(QString("回答"));
    ui->answer->setFocus();
}

void Game::submitAnswer(){
    ui->answer->setEnabled(false);
    if (!ui->answer->text().isEmpty()
            && ui->answer->text().toInt() == ans.front()) {
        ui->answer->setPlaceholderText(QString("正确"));
        ui->result->setPixmap(QPixmap(":/Resources/correct.png"));
    } else {
        ui->answer->setPlaceholderText(QString::number(ans.front()));
        ui->result->setPixmap(QPixmap(":/Resources/wrong.png"));

        QMediaPlayer *music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/Resources/FAQ.wav"));
        music->setVolume(50);
        music->play();

    }

    ui->num31->setText(QString::number(num1.front()));
    ui->num33->setText(QString::number(num2.front()));
    if(isAdd.front()){
        ui->num32->setText(QString("+"));
    } else {
        ui->num32->setText(QString("×"));
    }
    ans.pop_front();
    num1.pop_front();
    num2.pop_front();
    isAdd.pop_front();
    QTime reachTime = QTime::currentTime().addMSecs(600);
    while(QTime::currentTime()<reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    generateQuestion();
    ui->answer->setPlaceholderText(QString("回答"));
    ui->answer->setText(QString(""));
    ui->answer->setEnabled(true);
    ui->answer->setFocus();
}

void Game::generateQuestion() {
  //ui->num31->setText(ui->num21->text());
  //ui->num32->setText(ui->num22->text());
  //ui->num33->setText(ui->num23->text());
  //ui->num21->setText(ui->num11->text());
  //ui->num22->setText(ui->num12->text());
  //ui->num23->setText(ui->num13->text());

  problemCount++;
  if(problemCount > level) {
    ui->num30->setText(QString::number(problemCount-level) + QString("."));
  }

  ui->num31->setText(QString(""));
  ui->num32->setText(QString("?"));
  ui->num33->setText(QString(""));
  ui->num21->setText(QString(""));
  ui->num22->setText(QString("?"));
  ui->num23->setText(QString(""));
  ui->result->setPixmap(QPixmap());

  srand(rand()%10086+time(0));
  tmp1 = rand()%12;
  tmp2 = rand()%2;
  tmp3 = rand()%12;
  num1.push_back(tmp1);
  isAdd.push_back(tmp2);
  num2.push_back(tmp3);

  ui->num10->setText(QString::number(problemCount) + QString("."));
  ui->num11->setText(QString::number(tmp1));
  ui->num13->setText(QString::number(tmp3));
  if (tmp2) {
      ans.push_back(tmp1 + tmp3);
      ui->num12->setText(QString("+"));
  } else {
      ans.push_back(tmp1 * tmp3);
      ui->num12->setText(QString("×"));
  }
}

void Game::countDown() {
    totalTime--;
    if(totalTime < 0){
        this->close();
    }
    ui->timeleft->display((int)totalTime);
}
