#include "mainwindow.h"
#include <QApplication>
#include "data.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../../shepp_logan.pgm3d");

    qDebug() << QT_VERSION_STR;
    Data *data = new Data();
    MainWindow *w = new MainWindow(*data);
    w->show();

    return a.exec();
}
