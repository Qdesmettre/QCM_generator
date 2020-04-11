#include <QApplication>
#include "Headers/login.h"
#include "Headers/project.h"
int main(int argc, char **argv){
    QApplication app(argc, argv);

    Project a;
    a.show();


    return app.exec();
}
