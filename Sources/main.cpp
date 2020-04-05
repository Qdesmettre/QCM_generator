#include <QApplication>
#include "Headers/login.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn base;
    base.show();

    return app.exec();
}
