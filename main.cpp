#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Application object
    QApplication a(argc, argv);

    // Load external stylesheet
    QFile file(":/css/index.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    // Set application version
    a.setApplicationVersion("1.0");

    // Set application title
    a.setApplicationName("Tridectet");

    // Set application name
    a.setApplicationDisplayName(a.applicationName() + " (" + a.applicationVersion() + ")");

    // Show window
    MainWindow w;
    w.show();

    // Continue the app
    return a.exec();
}
