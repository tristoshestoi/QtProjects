/**
 * @file server.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>, Ivahniuk Valery <topkekhs1337@gmail.com>
 * @brief Содержит объявление класса Server
 */
#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QtNetwork>
#include <QVector>
#include <QFile>
#include <QMap>
#include <QDebug>
#include <vector>

class Server : public QObject
{
    Q_OBJECT
private:
    QTcpServer* tcpServer;
    QVector <QString> last_messages;
    QMap<QTcpSocket*, QString> clients_map;

public:
    /**
     * @brief Server Конструктор класса Server
     */
    explicit Server(QObject *parent = nullptr);

private slots:
    /**
     * @brief connectUser Метод для подключения клиента
     */
    void connectUser();

    /**
     * @brief runClientAction Метод для обработки сообщений пользователей
     */
    void runClientAction();

    /**
     * @brief save_last_messages Метод для записи последний 10 сообщений в файл
     * @param message Текст сообщения
     */
    void save_last_messages(QString message);
};

#endif // SERVER_H
