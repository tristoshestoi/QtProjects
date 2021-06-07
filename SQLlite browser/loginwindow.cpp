#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle ("Вход");
    setWindowIcon(QIcon("logo.png"));

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_2_clicked()
{
    this->close();
}

void LoginWindow::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSqlQuery getAll;
        db.setHostName("localhost");
        db.setDatabaseName("vodokanal");
        db.setUserName("root");
        db.setPassword("1234");
        bool ok = db.open();
        this->setFixedSize(this->width(), this->height());

    if (!ok) {

        QMessageBox::critical(nullptr, "Ошибка!", "Невозможно подключиться к базе данных!");

    }
    else{
    getAll.exec("select * from user");
    while (getAll.next()) {
       if (getAll.value(1).toString() == ui->lineEdit->text() && getAll.value(2).toString()==ui->lineEdit_2->text()){
               MainWindow *w = new MainWindow();
               this->close();
               w->show();

       }
       else
           QMessageBox::critical(nullptr, "Ошибка!", "Неправильно введен логин или пароль!");
    }
    }
}
