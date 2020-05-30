/**
 * @file mainwindow.cpp
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>
 * @brief Содержит реализацию класса MainWindow
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->pushButton,
             &QPushButton::clicked,
             this,
             &MainWindow::getID );
    connect( ui->pushButton,
             &QPushButton::clicked,
             this,
             &MainWindow::user_get );
    connect( ui->pushButton,
             &QPushButton::clicked,
             this,
             &MainWindow::friends_get );
    connect( ui->pushButton,
             &QPushButton::clicked,
             this,
             &MainWindow::photo_get );
    connect( ui->pushButton,
             &QPushButton::clicked,
             this,
             &MainWindow::Show );
    connect( ui->pushButton,
             &QPushButton::clicked,
             this,
             &MainWindow::Delete );
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::getID(){
    id = ui->lineEdit->text();
    qDebug() << id;
}

void MainWindow::user_get(){
    QJsonObject json;
    QJsonDocument jsonDoc(json);

    QUrl url = QUrl("https://api.vk.com/method/users.get?user_ids=" + id + "&fields=bdate,nickname,photo_200&access_token=d29638ebdeb337d280166568d0e8b107af1869ca0f91b17f7de1a8b44ad6750392581e59dd8ec59975c9b&v=5.103");
    QNetworkRequest request(url);
    QNetworkAccessManager manager;
    QByteArray sendData = jsonDoc.toJson();
    QNetworkReply *response = manager.post(request, sendData);
    QEventLoop event;

    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));

    QJsonDocument reply = QJsonDocument::fromJson(response->readAll());
    QJsonObject jsonObject = reply.object();
    QJsonArray jsonArray = jsonObject["response"].toArray();
    qDebug() << reply;

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        dbate.append(obj["bdate"].toString());
        first_name.append(obj["first_name"].toString());
        check_id=obj["id"].toInt();
        last_name.append(obj["last_name"].toString());
        nickname.append(obj["nickname"].toString());
        photo.append(obj["photo_200"].toString());
    }

    if(dbate.isEmpty())
        dbate="не указана";
    if(nickname.isEmpty())
        nickname="не указан";
}

void MainWindow::friends_get(){
    QJsonObject json;
    QJsonDocument jsonDoc(json);

    QUrl url_friends = QUrl("https://api.vk.com/method/friends.get?user_id=" + id + "&access_token=d29638ebdeb337d280166568d0e8b107af1869ca0f91b17f7de1a8b44ad6750392581e59dd8ec59975c9b&v=5.103");
    QNetworkRequest request(url_friends);
    QNetworkAccessManager manager;

    QByteArray sendData = jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkReply *response = manager.post(request, sendData);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));

    QJsonDocument reply = QJsonDocument::fromJson(response->readAll());
    QJsonObject jsonObject = reply.object();
    QJsonObject s = reply["response"].toObject();
    QJsonArray jsonArray = s.value("items").toArray();
    QJsonDocument doc;
    doc.setArray(jsonArray);
    QString id(doc.toJson());
    id.remove('\n').remove('[').remove(']');
    if (id.isEmpty())
        id="Отсутствуют";
    id_friends=id;
    qDebug() <<id_friends;
}

void MainWindow::photo_get(){
    QNetworkAccessManager manager;
    QUrl url_photo = QUrl(photo);
    QNetworkRequest requestMy(url_photo);
    QNetworkReply *response = manager.get(requestMy);

    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));

    qDebug() << response->error();
    qDebug() << response->errorString();
    if (response->error() != QNetworkReply::NoError) {
        QMessageBox msgBox;

           msgBox.setText("пользователя не существует или его аккаунт удален");

        msgBox.exec();
        msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
        return;
    }
    filename = "image.jpg";
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(response->readAll());
    file.close();
    emit downloadComplete(filename);
}

void MainWindow::Show(){
    ui->label_text->setText("ФИО: "+first_name+" "+last_name+"\r\n"+"ник: "+nickname+"\r\n"+"дата рождения: "+dbate+"\r\n\n\n"+"фото: ");
    ui->label_friends->setText("список друзей:\r\n"+id_friends);
    if(check_id==-1){
        ui->label_text->clear();
        ui->label_friends->clear();
    }
    QPixmap img(filename);
    ui->label_photo->setPixmap(img);
    if(photo.isEmpty()){
        ui->label_photo->clear();
    }
}

void MainWindow::Delete(){
    check_id=-1;
    first_name.clear();
    last_name.clear();
    dbate.clear();
    nickname.clear();
    photo.clear();
    id_friends.clear();
}

