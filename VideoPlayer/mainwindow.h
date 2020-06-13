#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QTime>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QMediaPlaylist *playlist;
    float totalt;
    QStandardItemModel *pmodel;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    int getpos(const QMediaContent& content);


    void on_verticalSlider_valueChanged(int value);
    QTime seconds(qint64 n);


    void savet(const QMediaContent& content);

    void setSettings(const QString& group);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void removeTimings(const QMediaContent& content);

    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
