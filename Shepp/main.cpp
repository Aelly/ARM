#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include "data.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../../shepp_logan.pgm3d");
    QWidget *tmp = new QWidget();
    QString filename =  QFileDialog::getOpenFileName(
              tmp,
              "Open Document",
              QDir::currentPath(),
              "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

        if( filename.isNull() )
        {
          return 0;
        }


    qDebug() << QT_VERSION_STR;
    Data *data = new Data();
    data->readPGM3D(filename);
    data->createObject();
    MainWindow *w = new MainWindow(*data);
    w->show();

    return a.exec();
}
