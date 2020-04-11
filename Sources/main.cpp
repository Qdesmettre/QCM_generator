#include <QApplication>
#include "Headers/login.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn a;
    a.show();


    return app.exec();
}
