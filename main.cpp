#include <QApplication>
#include "Project/qcmedit.h"
#include <QSettings>
#include <QFile>
int main(int argc, char **argv){




    QCoreApplication::setApplicationName("QCMake");
    QCoreApplication::setOrganizationName("QDesmettre");
    QCoreApplication::setOrganizationDomain("https://github.com/Qdesmettre/");

    QSettings settings;

    QStringList list;
    for(int i(0); i<argc; i++){
        list.push_back(argv[i]);
    }
    list << settings.value("qcmedit/projects").toStringList();

     QApplication app(argc, argv);

    QFile f(":/Dark/darkOrange.qss");
    f.open(QFile::ReadOnly);
    QString ss = f.readAll();
    app.setStyleSheet(ss);
    f.close();

    srand(time(nullptr));
    QcmEdit mainW(argc, list);

    mainW.resize(settings.value("qcmedit/size").toSize());
    mainW.move(settings.value("qcmedit/position").toPoint());

    mainW.show();

    return app.exec();
}
