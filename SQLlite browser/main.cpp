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


    MainWindow w;
    w.show();

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("/data/lenoblles.sqlite");
//    db.open();

//    QTableView view;
//    QSqlTableModel table;
//    table.setTable("zone_info");
//    table.select();

//    QSqlQueryModel query;
//    query.setQuery("SELECT * FROM zone_kml WHERE zone_id = 17");


//    view.setModel(&query);
//    view.show();

    return a.exec();
}
