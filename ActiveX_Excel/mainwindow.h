#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ActiveQt\QAxObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<QVariant> cellsList;
    // список строк
    QList<QVariant> rowsList;
    QAxObject* sheet;
    QAxObject *mExcel; // Создаём подключение к Excel
    QAxObject *workbooks; // Получаем рабочие книги
    QAxObject *workbook; //Открываем файл (файл должен быть)
    QAxObject *mSheets; // Получаем все листы
    int count; // Получаем количество листов
    QAxObject *page;
    QAxObject *rows;
    QAxObject *columns;

private slots:

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
