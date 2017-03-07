#include <QApplication>
#include "App.h"
#include "setusername.h"
#include <QProcess>

int main(int argc, char* argv[])
{
    //start control
    QProcess control, ft;
    control.start("../control/control.bin");
    ft.start("../filetransmit/filetransmit.bin");
    //start file transmit
    QApplication app(argc, argv);
    App* a = new App;
    SetUsername *setname = new SetUsername;
    QObject::connect(setname, SIGNAL(signame(QString)), a, SLOT(slotSetusername(QString)));
    QObject::connect(setname, SIGNAL(sigcancel()), qApp, SLOT(quit()));
    setname->exec();
    delete setname;
    app.exec();
}
