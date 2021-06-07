#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ActiveQt\QAxObject>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QTimer>
#include <QDebug>
#include <QSqlDatabase>
#include <QDateTimeAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace QtCharts;


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase db;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString cts;
    QChart *chart;
    QChartView *view;
    QLineSeries *series;
    QAxObject* sheet;
    int count; // Получаем количество листов




    QDateTimeAxis *createXAxis();
    QValueAxis *createYAxis();
    QLineSeries *createSeries();
    void createChart();
    void createChartView();
    void init();

    void updateActiveFlag();
    void filterTags();
    void search();
    void excelImport();
    void setText(const QString &text);
        void setAnchor(QPointF point);
        void updateGeometry();

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
        QString m_text;
            QRectF m_textRect;
            QRectF m_rect;
            QPointF m_anchor;
            QFont m_font;
            QChart *m_chart;


private slots:


    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
