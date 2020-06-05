#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtNetwork>
#include <QColor>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <QtWebSockets/QWebSocket>
#include <QIntValidator>


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

    void execButtonAction();


    void readSocket(QString message);


    void get_nick();

    void get_port();

    void error(QString message);


    QString getRandomColor();

private:
    QString nick;
    QString port;
    QString spare_nick;
    int dis_flag=0;
    int con_flag=0;
    QString colour;
    QWebSocket socketClient;
    QUrl url;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
