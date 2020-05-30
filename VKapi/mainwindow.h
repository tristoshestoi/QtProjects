/**
 * @file mainwindow.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>
 * @brief Содержит объявление класса MainWindow
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QEventLoop>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString id;
    QString photo;
    QString filename;
    QString dbate;
    QString first_name="";
    QString last_name;
    QString nickname;
    QString id_friends;
    int check_id=-1;

    Ui::MainWindow *ui;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void getID();


    void user_get();


    void friends_get();


    void photo_get();


    void Show();


    void Delete();

signals:

    void downloadComplete(QString fileName);
};
#endif // MAINWINDOW_H
