#include "downloader.h"
#include <QtNetwork/QtNetwork>
#include <QFile>
#include <QMessageBox>

Downloader::Downloader(QObject *parent) : QObject(parent)
{

}

void Downloader::downloadImage(QString link)
{

    QNetworkAccessManager manager;


    QUrl url = QUrl(link);
    QNetworkRequest requestMy(url);

    QNetworkReply *response = manager.get(requestMy);

    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));

    qDebug() << response->error();
    qDebug() << response->errorString();
    if (response->error() != QNetworkReply::NoError) {
        QMessageBox msgBox;
        msgBox.setText(response->errorString());
        msgBox.exec();
        msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
        return;
    }

    QString fileName = "image.jpg";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(response->readAll());
    file.close();
    emit downloadComplete(fileName);
}
