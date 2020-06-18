#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLogValueAxis>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <arraysort.h>
#include <QThread>
#include <QtDebug>
using namespace QtCharts;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChart *chart = new QChart();
    arraysort *arr = new arraysort(this);
    QChartView *chartview = new QChartView(this);
    QLineSeries *series = new QLineSeries();
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
     QThread *thread;






private slots:
     void on_pushButton_2_clicked();

     void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
