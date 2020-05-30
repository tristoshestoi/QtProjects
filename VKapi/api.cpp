#include "api.h"
#include <QtNetwork/QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QEventLoop>

api::api(QObject *parent) : QObject(parent)
{

}

void api::user_get()
{
    MainWindow mainwindow;

    QJsonObject json;
    QJsonDocument jsonDoc(json);

    QUrl url = QUrl("https://api.vk.com/method/users.get?user_ids=" + mainwindow.SetID() + "&fields=bdate&access_token=bcc904c1bcc904c1bcc904c12abca6e30ebbcc9bcc904c1e29d09f23b28c14396cbe3a4&v=5.103");
    QNetworkRequest request(url);
    QNetworkAccessManager manager;
    qDebug() << url;

    QByteArray sendData = jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkReply *response = manager.post(request, sendData);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));
    qDebug() << json;
}
//QUrl url("https://api.vk.com/method/users.get");
