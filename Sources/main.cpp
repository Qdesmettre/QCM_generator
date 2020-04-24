#include <QApplication>
#include "Headers/qcmedit.h"
#include <QMessageBox>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    QcmEdit mainW;
    mainW.show();

    // Au cas où plusieurs fichier sont à ouvrir
    for(int i(1); i<argc; i++){
        QString empla = argv[i];
        if(empla.back() == "m" &&
                empla[empla.size()-2] == "c" &&
                empla[empla.size()-3] == "q" &&
                empla[empla.size()-4] == ".")

            mainW.open(argv[i]);
        else QMessageBox::critical(&mainW, QObject::tr("Erreur"), QObject::tr("Impossible d'ouvrir ")+argv[i]);
    }



    return app.exec();
}
