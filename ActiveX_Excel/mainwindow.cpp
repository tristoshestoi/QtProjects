#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mExcel = new QAxObject( "Excel.Application", this); // Создаём подключение к Excel
    workbooks = mExcel->querySubObject( "Workbooks" ); // Получаем рабочие книги
    workbook = workbooks->querySubObject( "Open(const QString&)", "C:\\excel\\work.xlsx" ); //Открываем файл (файл должен быть)
    mSheets = workbook->querySubObject( "Sheets" ); // Получаем все листы
    int count = mSheets->dynamicCall("Count()").toInt(); // Получаем количество листов
    page = mSheets->querySubObject("Item(const int&)",count);
    rows = page->querySubObject("Rows()");
    columns = page->querySubObject("Columns()");

    int rowCount = rows->dynamicCall("Count()").toInt();
    int columnCount = columns->dynamicCall("Count()").toInt();
    delete rows;
    delete columns;

    ui->table->setRowCount(rowCount/10000);
    ui->table->setColumnCount(columnCount/1000);
    for (int i = 0; i < ui->table->rowCount(); i++){
        for (int j = 0; j < ui->table->columnCount(); j++){
             QAxObject *cell = page->querySubObject("Cells(int,int)",i+1,j+1);
             int value = cell->dynamicCall("Value()").toInt();
             qDebug() << value;
            ui->table->setItem(i, j, new QTableWidgetItem(QString::number(value)));
        }

    }

    connect(ui->table,&QTableWidget::cellChanged,[&](const int& row,const int& column){
    QAxObject *value = page->querySubObject("Cells(int,int)",row+1,column+1);
    value->dynamicCall("SetValue(const QVariant&)",QVariant(ui->table->item(row,column)->text()));
    delete value;
    });
    // В блоке выше мы получаем все листы которые есть и запоминаем название последнего






}

MainWindow::~MainWindow()
{
    workbook->dynamicCall("Close()"); // Закрываем книгу
    mExcel->dynamicCall("Quit()"); // Закрываем Excel
    delete ui;
    delete sheet;
    delete mExcel; // Создаём подключение к Excel
    delete workbooks; // Получаем рабочие книги
    delete workbook; //Открываем файл (файл должен быть)
    delete mSheets; // Получаем все листы
    delete page;
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{
    workbook->dynamicCall("Save()"); // Сохраняем изменения в рабочей книге



}
