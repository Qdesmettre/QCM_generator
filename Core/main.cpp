#include <QApplication>
#include "ProjectEdit/printer.h"
#include <QTranslator>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    // Au cas où plusieurs fichiers sont à ouvrir
    QStringList list;
    for(int i(0); i<argc; i++){
        list.push_back(argv[i]);
    }

    PrintSetter mainW;

    mainW.show();



    return app.exec();
}
