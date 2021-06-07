#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QMessageBox>



struct Tag{
 int id;
 QString name;
 bool isActive;
 QString desc;
 int dataType;
};
int cursel;
QVector<Tag> tagList;
QVector<long> intValue;
QVector<double> floatValue;
QVector<qreal> dateValue;
int graphTicks;
bool flag = false;
int filter = 1;
QSqlQueryModel *model = new QSqlQueryModel;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    setWindowIcon(QIcon("logo.png"));
    ui->widget->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("vodokanal");
        db.setUserName("root");
        db.setPassword("1234");
        bool ok = db.open();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    if (!ok) {
        qDebug() << "Не можем открыть БД";
        QMessageBox::critical(nullptr, "Ошибка!", "Невозможно подключиться к базе данных!");

    }
    db.open();
     ui->label->setText("Тег не выбран");
     ui->tableView->setVisible(false);
     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QString string;
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &MainWindow::init);
     connect(ui->checkBox, &QCheckBox::clicked, this, &MainWindow::updateActiveFlag);
     connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::filterTags);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::search);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::excelImport);

    ui->pushButton_3->setEnabled(false);
    QSqlQuery query;
       QSqlQuery upd;
       upd.exec("VACUUM");

//       ui->listWidget->addItem(new QListWidgetItem();
       query.exec("SELECT * FROM TAG;");
       while(query.next()){
           tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
           ui->listWidget->addItem(query.value(3).toString());
           qDebug()<< query.value(3).toString();
       }
       qDebug() << ui->listWidget->currentRow();



}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}




void MainWindow::init(){

    ui->pushButton_3->setEnabled(true);
    int i = 0;
    qDebug() << ui->listWidget->currentIndex().row();
    if(ui->listWidget->currentRow()!=-1){

    cursel = tagList[ui->listWidget->currentIndex().row()].id;


    qDebug() << tagList[ui->listWidget->currentRow()].isActive << " adada " << tagList[ui->listWidget->currentRow()].name;

qDebug() << tagList[ui->listWidget->currentRow()].isActive << " adada " << tagList[ui->listWidget->currentRow()].name;

    QSqlQuery getTag;

    getTag.prepare("select tagValue, TimeStamp, ConnectionQuality from techData where TagID = :id order by TimeStamp desc");

    getTag.bindValue(":id", tagList[ui->listWidget->currentIndex().row()].id);

    getTag.exec();

    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    int dataType = tagList[ui->listWidget->currentIndex().row()].dataType;

    if (!getTag.first())
    {
        ui->widget->setVisible(false);
        ui->tableView->setVisible(false);
         ui->label->setVisible(true);
         ui->label->setText("Данных нет");
    }
    else if (dataType >21 || dataType==8 || dataType==7 || dataType==8197 || dataType==8197){
        ui->widget->setVisible(false);
        ui->label->setVisible(true);
        ui->tableView->setVisible(true);
        ui->label->setText("Данный тип данных не поддерживает построение графиков");
    }
    else
    {
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->widget->setVisible(false);
        chart = new QChart();
        view = new QChartView(ui->widget);
        QSqlQuery getGraph, getValues;
        getGraph.prepare("select tagValue, TimeStamp, ConnectionQuality from techData where TagID = :id and ConnectionQuality ='Good' and timestampdiff(HOUR, TimeStamp, CURRENT_TIMESTAMP)<36 order by TimeStamp limit 36");
         getValues.prepare("select max(cast(tagValue as DECIMAL(12, 2))), min(cast(tagValue as DECIMAL(12, 2))), avg(cast(tagValue as DECIMAL(12, 2))) from (select tagValue, TimeStamp, ConnectionQuality from techData where TagID = :id and ConnectionQuality ='Good' and timestampdiff(HOUR, TimeStamp, CURRENT_TIMESTAMP)<24 order by TimeStamp limit 36) as temp;");
        getGraph.bindValue(":id", tagList[ui->listWidget->currentIndex().row()].id);
         getValues.bindValue(":id", tagList[ui->listWidget->currentIndex().row()].id);
        getValues.exec();
        getGraph.exec();
        ui->tableView->setVisible(true);
        ui->label->setVisible(false);
        while(getValues.next()){
        ui->label_2->setText("Максимальное: " + getValues.value(0).toString());
        ui->label_3->setText("Минимальное: " + getValues.value(1).toString());
        ui->label_4->setText("Среднее: " + getValues.value(2).toString());
        }
        while (getGraph.next()) {
            i++;
            QDateTime dateTime;
            dateTime = QDateTime::fromString(getGraph.value(1).toString(), Qt::ISODate);
            dateValue.push_back(dateTime.toMSecsSinceEpoch());
            if(dataType==4 || dataType==5 ){
                floatValue.push_back(getGraph.value(0).toFloat());


            }
            else
            intValue.push_back(getGraph.value(0).toInt());

        }

        graphTicks = i;
        this->createChart();
        this->createXAxis();
        this->createYAxis();
        this->createChartView();
        ui->widget->setVisible(true);
    }
        model->setQuery(getTag);
        model->setHeaderData(0, Qt::Horizontal, tr("Значение"));
        model->setHeaderData(1, Qt::Horizontal, tr("Дата и время"));
        model->setHeaderData(2, Qt::Horizontal, tr("Качество соединения"));
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(2, 150); 
        ui->checkBox->setChecked(tagList[ui->listWidget->currentRow()].isActive);

    }

}



void MainWindow::createChart()
{
    series = new QLineSeries;
    this->createSeries();
    chart->removeAllSeries();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
}

void MainWindow::createChartView()
{
    view->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setVisible(false);
    view->setChart(chart);
    view->resize(ui->widget->size());
}
QDateTimeAxis* MainWindow::createXAxis()
{
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("yyyy-MM-dd hh:mm:ss");
    axisX->setTitleText("Date");
    axisX->setLabelsAngle(90);
    axisX->setTickCount(graphTicks);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    return axisX;
}

QValueAxis* MainWindow::createYAxis()
{
    QValueAxis *axisY = new QValueAxis();
    if(tagList[ui->listWidget->currentRow()].dataType==4){
        axisY->setLabelFormat("%.2f");

    }
    else
    axisY->setLabelFormat("%i");
    axisY->setTickCount(graphTicks/2);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    return axisY;
}



QLineSeries* MainWindow::createSeries()
{

      series->clear();
        if(tagList[ui->listWidget->currentRow()].dataType==4)
            for (int i = 0; i < floatValue.length(); i++){
            series->append(dateValue[i], floatValue[i]);
            }
        else
      for (int i = 0; i < intValue.length(); i++){
      series->append(dateValue[i], intValue[i]);
      }
      floatValue.clear();
      dateValue.clear();
      intValue.clear();
    return series;
}





void MainWindow::updateActiveFlag()
{
    QSqlQuery update;

    if (ui->checkBox->checkState()==Qt::Checked){
        update.prepare("UPDATE `vodokanal`.`tag` SET `isActive` = '1' WHERE (id = :id )");
        update.bindValue(":id", tagList[ui->listWidget->currentRow()].id);
        update.exec();

        tagList[ui->listWidget->currentRow()].isActive=true;
    }
    else {
        update.prepare("UPDATE `vodokanal`.`tag` SET `isActive` = '0' WHERE (id = :id )");
        update.bindValue(":id", tagList[ui->listWidget->currentRow()].id);
        update.exec();

        tagList[ui->listWidget->currentRow()].isActive=false;


    }
}

void MainWindow::filterTags()
{

    tagList.clear();
    ui->listWidget->clear();
    QSqlQuery query;
       QSqlQuery upd;
       upd.exec("VACUUM");

    switch(filter){

    case 1: {
          query.exec("SELECT * FROM TAG where isActive = 1;");
        while(query.next()){
        tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
        ui->listWidget->addItem(query.value(3).toString());
        }
    filter=2;
    ui->pushButton_2->setText("Фильтр: неактивные");
    }
        break;
    case 2:{
          query.exec("SELECT * FROM TAG where isActive = 0;");
        while(query.next()){
        tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
        ui->listWidget->addItem(query.value(3).toString());
    }

        filter=3;
        ui->pushButton_2->setText("Фильтр: нет");
    }
        break;
    case 3:{ query.exec("SELECT * FROM TAG;");
        while(query.next()){
        tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
        ui->listWidget->addItem(query.value(3).toString());
    }
        filter=1;
        ui->pushButton_2->setText("Фильтр: активные");
    }
        break;
    }
ui->listWidget->setCurrentRow(-1);

}

void MainWindow::search()
{
 ui->listWidget->clear();

    QSqlQuery query;
       QSqlQuery upd;
       upd.exec("VACUUM");



    QString search = ui->lineEdit->text();
    if(search.size()==0){
         tagList.clear();
        switch(filter){

        case 2: {
            tagList.clear();
              query.exec("SELECT * FROM TAG where isActive = 1;");
            while(query.next()){
            tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
            ui->listWidget->addItem(query.value(3).toString());
            }

        }
            break;
        case 3:{
              query.exec("SELECT * FROM TAG where isActive = 0;");
            while(query.next()){
            tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
            ui->listWidget->addItem(query.value(3).toString());
        }



        }
            break;
        case 1:{ query.exec("SELECT * FROM TAG;");
            while(query.next()){
            tagList.push_back(Tag {query.value(0).toInt(), query.value(3).toString(), query.value(1).toBool(), query.value(2).toString(), query.value(4).toInt()});
            ui->listWidget->addItem(query.value(3).toString());
        }

        }
            break;
        }

    }
    QMutableVectorIterator<Tag> i(tagList);
    while(i.hasNext()){
        if (!i.next().name.contains(search, Qt::CaseInsensitive))
            i.remove();
    }

    if(search.size()!=0){
    for(int i = 0; i<tagList.size(); i++){
         ui->listWidget->addItem(tagList[i].name);
      }
    }





}

void MainWindow::excelImport()
{

    if(cursel-1!=-1){
    QString textData;
    for (QListWidgetItem* i : ui->listWidget->selectedItems()) {
        QSqlQuery getAll;
        getAll.prepare("select tagValue, TimeStamp, ConnectionQuality from techData, tag where tagName = :id and TagID = id  order by TimeStamp desc");
        getAll.bindValue(":id", i->text());
        getAll.exec();
    QSqlQueryModel model2;
        model2.setQuery(getAll);

    int rows = model2.rowCount();
    int columns = model2.columnCount();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model2.data(model2.index(i,j)).toString().left(19);
                if(j==1)
                    textData.replace("T", " ");

                textData += "; ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }
    QFile csvFile(i->text() + ".csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
    }
    }

}




void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(nullptr, "Связь с разработчиком", "Для связи с разработчиком напишите на почту: \ntopkekhs1337@gmail.com");
}
