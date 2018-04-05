#ifndef SLEEP_H
#define SLEEP_H

#include <QCoreApplication>
#include <QEventLoop>
#include <QTime>

void mysleep(unsigned int msec) {
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime()<reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

#endif // SLEEP_H
