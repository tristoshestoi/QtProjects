#include "getavg.h"

getavg::getavg(QObject *parent) :
    QThread(parent)
{
}

QList<int> getavg::average(QVector<int> vec)
{
 QList<int> smth;
 smth.reserve(500);
 for (int i = 0; i != 500000; i+=1000){
     smth.push_back(std::accumulate(vec.begin()+i,vec.begin()+i+1000,0)/1000);
 }
 return smth;
}

getavg::~getavg(){

}
