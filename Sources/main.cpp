#include <QApplication>
#include "Headers/signin.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    SignIn test;
    test.show();

    return app.exec();
}
