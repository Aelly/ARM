#include "data.h"

Data::Data(){
    printf("test");
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
                        /*if (color>0){
                            createCube(offx+x,offy+y,offz+z,color,0.02);

                        }*/
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
