#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QString>
#include <QTextStream>

class Data{

public:
    Data();

    void readPGM3D(QString nameFile);

    int width;
    int height;
    int depth;
    int verticesLength;
    int facesLength;
    int*** rawData;
    float** vertices;
    int verticesIndex;
    int** faces;
    int facesIndex;

private:
    void getSize(QString text);

    int addVertice(float x, float y, float z); //Add a new vertice to the vertices matrix (resize+add) return index of added vertice
    void addFace(int vertice1, int vertice2, int vertice3, int color); //Add a new triangle face with the color and the 3 vertices (resize+add)


};


#endif // DATA_H
