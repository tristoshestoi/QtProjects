#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);\
    videoWidget = new QVideoWidget(this);
    pmodel = new QStandardItemModel(this);
    ui->tableView->setModel(pmodel);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    player = new QMediaPlayer(videoWidget);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    ui->gridLayout->addWidget(videoWidget);
    player->setVideoOutput(videoWidget);
    connect(player, &QMediaPlayer::positionChanged, [&](qint64 time) {
        qDebug() << time;
        ui->label->setText(seconds(time).toString());
        ui->horizontalSlider->setSliderPosition(time);
 });
    connect(ui->horizontalSlider, &QAbstractSlider::sliderMoved,[&](float value) {
        player->setPosition(value);
 });

    setSettings("curpos");
    connect(player,&QMediaPlayer::currentMediaChanged,[&](const QMediaContent &content){
        player->setPosition(getpos(content));
    });

    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
           qDebug() << "duration = " << dur;
           ui->label_2->setText(seconds(dur).toString());
           totalt = dur;
           qDebug() << totalt;
           ui->horizontalSlider->setMaximum(dur);
           qDebug() << ui->horizontalSlider->maximum();

    });

    connect(ui->tableView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        savet(playlist->currentMedia());
        playlist->setCurrentIndex(index.row());
        player->setPosition(getpos(playlist->currentMedia()));
        player->play();
    });

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{
    player->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    player->pause();
}


void MainWindow::on_pushButton_3_clicked()
{
    qint64 tmp;
    QStringList file = QFileDialog::getOpenFileNames(this, tr("Select videos"), QString(), tr("Video Files (*.mp4 *.avi *.mkv)"));
    foreach (QString filePath, file) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QDir(filePath).dirName()));
            pmodel->appendRow(items);
            playlist->addMedia(QUrl(filePath));
        }


    player->setVideoOutput(videoWidget);
    tmp = player->duration();

    videoWidget->show();
    player->play();
}





void MainWindow::on_verticalSlider_valueChanged(int value)
{
    qDebug()<<value;
    player->setVolume(value);
}


void positionChanged(qint64 position){
    qDebug() << position;
}


QTime MainWindow::seconds(qint64 n){
    int nHours = (n/(60*60*1000));
    int nMinutes = ((n%(60*60*1000))/(60*1000));
    int nSeconds = ((n%(60*1000))/1000);
    return QTime(nHours, nMinutes, nSeconds);
}

void MainWindow::on_pushButton_4_clicked()
{
    savet(playlist->currentMedia());
    playlist->next();
    player->setPosition(getpos(playlist->currentMedia()));
}

void MainWindow::on_pushButton_5_clicked()
{
    savet(playlist->currentMedia());
    playlist->previous();
    player->setPosition(getpos(playlist->currentMedia()));

}

void MainWindow::on_pushButton_6_clicked()
{
    player->stop();
}

void MainWindow::savet(const QMediaContent& content){
    QSettings curpos("Vavai","Player");
    curpos.beginGroup("curpos");
    curpos.setValue(content.request().url().toString(),ui->horizontalSlider->value());
    curpos.endGroup();
}

void MainWindow::setSettings(const QString& group){
    QSettings curpos("Vavai","Player");
    if(group != "curpos"){return;}
    curpos.beginGroup(group);
    for (const auto& item : curpos.allKeys()){
        playlist->addMedia(QUrl(item));
        pmodel->appendRow(new QStandardItem(QDir(item).dirName()));

    }
    curpos.endGroup();
}

int MainWindow::getpos(const QMediaContent& content){
    QSettings curpos("Vavai","Player");
    curpos.beginGroup("curpos");
    auto smth = curpos.value(content.request().url().toString()).toInt();
    curpos.endGroup();
    return smth;
}

void MainWindow::on_pushButton_7_clicked()
{
    removeTimings(playlist->currentMedia());
    pmodel->removeRow(playlist->currentIndex());
    playlist->removeMedia(playlist->currentIndex());

}


void MainWindow::removeTimings(const QMediaContent& content){
    QSettings curpos("Vavai","Player");
    curpos.beginGroup("curpos");
    curpos.remove(content.request().url().toString());
    curpos.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event){
    savet(playlist->currentMedia());

}
