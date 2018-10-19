#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>


MainWindow::MainWindow(Data &data,QWidget *parent) :
    myGLWidget(60, parent, "ARM projet")
{
    this->data = data;
}

// Based on https://fhalgand.developpez.com/tutoriels/qt/integration-opengl/01-premiere-application/

void MainWindow::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void MainWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void MainWindow::createCube(float coordx, float coordy, float coordz, float color, float alpha)
{
    //TODO set color as data color once for each face
    glColor4f(color, color, color, alpha);

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

void MainWindow::updateDistance(){
    //Get the modelViewMatrix ("camera position")
    GLfloat matrix[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, matrix );

    float DOF[3];
    DOF[0] = matrix[  2 ]; // x
    DOF[1] = matrix[  6 ]; // y
    DOF[2] = matrix[ 10 ]; // z

    //Compute and update the distance for each face
    //We simplify the position of the face as the position of the first vertice composing this face
    for(int i=0; i<data.facesIndex; i++){
        int fX = data.vertices[data.faces[i][0]][0];
        int fY = data.vertices[data.faces[i][0]][1];
        int fZ = data.vertices[data.faces[i][0]][2];
        float distance = std::sqrt((DOF[0]-fX)*(DOF[0]-fX) + (DOF[1]-fY)*(DOF[1]-fY) + (DOF[2]-fZ)*(DOF[2]-fZ));
        data.faces[i][4] = distance;
        //printf("%f\n",distance);
    }
}

bool cmp( int* a, int* b){
    return a[4] < b[4];
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -120.0f);

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    glScaled(zoomScale, zoomScale, zoomScale);

    //glTranslatef(3.0f, 0.0f, -6.0f);

    //Update the distance and sort by distance before drawing
    updateDistance();
    std::sort(data.faces, data.faces + data.facesIndex, cmp);


    float offset_x = data.width /2.0;
    float offset_y = data.height /2.0;
    float offset_z = data.depth /2.0;



    for (int i = 0; i < data.facesIndex; i++){
        glColor4f(data.faces[i][3], data.faces[i][3], data.faces[i][3],0.25);
        glBegin(GL_TRIANGLES);
            glVertex3f(data.vertices[data.faces[i][0]][0] - offset_x, data.vertices[data.faces[i][0]][1] - offset_y, data.vertices[data.faces[i][0]][2] - offset_z);
            glVertex3f(data.vertices[data.faces[i][1]][0] - offset_x, data.vertices[data.faces[i][1]][1] - offset_y, data.vertices[data.faces[i][1]][2] - offset_z);
            glVertex3f(data.vertices[data.faces[i][2]][0] - offset_x, data.vertices[data.faces[i][2]][1] - offset_y, data.vertices[data.faces[i][2]][2] - offset_z);
        glEnd();
    }
}


MainWindow::~MainWindow()
{

}
