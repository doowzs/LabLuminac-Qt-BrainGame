#include "home.h"
#include "game.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Home w;
  w.show();

  return a.exec();
}
