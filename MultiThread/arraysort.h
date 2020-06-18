#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <QThread>
#include <QObject>
#include <QRandomGenerator>


class arraysort : public QThread
{

    Q_OBJECT

public:
    arraysort();
    explicit arraysort(QObject *parent = nullptr);
    QList<int> average(QVector<int>);
    QVector<int> returnarray();
private:
    QVector<int> vector;
    int size = 500000;

private slots:
    void run();

};

#endif // ARRAYSORT_H
