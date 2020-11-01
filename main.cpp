#include <QApplication>
#include "Project/qcmedit.h"
#include <QSettings>
#include <QFile>
int main(int argc, char **argv){
    QStringList list;
    for(int i(0); i<argc; i++){
        list.push_back(argv[i]);
    }
  /*QSettings settings("QDesmettre", "QCMake");
    if(settings.value("editor/openned").toBool()){
        settings.setValue("editor/newFilesToOpen", true);
        settings.setValue("editor/newFiles", list);
        return 0;
    }
    else{
        QApplication app(argc, argv);

        srand(time(nullptr));

        QcmEdit mainW(argc, list);
        mainW.show();
        settings.setValue("editor/openned", true);
        settings.setValue("editor/newFilesToOpen", false);
        return app.exec();
    }*/
    QApplication app(argc, argv);

    QFile f(":/Dark/darkOrange.qss");
    f.open(QFile::ReadOnly);
    QString ss = f.readAll();
    app.setStyleSheet(ss);
    f.close();

    srand(time(nullptr));
    QcmEdit mainW(argc, list);
    mainW.show();

    return app.exec();
}
