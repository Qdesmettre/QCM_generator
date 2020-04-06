#include <QApplication>
#include "Headers/login.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn test;
    test.show();

    return app.exec();
}
