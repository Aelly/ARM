#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myglwidget.h"
#include <QString>
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public myGLWidget
{
    Q_OBJECT

public:
    explicit MainWindow(Data &data, QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void createCube(float coordx, float coordy, float coordz, float color, float alpha);
    void paintGL();
    void readPGM3D(QString file);
    ~MainWindow();

     Data data;

private:
     void updateDistance();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
