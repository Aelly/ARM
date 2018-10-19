#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H


#include <QtOpenGL>
#include <QGLWidget>
#include "GL/glu.h"

class myGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit myGLWidget(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;

    int xRot;
    int yRot;
    int zRot;
    float zoomScale =1;


protected:

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void keyPressEvent( QKeyEvent *keyEvent);
    virtual void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void qNormalizeAngle(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);


public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

private:
    QTimer *t_Timer;
    QPoint lastPos;

};




#endif // MYGLWIDGET_H
