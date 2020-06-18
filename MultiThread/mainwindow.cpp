#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPointF>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart->addSeries(series);
    chart->legend()->hide();
    ui->gridLayout->addWidget(chartview);

            axisX->setLabelFormat("%i");
            axisX->setTickCount(500);
            axisX->setMax(500);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            axisY->setLabelFormat("%i");
            axisY->setTickCount(8);
            axisY->setRange(-500000, 500000);
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

    chartview->setChart(chart);
    thread = new QThread(this);
    connect(thread, &QThread::started,[&](){
        QTimer *timer = new QTimer;
        timer->moveToThread(thread);
        timer->setInterval(1000);
        connect(timer, &QTimer::timeout,[&](){
            auto item = arr->average(arr->returnarray());
            series->clear();
            for (int i = 0; i < 500; ++i){
                      *series << QPointF(i,item[i]);
              }
        });
        timer->start();
    });

    connect(arr, &QThread::started,[&](){
        thread->start();
    });
    connect(arr, &QThread::finished,[&](){
        thread->terminate();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->text() == "Sort"){

       arr->start();

        ui->pushButton_2->setText("Stop sorting");
    } else {
        arr->terminate();

        ui->pushButton_2->setText("Sorting stopped");
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (thread->isRunning()){
        thread->exit();
    }
    this->close();
}
