/**
 * @file mainwindow.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>, Ivahniuk Valery <topkekhs1337@gmail.com>
 * @brief Содержит объявление класса MainWindow
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtNetwork>
#include <QColor>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QTime>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString nick;
    QString spare_nick;
    int dis_flag=0;
    QString colour;

public:
    /**
     * @brief Конструктор класса MainWindow
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса MainWindow
     */
    ~MainWindow();

private slots:
    /**
     * @brief execButtonAction Метод для отправки сообщения на сервер
     */
    void execButtonAction();

    /**
     * @brief readSocket Метод для принятия сообщения от сервера
     */
    void readSocket();

    /**
     * @brief get_nick Метод для получения ника из lineEdit
     */
    void get_nick();

    /**
     * @brief error Метод для вывода ошибки
     * @param message Текст ошибки
     */
    void error(QString message);

    /**
     * @brief getRandomColor Метод для получени рандомного цвета
     * @return Цвет в HTML
     */
    QString getRandomColor();

private:
    QTcpSocket *socketClient;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
