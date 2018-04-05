#include "home.h"
#include "game.h"
#include "init.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);  

  Home w;
  if (w.init()){
      w.show();
  }

  return a.exec();
}
