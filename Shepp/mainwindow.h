#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myglwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public myGLWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
