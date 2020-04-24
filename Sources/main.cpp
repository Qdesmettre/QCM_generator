#include <QApplication>
#include "Headers/qcmedit.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    QcmEdit main;
    main.show();

    // Ouverture par un/plusieurs .qcm
    if(argc>1){

    }

    return app.exec();
}
