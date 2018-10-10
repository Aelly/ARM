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


