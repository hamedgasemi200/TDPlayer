#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Make tab bar expanded.
    ui->tabWidget->tabBar()->setExpanding(true);
    ui->tabWidget->tabBar()->setDocumentMode(true);

    // Connect tab changed signal to its slot
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::currentTabChanged);
    MainWindow::currentTabChanged(ui->tabWidget->currentIndex());

    auto list_widgets = ui->tabWidget->findChildren<QListWidget*>();
    for(int i = 0; i < list_widgets.count(); i++) connect(list_widgets.at(i), &QListWidget::itemClicked, this, &MainWindow::linkClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::requestTo(QUrl url)
{
    ui->statusBar->showMessage("⚫️ Loading from " + url.toString() + " ...");

    // Access Manager => Manages the request
    QNetworkAccessManager * manager = new QNetworkAccessManager;

    // QNetwork => Configures the request
    QNetworkRequest * request = new QNetworkRequest(url);

    // Network Reply => Gives some helper methods to the reply
    QNetworkReply * reply = manager->get(* request);

    // Connet signals to slots
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::requestFinished);
}

void MainWindow::requestFinished(QNetworkReply * reply)
{
    //QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    // Show Message
    ui->statusBar->showMessage("✅ Content loaded successfully.", 2000);

    // Get Text
    QString json_text = reply->readAll();

    // Parse data as array
    QJsonArray items = QJsonDocument::fromJson(json_text.toUtf8()).object().value("data").toArray();
    this->items = items;

    // Get current tab
    QListWidget * list = ui->tabWidget->widget(ui->tabWidget->currentIndex())->findChild<QListWidget*>();
    list->clear();

    // Json Document
    for(int i = 0; i < items.count(); i++) {
        // Get data
        QString title = items.at(i).toObject().value("title").toString();
        QString uuid = items.at(i).toObject().value("uuid").toString();
        QString description = items.at(i).toObject().value("description").toString();

        // Add title
        QListWidgetItem * item_widget = new QListWidgetItem;
        item_widget->setData(Qt::UserRole, i);
        item_widget->setText('"' + title + '"\n'); // + "\n\n" + description

        list->addItem(item_widget);
    }
}

void MainWindow::linkClicked(QListWidgetItem * item)
{
    // Get current tab
    QWidget * tab = ui->tabWidget->widget(ui->tabWidget->currentIndex());

    // Get text browser
    QTextBrowser * browser = tab->findChild<QTextBrowser*>();

    // Get URL
    auto item_object = this->items.at(item->data(Qt::UserRole).toInt()).toObject();

    // Set text to text browser
    browser->setHtml("<h2>" + item_object.value("title").toString() + "</h2>" + "<hr><br>" + item_object.value("html").toString());

    // Show message
    ui->statusBar->showMessage("✔️ Loaded successfully.", 1500);
}

void MainWindow::currentTabChanged(int index)
{
    // Get widget
    QWidget * widget = ui->tabWidget->widget(index);

    // Load from API
    MainWindow::requestTo(QUrl("https://tridectet.ir/api/" + widget->objectName().toLower()));
}
