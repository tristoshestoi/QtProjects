#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <QObject>
#include <QDebug>
#include <math.h>

class action : public QObject
{
    Q_OBJECT
private:
    double operator1 = 0.0;
    double operator2 = 0.0;
public:
    explicit action(QObject *parent = nullptr);
public slots:
    void SetOperator1(QString operator1){
        this->operator1 = operator1.replace(",", ".").toDouble();
    }
    void SetOperator2(QString operator2){
        this->operator2 = operator2.replace(",", ".").toDouble();
    }
    void initPLus(){
        double result = this->operator1+operator2;
        QString qstringResult;
        emit setResult(QString::number(result));
    }
    void initMinus(){
        double result = this->operator1-operator2;
        QString qstringResult;
        emit setResult(QString::number(result));
    }
    void initMult(){
        double result = this->operator1*operator2;
        QString qstringResult;
        emit setResult(QString::number(result));
    }
    void initDiv(){
            if (operator2==0){
            QString result = "Can't divide by 0";
            emit setResult(QString(result));
            }
            else{
            double result = this->operator1/operator2;
            emit setResult(QString::number(result));
            }


    }
    void initPow(){
        double result = pow(operator1, operator2);
        QString qstringResult;
        emit setResult(QString::number(result));
    }
    void initRoot(){
        if (operator1<0){
            QString result = "Can't take the root from a negative number";
            emit setResult(QString(result));
        }
        else{
        double result = pow(operator1, 1/operator2);
        QString qstringResult;
        emit setResult(QString::number(result));
        }
    }
    void initLn(){
        if (operator1<=0){
            QString result = "Doesn't exist";
            emit setResult(QString(result));
        }
        else{
        double result = log(operator1)/log(operator2);
        QString qstringResult;
        emit setResult(QString::number(result));
        }
    }
    void initSin(){
        double result = sin(operator1*3.14159265/180);
        QString qstringResult;
        emit setResult(QString::number(result));
    }
    void initCos(){
        double result = cos(operator1*3.14159265/180);
        QString qstringResult;
        emit setResult(QString::number(result));
    }
    void initTan(){
        if (cos(operator1)*3.14159265/180==0){
            QString result = "Doesn't exist";
            emit setResult(QString(result));
        }
        else{
        double result = tan(operator1*3.14159265/180);
        QString qstringResult;
        emit setResult(QString::number(result));
        }
    }
signals:
    void setResult(QString result);

};

#endif // ACTION_H
