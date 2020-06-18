#include "arraysort.h"

arraysort::arraysort(QObject *parent) :
    QThread(parent)
{
    vector.resize(size);
    QRandomGenerator *gen = new QRandomGenerator();
    std::generate(vector.begin(), vector.end(), [&]() {
        return gen->bounded(-500000,500000);
    });
    gen->~QRandomGenerator();
}


QVector<int> arraysort::returnarray()
{

    return {vector.begin(), vector.end()};
}

QList<int> arraysort::average(QVector<int> vec)
{
 QList<int> list;
 list.reserve(500);
 for (int i = 0; i != 500000; i+=1000){
     list.push_back(std::accumulate(vec.begin()+i,vec.begin()+i+1000,0)/1000);
 }
 return list;
}



void arraysort::run()
{
    for (int i = size - 1; i > 0; --i){
        for (int j = 0; j < i; ++j){
            if (vector[j] > vector[j + 1]){
                std::swap(vector[j],vector[j+1]);
            }
        }
    }
}
