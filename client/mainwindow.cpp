/**
 * @file mainwindow.cpp
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>, Ivahniuk Valery <topkekhs1337@gmail.com>
 * @brief Содержит реализацию класса MainWindow
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socketClient = new QTcpSocket(this);
    socketClient->connectToHost(
                "localhost",
                1337,
                QTcpSocket::ReadWrite
                );
    if(socketClient->waitForConnected(30000)) {
        qInfo() << "Connected!";
        qInfo() << socketClient->peerAddress();
    } else{
        error("Сервер недоступен!");
    }
    connect(socketClient, &QTcpSocket::readyRead,
            this, &MainWindow::readSocket);
    connect(ui->pushButton_2, &QPushButton::clicked,
            this, &MainWindow::get_nick);
    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::execButtonAction);
    connect(ui->pushButton_3, &QPushButton::clicked,[&](){ socketClient->disconnectFromHost();
                                                           dis_flag = 1;});
}

void MainWindow::get_nick(){
    spare_nick = ui->lineEdit_2->text();
    colour = getRandomColor();
    socketClient->write(spare_nick.toUtf8());
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::execButtonAction(){
    if(dis_flag==0){
        socketClient->write((colour+"<"+nick+"> "+ui->lineEdit->text()).toUtf8());
        qDebug()<<ui->lineEdit->text();
    } else {
        error("Вы были отключены от сервера!");
    }
}

void MainWindow::readSocket()
{
    QString data = QString(socketClient->readAll());
    if(data=="1"){
        error("Такой ник уже существует!");
        spare_nick = nick;
    } else {
        nick = spare_nick;
        if(data=="0"){
            ui->lineEdit->setReadOnly(0);
            ui->pushButton->setEnabled(1);
        } else {
            if(data[0]=="#"){
               QString user_colour = data.mid(0, data.indexOf("<"));
               QString data_nick = data.mid(data.indexOf("<")+1, data.indexOf(">")-data.indexOf("<")-1);
               data.remove(0, data.indexOf(">")+1);
               ui->textEdit->append("");
               ui->textEdit->insertPlainText("<");
               ui->textEdit->insertHtml("<span style=\"color:"+user_colour+";\">"+data_nick+"</span>");
               ui->textEdit->insertHtml(">"+data);
            } else {
                if(!data.isEmpty()){
                    ui->textEdit->append(data);
                }
            }
        }
    }
}

void MainWindow::error(QString message){
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
    msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    return;
}

QString MainWindow::getRandomColor(){
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    QString letters = "0123456789ABCDEF";
    QString color = "#";
    for (int i = 0; i < 6; i++) {
       color += letters[qrand() % 16];
    }
    return color;
}
