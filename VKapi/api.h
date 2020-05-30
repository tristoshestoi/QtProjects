#ifndef API_H
#define API_H

#include <QObject>
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


class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(QObject *parent = nullptr);
    QString id;
    QString photo;
    QString filename;
    QString dbate;
    QString first_name="";
    QString last_name;
    QString nickname;
    QString id_friends;
    int check_id=-1;


public slots:
    /**
     * @brief user_get Метод для получения информации о пользователи
     */
    void user_get();

    /**
     * @brief get_f Метод для получения списка друзей пользователя
     */
    void get_f();

    /**
     * @brief photo_get Метод для получения фото пользователя
     */
    void photo_get();
signals:
    void downloadComplete(QString fileName);

};

#endif // API_H
