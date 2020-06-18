#ifndef GETAVG_H
#define GETAVG_H
#include <QThread>

class getavg : public QThread
{

    Q_OBJECT


public:
    explicit getavg(QObject *parent = nullptr);
    
    QList<int> average(QVector<int>);
    QList<int> returnv(QVector<int> vec);
private:
    QList<int> buff;
    virtual ~getavg();
};




#endif // GETAVG_H
