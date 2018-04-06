#include "home.h"
#include "game.h"
#include "result.h"
#include "ui_game.h"
#include <ctime>
#include <QMessageBox>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QtMultimedia>
#include <QTimer>

QTimer *mainTimer;

Game::Game(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  ui->answer->setVisible(false);
  ui->equal->setVisible(false);

  connect(ui->startbutton, SIGNAL(clicked(bool)), this, SLOT(gameStart()));
  connect(ui->stopbutton, SIGNAL(clicked(bool)), this, SLOT(giveUp()));
  connect(ui->answer, SIGNAL(returnPressed()), this, SLOT(submitAnswer()));

  mainTimer = new QTimer();
  connect(mainTimer, SIGNAL(timeout()), this, SLOT(countDown()));
}

Game::~Game()
{
  delete mainTimer;
  delete ui;
}

void Game::gameStart() {
    score = 0;
    combo = 0;
    problemCount = 0;
    totalTime = 2 * level;

    mainTimer->setInterval(100);
    mainTimer->start();

    ui->answer->setEnabled(false);
    ui->startbutton->setVisible(false);
    ui->stopbutton->setVisible(true);
    ui->stopbutton->setEnabled(false);

    ui->score->setText(QString::number(score));
    ui->timeleft->setText(QString::number(totalTime, 'f', 1));

    for (int i = 0; i < level; i++) {
        generateQuestion();

        QTime reachTime = QTime::currentTime().addMSecs(2000);
        while(QTime::currentTime()<reachTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    generateQuestion();
    ui->answer->setEnabled(true);
    ui->answer->setVisible(true);
    ui->equal->setVisible(true);
    ui->timelabel->setText(QString("剩余时间："));
    ui->answer->setPlaceholderText(QString("作答"));
    ui->answer->setFocus();

    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Resources/attentiongo.wav"));
    music->setVolume(50);
    music->play();

    totalTime += 60;
    ui->stopbutton->setEnabled(true);
    ui->timeleft->setText(QString::number(totalTime, 'f', 1));
    inGame = true;
}

void Game::submitAnswer(){
    ui->answer->setEnabled(false);
    if (!ui->answer->text().isEmpty()
            && ui->answer->text().toInt() == ans.front()) {
        combo++;
        if (combo <= 5) {
            score += combo;
        } else {
            score += 5;
            if (combo > 10) {
                difficulty++;
                combo = 0;
            }
        }
        totalTime++;
        ui->score->setText(QString::number(score));

        ui->answer->setPlaceholderText(QString("作答"));
        ui->result->setPixmap(QPixmap(":/Resources/correct.png"));

        QMediaPlayer *music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/Resources/correct.wav"));
        music->setVolume(50);
        music->play();
    } else {
        combo = 0;
        if(difficulty>1)difficulty--;
        ui->answer->setPlaceholderText(QString::number(ans.front()));
        ui->result->setPixmap(QPixmap(":/Resources/wrong.png"));

        QMediaPlayer *music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/Resources/wrong.wav"));
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
    ui->answer->setPlaceholderText(QString("作答"));
    ui->answer->setText(QString(""));
    ui->answer->setEnabled(true);
    ui->answer->setFocus();
}

void Game::generateQuestion() {
  problemCount++;
  if(problemCount > 1){
      ui->num21->setText(QString(""));
      ui->num22->setText(QString("?"));
      ui->num23->setText(QString(""));
  }
  if(problemCount > level) {
    ui->num30->setText(QString::number(problemCount-level) + QString("."));
    ui->num31->setText(QString(""));
    ui->num32->setText(QString("?"));
    ui->num33->setText(QString(""));
    ui->num21->setText(QString(""));
    ui->num22->setText(QString("?"));
    ui->num23->setText(QString(""));
    ui->result->setPixmap(QPixmap());
  }

  srand(rand()%10086+time(0));
  tmp1 = rand()%(10*difficulty)+1; //dont want to be 0
  srand(rand()%10087+time(0));
  tmp2 = rand()%2;
  srand(rand()%10088+time(0));
  tmp3 = rand()%(15*difficulty+1);
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
    totalTime-=0.1;
    if(inGame && totalTime < 0){
        gameOver();
    }
    ui->timeleft->setText(QString::number(totalTime, 'f', 1));
}

void Game::giveUp() {
    gameOver();
}

void Game::gameOver() {
    mainTimer->stop();
    inGame = false;

    totalTime = 0;
    problemCount = 0;
    num1.clear();
    num2.clear();
    isAdd.clear();
    ans.clear();

    ui->startbutton->setVisible(true);
    ui->stopbutton->setVisible(false);
    ui->answer->setVisible(false);
    ui->answer->setEnabled(false);
    ui->equal->setVisible(false);

    ui->timelabel->setText(QString("准备时间："));
    ui->timeleft->setText(QString("0"));
    ui->score->setText(QString("0"));

    ui->num10->setText(QString(""));
    ui->num11->setText(QString(""));
    ui->num12->setText(QString(""));
    ui->num13->setText(QString(""));
    ui->num21->setText(QString(""));
    ui->num22->setText(QString(""));
    ui->num23->setText(QString(""));
    ui->num30->setText(QString(""));
    ui->num31->setText(QString(""));
    ui->num32->setText(QString(""));
    ui->num33->setText(QString(""));
    this->close();

    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Resources/correct.wav"));
    music->setVolume(50);
    music->play();

    QString result = QString("尻♂试结束，您的成绩是")
            + QString::number(score) + QString("分\n");
    if (score >= 80) {
        result = result + QString("恭喜你，考试成功！");
    } else {
        result = result + QString("您的成绩不合格，请继续努力！");
    }
    Result msgResult;
    msgResult.showResult(result);
    msgResult.show();
    msgResult.exec();
    emit sGameOver();
}
