/**
 * @file server.cpp
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>, Ivahniuk Valery <topkekhs1337@gmail.com>
 * @brief Содержит реализацию класса Server
 */
#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &Server::connectUser);
    if (tcpServer->listen(QHostAddress::Any, 1337)) {
        qInfo() << "Server started";
    } else {
        qWarning() << "Unable to start server";
    }
}

void Server::connectUser()
{
    QTcpSocket* socket = tcpServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead,
            this, &Server::runClientAction);
    connect(socket,  &QAbstractSocket::stateChanged, this, [&](QAbstractSocket::SocketState state){
        if(state==QAbstractSocket::SocketState::UnconnectedState){
            int i=0;
            foreach(QTcpSocket* key,clients_map.keys()){
               if(key->socketDescriptor() == -1){
                   clients_map.erase(clients_map.begin() + i);
               }
               i++;
            }
            foreach(QTcpSocket* key,clients_map.keys()){
               QTextStream messageStream (key);
               messageStream << endl <<"Someone left the chat!";
            }
        }
    });

    QFile file("last_messages.txt");
    if (file.open(QIODevice::ReadOnly)){
        qDebug()<<"File is open!";
            while(!file.atEnd())
            {
                QTextStream messageStream (socket);
                messageStream <<file.readLine();
            }
        file.close();
    } else {
        qDebug()<< "File is not open!";
    }
    clients_map.insert(socket,"");
    foreach(QTcpSocket* key,clients_map.keys()){
       QTextStream messageStream (key);
       messageStream << endl <<"We have a new user!";
    }
}

void Server::runClientAction()
{
    QTcpSocket* clientSocket = (QTcpSocket*) sender();
    QTextStream messageStream (clientSocket);

    QString message;
    message = messageStream.readLine(100);
    qInfo() << "Get message: " << message;

    if(message[0]!='#'){
        int k=0;
        foreach(QTcpSocket* key,clients_map.keys()){
            if(clients_map.value(key) == message){
                k++;
            }
        }
        if(k>0){
            messageStream << 1;
        } else {
            messageStream << 0;
            int i = 0;
            foreach(QTcpSocket* key,clients_map.keys()){
               if(key == clientSocket){
                   clients_map.erase(clients_map.begin() + i);
                   clients_map.insert(clientSocket, message);
               }
               i++;
            }
        }
    } else {
        save_last_messages(message);
        foreach(QTcpSocket* key,clients_map.keys()){
           QTextStream messageStream (key);
           messageStream << message;
        }
    }
}

void Server::save_last_messages(QString message){
    message.remove(0, 7);
    if(last_messages.size()==10){
        last_messages.pop_front();
        last_messages.push_back(message);
    } else {
        last_messages.push_back(message);
    }
    QFile file("last_messages.txt");
    if (file.open(QIODevice::WriteOnly)){
        qDebug()<<"File is open!";
        for(int i=0; i<last_messages.size();i++){
            file.write(last_messages[i].toUtf8());
            if(i!=last_messages.size()-1)
                file.write("\n");
        }
        file.close();
    } else {
        qDebug()<< "File is not open!";
    }
}
