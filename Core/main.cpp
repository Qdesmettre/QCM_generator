#include <QApplication>
#include "ProjectEdit/qcmedit.h"
#include "Login/login.h"
#include <QMessageBox>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn start;

    // Au cas où plusieurs fichiers sont à ouvrir
    QStringList list;
    for(int i(0); i<argc; i++){
        list.push_back(argv[i]);
    }

    QcmEdit mainW(argc, list);


    QObject::connect(&start, SIGNAL(connected()), &mainW, SLOT(show()));

    start.show();



    return app.exec();
}
