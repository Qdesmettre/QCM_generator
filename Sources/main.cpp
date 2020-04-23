#include <QApplication>
#include "Headers/login.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn login;
    login.show();

    return app.exec();
}
