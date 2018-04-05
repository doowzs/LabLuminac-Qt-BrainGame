#include "init.h"
#include "ui_init.h"
#include "sleep.h"
#include <QTimer>
#include <windows.h>
#include <QPixmap>
#include <QMatrix>
#include <QImage>

QTimer *timer;

Init::Init(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Init)
{
    ui->setupUi(this);

    //init();
    img->load(":/Resources/loading.png");
    *img = img->scaled(70, 70);
    //img->scaled(*size, Qt::KeepAspectRatio);
    ui->icon->setPixmap(QPixmap::fromImage(*img));

    timer = new QTimer;
    timer->setInterval(100);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
}

Init::~Init()
{
    delete img;
    delete imgx;
    delete mtrx;
    delete timer;
    delete ui;
}

void Init::rotate(){
    xdegree = (xdegree + 3) % 360;
    mtrx->rotate(xdegree);
    *imgx = img->transformed(*mtrx);
    ui->icon->setPixmap(QPixmap::fromImage(*imgx));
}


bool Init::init(){
    mysleep(300);
    startConnect();
    mysleep(300);
    establishConnect();
    mysleep(300);
    login();
    mysleep(300);
    getData();
    mysleep(300);
    return true;
}

void Init::startConnect(){
    ui->text->setText(QString("正在初始化……"));
    ui->text->show();
}
void Init::establishConnect(){
    ui->text->setText(QString("连接至数据中心……"));
    ui->text->show();
}
void Init::login(){
    ui->text->setText(QString("正在登陆……"));
    ui->text->show();
}
void Init::getData(){
    ui->text->setText(QString("取得远端数据……"));
    ui->text->show();
}
