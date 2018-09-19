#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../../shepp_logan.pgm3d");

    qDebug() << QT_VERSION_STR;
    MainWindow w;
    w.show();

    return a.exec();
}
