/**
 * @file main.cpp
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>, Ivahniuk Valery <topkekhs1337@gmail.com>
 * @brief Содержит функцию main.cpp проекта client
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
