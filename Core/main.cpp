#include <QApplication>
#include "ProjectEdit/qcmedit.h"
#include "Login/login.h"
#include <QMessageBox>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn start;
    QcmEdit mainW;

    QObject::connect(&start, SIGNAL(connected()), &mainW, SLOT(show()));

    start.show();



    return app.exec();
}
