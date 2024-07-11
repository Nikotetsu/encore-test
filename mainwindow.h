#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SOURCE_URL "https://cbr.ru/scripts/XML_daily.asp?date_req="

#include <QMainWindow>
#include "QtNetwork/qnetworkaccessmanager.h"
#include "QtNetwork/qnetworkreply.h"
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();
    void getUrl(QNetworkReply *reply);
    void connect_to(QString &source_url);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
