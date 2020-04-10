#include <QApplication>
#include "Headers/login.h"
#include <iostream>
#include "Headers/question.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    LogIn a;
    a.show();


    return app.exec();
}
