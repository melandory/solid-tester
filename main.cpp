#include <QDebug>
#include <QCoreApplication>
#include "AudioCdTest.h"

int main(int argc, char* argv[])
{
    AudioCdTest test;
    test.init();
    qDebug() << "Waiting for devices";
    QCoreApplication a(argc, argv);
    return a.exec();
}
