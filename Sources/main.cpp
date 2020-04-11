#include <QApplication>
#include "Headers/login.h"
#include "Headers/qcmedit.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    QcmEdit a;
    a.show();


    return app.exec();
}
