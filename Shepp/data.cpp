#include "data.h"

Data::Data(){
  vertices = (float**) malloc(100*sizeof(float*));
  for(int i = 0; i<100 ; i++)
      vertices[i] = (float*) malloc(3*sizeof(float));
  verticesIndex = 0;
  verticesLength = 100;

  faces = (int**) malloc(100*sizeof(int*));
  for(int i = 0; i<100 ; i++)
      faces[i] = (int*) malloc(4*sizeof(int));
  facesIndex = 0;
  facesLength = 100;
}

void Data::readPGM3D(QString nameFile){
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
            text = flux.readLine(); //164 64 64 size
            getSize(text);

            rawData = new int**[width];
            for (int i=0; i<width; i++){
                rawData[i] = new int*[height];
                for(int j=0; j<height; j++){
                    rawData[i][j] = new int[depth];
                    for(int k=0; k<depth; k++){
                        rawData[i][j][k] = 0;
                    }
                }
            }

            text = flux.readLine(); //255 maxval

            for(int x = 0; x<width; x++){
                for(int y = 0; y<height; y++){
                    for(int z=0; z<depth; z++){
                        text = flux.readLine();
                        rawData[x][y][z] = text.toInt();
                    }
                }
            }
            return;
        }
        file.close();
    }
    else{
        printf("mauvais fichier\n");
    }
    return;
}


void Data::getSize(QString text){
    auto parts = text.split(" ");
    this->width = parts.at(0).toInt();
    this->height = parts.at(1).toInt();
    this->depth = parts.at(2).toInt();
}

int addVertice(float x, float y, float z){
    //Check size and resize if needed
    if(verticesIndex >= verticesLength){
        vertices = (float**) realloc(vertices, (2 * verticesLength) * sizeof(float*));
        for(int i=0; i<verticesLength; i++){
            vertices[verticesLength + i] = (float*) malloc(3*sizeof(float));
        }
        verticesLength *= 2;
    }

    //Add vertice
    vertices[verticesIndex][0] = x;
    vertices[verticesIndex][1] = y;
    vertices[verticesIndex][2] = z;
    verticesIndex++;

    return verticesIndex-1;
}

void addFace(int vertice1, int vertice2, int vertice3, int color){
    //Check size and resize if needed
    if(facesIndex >= facesLength){
        faces = (int**) realloc(faces, (2 * facesLength) * sizeof(int *));
        for(int i=0; i<facesLength; i++){
            faces[facesLength + i] = (int*) malloc(4*sizeof(int));
        }
        facesLength *= 2;
    }

    //Add Face
    faces[facesIndex][0] = vertice1;
    faces[facesIndex][1] = vertice2;
    faces[facesIndex][2] = vertice3;
    faces[facesIndex][3] = color;

    facesIndex++;
}

void Data::createCube(float coordx, float coordy, float coordz, float color)
{
    int x = 0;
    int y = 0;
    int z = 0;

    //face

        x = addVertice(coordx, coordy, coordz);
        y = addVertice(coordx + 1.0f, coordy, coordz);
        z = addVertice(coordx + 1.0f, coordy + 1.0f, coordz);
        addFace(x,y,z,color);

        y = addVertice(coordx, coordy + 1.0f, coordz);
        addFace(x,y,z,color);


    //gauche

        x = addVertice(coordx, coordy, coordz);
        y = addVertice(coordx, coordy + 1.0f, coordz);
        z = addVertice(coordx, coordy, coordz -1.0f);
        addFace(x,y,z,color);

        x = addVertice(coordx, coordy + 1.0f, coordz - 1.0f);
        addFace(x,y,z,color);


    //droit

        x = addVertice(coordx + 1.0f, coordy, coordz);
        y = addVertice(coordx + 1.0f, coordy + 1.0f, coordz);
        z = addVertice(coordx + 1.0f, coordy, coordz -1.0f);
        addFace(x,y,z,color);

        x = addVertice(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
        addFace(x,y,z,color);


    //haut

        x = addVertice(coordx, coordy + 1.0f, coordz);
        y = addVertice(coordx, coordy + 1.0f, coordz - 1.0f);
        z = addVertice(coordx + 1.0f, coordy + 1.0f, coordz);
        addFace(x,y,z,color);

        x = addVertice(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
        addFace(x,y,z,color);

    //bas

        x = addVertice(coordx, coordy, coordz);
        y = addVertice(coordx, coordy, coordz - 1.0f);
        z = addVertice(coordx + 1.0f, coordy, coordz);
        addFace(x,y,z,color);

        x = addVertice(coordx + 1.0f, coordy, coordz - 1.0f);
        addFace(x,y,z,color);

    //arrière

        x = addVertice(coordx, coordy, coordz - 1.0f);
        y = addVertice(coordx + 1.0f, coordy, coordz - 1.0f);
        z = addVertice(coordx + 1.0f, coordy + 1.0f, coordz - 1.0f);
        addFace(x,y,z,color);

        y = addVertice(coordx, coordy + 1.0f, coordz - 1.0f);
        addFace(x,y,z,color);
}




