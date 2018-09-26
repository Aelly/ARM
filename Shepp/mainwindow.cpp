#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    myGLWidget(60, parent, "Premier Polygone avec OpenGL et Qt")
{

}

// Based on https://fhalgand.developpez.com/tutoriels/qt/integration-opengl/01-premiere-application/

void MainWindow::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}



void MainWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void MainWindow::createCube(float coordx, float coordy, float coordz, float color)
{
    //TODO set color as data color once for each face
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

    //face
    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy, coordz);
        glVertex3f(coordx + 1.0f, coordy, coordz);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy, coordz);
        glVertex3f(coordx, coordy + 1.0f, coordz);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz);
    glEnd();


    glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
    //gauche
    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy, coordz);
        glVertex3f(coordx, coordy + 1.0f, coordz);
        glVertex3f(coordx, coordy, coordz -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy + 1.0f, coordz);
        glVertex3f(coordx, coordy + 1.0f, coordz - 1.0f);
        glVertex3f(coordx, coordy, coordz - 1.0f);
    glEnd();


    glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
    //droit
    glBegin(GL_TRIANGLES);
        glVertex3f(coordx + 1.0f, coordy, coordz);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz);
        glVertex3f(coordx + 1.0f, coordy, coordz -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy, coordz - 1.0f);
    glEnd();


    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
    //haut
    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy + 1.0f, coordz);
        glVertex3f(coordx, coordy + 1.0f, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
        glVertex3f(coordx, coordy + 1.0f, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz);
    glEnd();

    glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
    //bas
    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy, coordz);
        glVertex3f(coordx, coordy, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy, coordz);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(coordx + 1.0f, coordy, coordz - 1.0f);
        glVertex3f(coordx, coordy, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy, coordz);
    glEnd();


    glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
    //arrière
    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(coordx, coordy, coordz - 1.0f);
        glVertex3f(coordx, coordy + 1.0f, coordz - 1.0f);
        glVertex3f(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
    glEnd();

}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    createCube(0.0f,0.0f,0.0f,4);



    //glTranslatef(3.0f, 0.0f, -6.0f);

}



MainWindow::~MainWindow()
{

}
