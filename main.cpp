#include "tasky.h"

#include <QProcess>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tasky w;
    w.show();
    /*QString ruta = "C:/Users/User/Downloads/Interfaz_7/build-Tasky-Desktop_Qt_6_5_3_MinGW_64_bit-Release/release/Tasky.exe";
    qDebug() << "Intentando ejecutar: " << ruta;
    QProcess *proceso = new QProcess();
    proceso->start(ruta);
    if(proceso->waitForFinished())
    {
        qDebug() << "Finalizado...\n";
    }
    else
    {
        qDebug() << "Error con el ejecutable...\n";
    }*/

    return a.exec();
}
