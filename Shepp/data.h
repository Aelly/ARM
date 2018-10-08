#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QString>
#include <QTextStream>

class Data{

public:
    Data();

    void readPGM3D(QString nameFile);

    int _x;
    int _y;
    int _z;
    int lengthVertices;
    int lengthFaces;
    int*** rawData;
    float** vertices;
    int** faces;

private:
    void getSize(QString text);
};


#endif // DATA_H
