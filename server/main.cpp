/**
 * @file main.cpp
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>, Ivahniuk Valery <topkekhs1337@gmail.com>
 * @brief Содержит функцию main.cpp проекта server
 */
#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server serv;
    return a.exec();
}

