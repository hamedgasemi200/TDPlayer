#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QListWidget>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTabWidget>
#include <QTabBar>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QList>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QJsonArray items;

public slots:
    void requestTo(QUrl url);
    void requestFinished(QNetworkReply * reply);
    void linkClicked(QListWidgetItem * item);
    void currentTabChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
