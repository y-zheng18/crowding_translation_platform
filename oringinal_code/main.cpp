#include "mainwindow.h"
#include <QApplication>
#include "edituserfile_ui.h"
#include "user.h"
#include "dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    MainWindow w;
    w.show();
    return a.exec();
}
