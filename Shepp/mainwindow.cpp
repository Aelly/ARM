#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>


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
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
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

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -100.0f);

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    QString file = "ARM/shepp_logan.pgm3d";
    readPGM3D(file);


    //glTranslatef(3.0f, 0.0f, -6.0f);

}

void MainWindow::readPGM3D(QString nameFile){
    QFile file(nameFile);
    QString text;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&file);
        if(!flux.atEnd()){
            text = flux.readLine();
            if(text.compare(text,"PGM3D\n")){
                printf("ok\n");
            }
            else{
                printf("Wrong format\n");
                return;
            }
            text = flux.readLine(); //64 64 64 size
            text = flux.readLine(); //255 maxval
            float offx=-32;
            float offy=-32;
            float offz=-32;
            for(float x = 0; x<64; x++){
                for(float y = 0; y<64; y++){
                    for(float z=0; z<64; z++){
                        text = flux.readLine();
                        float color = text.toFloat();
                        if (color>0){
                            createCube(offx+x,offy+y,offz+z,color,0.02);

                        }
                        printf("%f\n", color);
                    }
                }
            }
            printf("%s\n", text.toLatin1().data());
            return;
        }
        file.close();
    }
    else{
        printf("mauvais fichier\n");
    }
    return;
}



MainWindow::~MainWindow()
{

}
