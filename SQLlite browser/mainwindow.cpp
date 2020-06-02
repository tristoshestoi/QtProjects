#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile check("db.sqlite");
    if (check.exists()==0) {                        //Создание и заполнение БД если ее не существует
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("db.sqlite");
        db.open();
        QSqlQuery create1;
        create1.exec("CREATE TABLE car "
                     "(id	INTEGER NOT NULL, "
                     "car_make	TEXT NOT NULL, "
                     "model	TEXT NOT NULL)");
        QSqlQuery create2;
        create2.exec("create table person "
                     "(id integer NOT NULL, "
                     "firstname varchar(20) NOT NULL, "
                     "lastname varchar(30 )NOT NULL, "
                     "age integer NOT NULL)");
        QSqlQuery queryInsert;
        queryInsert.prepare(
                    "INSERT INTO person  \
                    (id, firstname, lastname, age) \
                    VALUES (:id, :firstname, :lastname, :age);\
                ");
        queryInsert.bindValue(":id", 1);
        queryInsert.bindValue(":firstname", "Сергей");
        queryInsert.bindValue(":lastname", "Иванов");
        queryInsert.bindValue(":age", 19);
        queryInsert.exec();

        QSqlQuery queryInsert2;
        queryInsert2.prepare(
                    "INSERT INTO car \
        (id, car_make, model) \
        VALUES (:id, :car_make, :model);\
        ");

            queryInsert2.bindValue(":id", 1);
            queryInsert2.bindValue(":car_make", "Toyota");
            queryInsert2.bindValue(":model", "Mark 2");
            queryInsert2.exec();



    }

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("db.sqlite");
    if (!db.open()) {
        qDebug() << "Не можем открыть БД";
        return;

    }
    db.open();     //Конструктор начального окна
    QSqlQuery query;
    QSqlQuery total;
    query.exec("SELECT * FROM person where rowid = 1;");
    while(query.next()){
    ui->lineEdit->setText(query.value(0).toString());
    ui->lineEdit_2->setText(query.value(1).toString());
    ui->lineEdit_3->setText(query.value(2).toString());
    ui->lineEdit_4->setText(query.value(3).toString());
    }
    total.exec("select count (*) from person;");
    total.next();
    totaltab = total.value(0).toInt();
    qDebug() << totaltab;
    curtab = 1;
    ui->lineEdit_5->setText(QString::number(curtab) + "/" + QString::number(totaltab));
    cts = "person";

}
MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}


void MainWindow::output(){ //Вывод данных из таблиц в LineEdit
    ui->lineEdit_5->setText(QString::number(curtab) + "/" + QString::number(ctotal()));
    QSqlQuery query;
    QSqlQuery upd;
    upd.exec("VACUUM");
    QString num = QString::number(curtab);
    query.exec("SELECT * FROM " + cts + " where rowid =" + num + ";");
    while(query.next()){
    ui->lineEdit->setText(query.value(0).toString());
    ui->lineEdit_2->setText(query.value(1).toString());
    ui->lineEdit_3->setText(query.value(2).toString());
    ui->lineEdit_4->setText(query.value(3).toString());
    }

}

void MainWindow::on_pushButton_5_clicked() //Переход на запись вперед
{
    if(curtab<ctotal()){
        curtab++;
       output();
    }
}

void MainWindow::on_pushButton_4_clicked() //Переход на запись назад
{
    if(curtab>1){
        curtab--;
        output();
        }
    }


void MainWindow::on_radioButton_2_clicked() //Выбор таблицы car
{
    curtab = 1;
    cts = "car";
    ui->lineEdit_4->hide();
    ui->label_4->hide();
    ui->label_2->setText("Марка");
    ui->label_3->setText("Модель");
    output();

}

void MainWindow::on_radioButton_clicked() //Выбор таблицы person
{
    curtab = 1;
    cts = "person";
    ui->lineEdit_4->show();
    ui->label_4->show();
    ui->label_2->setText("Имя");
    ui->label_3->setText("Фамилия");

    output();
}

void MainWindow::on_pushButton_3_clicked() //Удаление записи из таблицы
{
    QSqlQuery query;
    QString num = QString::number(curtab);
    query.exec("DELETE FROM " + cts + " where rowid =" + num + ";");
    curtab--;
    output();
}

int MainWindow::ctotal(){ //Подсчет общего количества записей
    int count;
    QSqlQuery ltotal;
    ltotal.exec("select count (*) from " + cts + ";");
    ltotal.next();
    qDebug() <<ltotal.value(0).toInt();
    count = ltotal.value(0).toInt();
    return count;
}


void MainWindow::on_pushButton_clicked() //Добавление записей
{
    if (cts == "car"){ //Добавление записей в таблицу car
    QSqlQuery queryInsert;
    queryInsert.prepare(
                "INSERT INTO " + cts + " \
    (id, car_make, model) \
    VALUES (:id, :car_make, :model);\
    ");

        queryInsert.bindValue(":id", ui->lineEdit->text().toInt());
        queryInsert.bindValue(":car_make", ui->lineEdit_2->text());
        queryInsert.bindValue(":model", ui->lineEdit_3->text());
        queryInsert.exec();
        output();

    }
    else {
        QSqlQuery queryInsert; //Добавление записей в таблицу person
        queryInsert.prepare(
                    "INSERT INTO " + cts + " \
        (id, firstname, lastname, age) \
        VALUES (:id, :firstname, :lastname, :age);\
        ");
            queryInsert.bindValue(":id", ui->lineEdit->text().toInt());
            queryInsert.bindValue(":firstname", ui->lineEdit_2->text());
            queryInsert.bindValue(":lastname", ui->lineEdit_3->text());
            queryInsert.bindValue(":age", ui->lineEdit_4->text().toInt());
            queryInsert.exec();
            output();


    }
}

void MainWindow::on_pushButton_6_clicked() // Создание пустых строк для добавления записей в таблицу
{

     totaltab=ctotal();
     curtab=totaltab+1;
     totaltab++;
     qDebug() << totaltab;
     ui->lineEdit_5->setText(QString::number(curtab) + "/" + QString::number(totaltab));
     ui->lineEdit->setText("");
     ui->lineEdit_2->setText("");
     ui->lineEdit_3->setText("");
     ui->lineEdit_4->setText("");

}

void MainWindow::on_pushButton_2_clicked() //Обновление данных, полученных из LineEdit
{
    if (cts == "car"){                     //Для таблицы car
    QSqlQuery queryInsert;
    QString num = QString::number(curtab);
    queryInsert.prepare( "UPDATE " + cts + " SET id = :id, car_make = :car_make, model = :model WHERE rowid = " + num + ";");

        queryInsert.bindValue(":id", ui->lineEdit->text().toInt());
        queryInsert.bindValue(":car_make", ui->lineEdit_2->text());
        queryInsert.bindValue(":model", ui->lineEdit_3->text());
        queryInsert.exec();
        output();

    }
    else {                                  //Для таблицы person
        QSqlQuery queryInsert;
        QString num = QString::number(curtab);
        queryInsert.prepare(
                    "UPDATE " + cts + " SET id = :id, firstname = :firstname, lastname = :lastname, age = :age WHERE rowid = " + num + ";");
            queryInsert.bindValue(":id", ui->lineEdit->text().toInt());
            queryInsert.bindValue(":firstname", ui->lineEdit_2->text());
            queryInsert.bindValue(":lastname", ui->lineEdit_3->text());
            queryInsert.bindValue(":age", ui->lineEdit_4->text().toInt());
            queryInsert.exec();
            output();


    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("SELECT * from person where age > 18");
    ui->tableView->setModel(setquery1);
}

void MainWindow::on_pushButton_8_clicked()
{
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("select * from car");
    ui->tableView->setModel(setquery1);
}

void MainWindow::on_pushButton_9_clicked()
{
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("select * from person");
    ui->tableView->setModel(setquery1);
}
