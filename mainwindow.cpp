#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    ui->dateEdit->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    exit(0);
}

void MainWindow::getUrl(QNetworkReply *reply)
{
    QString otvet;
    QByteArray buf;
    QFile fileOut("..\\tmp\\tmp.xml");

    if(!fileOut.open(QIODevice::WriteOnly))
    {
        qDebug() << "File open error";
        ui->label_3->setText("File open error");
    }

    ui->plainTextEdit->clear();

    switch (reply->error())
    {
    case 0:
        buf = reply->readAll();
        otvet = QString::fromUtf8(buf);
        fileOut.write(buf);
        ui->plainTextEdit->insertPlainText(otvet);
        break;
    default:
        ui->plainTextEdit->insertPlainText("Ошибка загрузки");
        break;
    }
    fileOut.close();
    reply->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    QString curday = QDate::currentDate().toString("dd");
    QString curmon = QDate::currentDate().toString("MM");
    QString curyear = QDate::currentDate().toString("yyyy");
    QString source_url = SOURCE_URL+curday+"/"+curmon+"/"+curyear;
    this->connect_to(source_url);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString selday = ui->dateEdit->date().toString("dd");
    QString selmon = ui->dateEdit->date().toString("MM");
    QString selyear = ui->dateEdit->date().toString("yyyy");
    QString source_url = SOURCE_URL+selday+"/"+selmon+"/"+selyear;
    this->connect_to(source_url);
}

void MainWindow::connect_to(QString &source_url){
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl(source_url)));
    ui->lineEdit->clear();
    ui->lineEdit->setText(source_url);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getUrl(QNetworkReply*)));
}

