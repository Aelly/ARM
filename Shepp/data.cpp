#include "data.h"

Data::Data(){
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

            rawData = new int**[_x];
            for (int i=0; i<_x; i++){
                rawData[i] = new int*[_y];
                for(int j=0; j<_y; j++){
                    rawData[i][j] = new int[_z];
                    for(int k=0; k<_z; k++){
                        rawData[i][j][k] = 0;
                    }
                }
            }

            text = flux.readLine(); //255 maxval

            for(int x = 0; x<_x; x++){
                for(int y = 0; y<_y; y++){
                    for(int z=0; z<_z; z++){
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
    this->_x = parts.at(0).toInt();
    this->_y = parts.at(1).toInt();
    this->_z = parts.at(2).toInt();
}
