#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationVersion("1.0");
    a.setApplicationName("Tridectet");
    a.setApplicationDisplayName(a.applicationName() + " (" + a.applicationVersion() + ")");

    MainWindow w;
    w.show();

    return a.exec();
}
