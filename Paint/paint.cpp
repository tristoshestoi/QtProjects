#include "paint.h"
#include "ui_paint.h"


Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);

    scene = new paintScene();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(100);          // Запускаем таймер
    menu->addAction(action);
    connect(action,&QAction::triggered,[&](){
        scene->clrchng("white");
    });
}

Paint::~Paint()
{
    delete ui;
}

void Paint::mousePressEvent(QMouseEvent * event){
    if (event->button() == Qt::RightButton){
        menu->exec(event->globalPos());
    }
}

void Paint::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);

}

void Paint::on_radioButton_clicked()
{
    scene->clrchng("red");
}

void Paint::on_radioButton_2_clicked()
{
    scene->clrchng("green");
}

void Paint::on_radioButton_3_clicked()
{
    scene->clrchng("blue");
}

void Paint::on_pushButton_3_clicked()
{
    scene->clear();

}



void Paint::on_pushButton_clicked()
{
   QString svpth = QFileDialog::getSaveFileName(this, tr("Save file"), "/untitled.bmp", tr("Images (*.png *.jpg *.bmp)"));
   QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
   image.fill(Qt::white);
   QPainter painter(&image);
   scene->render(&painter);
   image.save(svpth);

}

void Paint::on_pushButton_2_clicked()
{
    QString openpth = QFileDialog::getOpenFileName(0, tr("Open image"), "/", tr("Images (*.png *.jpg *.bmp)"));
    QPixmap image(openpth);
    scene->clear();
    scene->addPixmap(image);
    //QPixmap pixmap = ui->graphicsView->render()
}
