#ifndef INIT_H
#define INIT_H

#include <QDialog>
#include <QPixmap>
#include <QMatrix>
#include <QImage>
#include <QSize>

namespace Ui {
class Init;
}

class Init : public QDialog
{
    Q_OBJECT

public:
    explicit Init(QWidget *parent = 0);
    bool init();
    ~Init();

public slots:
    void rotate();

private:
    Ui::Init *ui;
    int xdegree = 0;
    QSize *size = new QSize(70, 70);
    QImage *img = new QImage;
    QMatrix *mtrx = new QMatrix;
    QImage *imgx = new QImage;
    void startConnect();
    void establishConnect();
    void login();
    void getData();
};

#endif // INIT_H
