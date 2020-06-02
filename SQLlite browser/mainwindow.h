#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase db;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void output();
    int ctotal();
    int curtab;
    int totaltab;
    int tabflag;
    QString cts;


private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
