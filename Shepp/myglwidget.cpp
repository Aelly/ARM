#include "myglwidget.h"

myGLWidget::myGLWidget(int framesPerSecond, QWidget *parent, char *name)
    : QGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name));
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

void myGLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
    }
}

void myGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
       setXRotation(xRot + 8 * dy);
       setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
       setXRotation(xRot + 8 * dy);
       setZRotation(zRot + 8 * dx);
    }
   lastPos = event->pos();
}

void myGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void myGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void myGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void myGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void myGLWidget::qNormalizeAngle(int angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

//found at http://goldsequence.blogspot.com/2016/04/how-to-zoom-in-in-opengl-qt.html
void myGLWidget::wheelEvent(QWheelEvent *event)
{
 QPoint numDegrees = event->angleDelta();
 if (numDegrees.y() < 0){
    //Zoom
    zoomScale = zoomScale/1.1;
 }
 if (numDegrees.y() > 0){
     //Dezoom
    zoomScale = zoomScale*1.1;

 }
 updateGL(); // call paintGL()
 printf("%d", zoomScale);
}



