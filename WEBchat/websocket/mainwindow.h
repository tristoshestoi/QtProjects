
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QObject>
#include <QtNetwork>
#include <QVector>
#include <QFile>
#include <QMap>
#include <QDebug>
#include <vector>
#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QPushButton>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);


    ~MainWindow();

private:
    QSqlDatabase db;
    Ui::MainWindow *ui;
    QWebSocketServer *server;
    QSystemTrayIcon  * trayIcon;
    QVector <QString> last_messages;
    QMap<QWebSocket*, QString> clients_map;
    int port;
    int flag=0;

protected:

    void closeEvent(QCloseEvent * event);

private slots:

    void connectUser();

    void exeuteclac(QString message);

    void savemsg(QString message);

    void save_settings();

    void message(QString message);

    void new_connection();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};
#endif // MAINWINDOW_H
