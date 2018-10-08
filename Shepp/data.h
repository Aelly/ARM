#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QString>
#include <QTextStream>

class Data{

public:
    Data();

    void readPGM3D(QString nameFile);

    int x;
    int y;
    int z;
    int lengthVertices;
    int lengthFaces;
    int*** rawData;
    float** vertices;
    int** faces;
};


#endif // DATA_H
