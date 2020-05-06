#include <QApplication>
#include "ProjectEdit/qcmedit.h"
#include "Login/login.h"
#include <QMessageBox>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn start;

    QcmEdit mainW;
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


    QObject::connect(&start, SIGNAL(connected()), &mainW, SLOT(show()));

    start.show();



    return app.exec();
}
