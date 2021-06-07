#include "loginwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQueryModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    //MainWindow w;

    w.show();


    return a.exec();
}
