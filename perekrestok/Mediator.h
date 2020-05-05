/**
 * @file Mediator.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>
 * @brief Содержит объявление и реализацию классов Mediator, Colleaque, GreenObjects, RedObjects, Light, ConcreteMediator
 */
#ifndef LABA_MEDIATOR_H
#define LABA_MEDIATOR_H
#include <iostream>
#include <vector>
#include "Fabric.h"

class Colleague;
/**
 * @brief Класс "Посредник"
 */
class Mediator {
public:
    /**
     * @param message Отправляемое сообщение
     * @param colleague Коллега, отпраляющий сообщение
     */
    virtual void Send(std::string const& message, Colleague *colleague) const = 0;
};

/**
 * @brief Класс коллег
 */
class Colleague {
protected:
    Mediator* mediator_;
public:
    /**
     * @brief Конструктор класса Colleague
     * @param mediator Объект класса Mediator
     */
    explicit Colleague(Mediator *mediator): mediator_(mediator){}
};

/**
 * @brief Класс объектов, зависящих от зеленого цвета светофора
 */
class GreenObjects: public Colleague {
private:
    std::vector <Object> GCars;
    std::vector <Object> GPeople;
public:
    /**
     * @brief Метод для передвижения машин, зависящих от зеленого цвета
     * @param f Переменная, определяющая движение объектов:
     * 0 - объект должен доехать до светофора или завершить движение, т.к. загорелся другой цвет,
     * 1 - объект движется, т.к. горит его цвет
     */
    void MoveGC(int f){
        for(int i=0; i<GCars.size(); i++){
            if (f==0){
                if((GCars[i].y==5) && ((GCars[i].x>=32) || (GCars[i].x<29))){
                    GCars[i].x-=2;}
                if((GCars[i].y==7) && ((GCars[i].x>15) || (GCars[i].x<=12)) ){
                    GCars[i].x+=2;}
            } else {
                if(GCars[i].y==5){
                    GCars[i].x-=2;
                    if(GCars[i].x<0){ GCars.erase(GCars.begin() + i); }
                } else {
                    GCars[i].x+=2;
                    if(GCars[i].x>42){ GCars.erase(GCars.begin() + i); }
                }
            }
        }
    };
    /**
     * @brief Метод для передвижения пешеходов, зависящих от зеленого цвета
     * @param f Переменная, определяющая движение объектов
     */
    void MoveGP(int f){
        for(int i=0; i<GPeople.size(); i++) {
            if(f==0){
                if((GPeople[i].x >15) && (GPeople[i].direction=="r")){
                    GPeople[i].x+=2;
                    if (GPeople[i].x > 29) { GPeople.erase(GPeople.begin() + i); }
                }
                if((GPeople[i].x <27) && (GPeople[i].direction=="l")){
                    GPeople[i].x-=2;
                    if (GPeople[i].x < 13) { GPeople.erase(GPeople.begin() + i); }
                }
            } else {
                if ((GPeople[i].x < 30) && (GPeople[i].direction=="r")) {
                    GPeople[i].x+=2;
                    if (GPeople[i].x > 29) { GPeople.erase(GPeople.begin() + i); }
                } else {
                    GPeople[i].x-=2;
                    if (GPeople[i].x < 13) { GPeople.erase(GPeople.begin() + i); }
                }
            }
        }
    };
    /**
     * @brief Метод для добавления нового объекта в вектор GPeople
     * @param person Объект класса Object
     */
    void AddP(Object& person){
        GPeople.push_back(person);
    }
    /**
     * @brief Метод для добавления нового объекта в вектор GCars
     * @param car Объект класса Object
     */
    void AddC(Object& car){
        GCars.push_back(car);
    };
    /**
     * @brief Конструктор класса GreenObjects
     * @param mediator Объект класса Mediator
     */
    explicit GreenObjects (Mediator* mediator):Colleague(mediator){}
    /**
     * @brief Метод для уведомления о начале движения объектов класса GreenObjects
     * @param f Переменная, определяющая движение объектов
     */
    void Notify(int f) {
        this->MoveGC(f);
        this->MoveGP(f);
    }
    friend void Screen(GreenObjects c, RedObjects p, std::string light);
};

/**
 * @brief Класс объектов, зависящих от красного цвета светофора
 */
class RedObjects: public Colleague {
private:
    std::vector <Object> RCars;
    std::vector <Object> RPeople;
public:
    /**
     * @brief Метод для передвижения машин, зависящих от красного цвета
     * @param f Переменная, определяющая движение объектов
     */
    void MoveRC(int f){
        for(int i=0; i<RCars.size(); i++){
            if (f==0){
                if((RCars[i].x==18) && ((RCars[i].y<3) || (RCars[i].y>4))){
                    RCars[i].y++;}
                if((RCars[i].x==24) && ((RCars[i].y>9) || (RCars[i].y<8)) ){
                    RCars[i].y--;}
            } else {
                if(RCars[i].x==18){
                    RCars[i].y++;
                    if(RCars[i].y>11){ RCars.erase(RCars.begin() + i); }
                } else {
                    RCars[i].y--;
                    if(RCars[i].y<1){ RCars.erase(RCars.begin() + i); }
                }
            }
        }
    };
    /**
     * @brief Метод для передвижения пешеходов, зависящих от красного цвета
     * @param f Переменная, определяющая движение объектов
     */
    void MoveRP(int f){
        for(int i=0; i<RPeople.size(); i++){
            if(f==0){
                if ((RPeople[i].y >4) && (RPeople[i].direction=="l")){
                    RPeople[i].y++;
                    if (RPeople[i].y > 9) { RPeople.erase(RPeople.begin() + i); }
                }
                if ((RPeople[i].y <8) && (RPeople[i].direction=="r")){
                    RPeople[i].y--;
                    if (RPeople[i].y < 3) { RPeople.erase(RPeople.begin() + i); }
                }
            } else {
                if ((RPeople[i].y < 10) && (RPeople[i].direction=="l")) {
                    RPeople[i].y++;
                    if (RPeople[i].y > 9) { RPeople.erase(RPeople.begin() + i); }
                } else {
                    RPeople[i].y--;
                    if (RPeople[i].y < 3) { RPeople.erase(RPeople.begin() + i); }
                }
            }
        }
    };
    /**
     * @brief Метод для добавления нового объекта в вектор RPeople
     * @param person Объект класса Object
     */
    void AddP(Object& person){
        RPeople.push_back(person);
    }
    /**
     * @brief Метод для добавления нового объекта в вектор RCars
     * @param car Объект класса Object
     */
    void AddC(Object& car){
        RCars.push_back(car);
    };
    /**
     * @brief Конструктор класса RedObjects
     * @param mediator Объект класса Mediator
     */
    explicit RedObjects (Mediator* mediator):Colleague(mediator){}
    /**
     * @brief Метод для уведомления о начале движения объектов класса RedObjects
     * @param f Переменная, определяющая движение объектов
     */
    void Notify(int f) {
        this->MoveRC(f);
        this->MoveRP(f);
    }
    friend void Screen(GreenObjects c, RedObjects p, std::string light);
};

/**
 * @brief Класс светофора
 */
class Light: public Colleague {
private:
    std::string colour="";
public:
    /**
     * Метод для изменения цвета в засисмости от времени
     * @param time Время работы программы
     */
    void ChangeColour(int time){
        if(time%5==0){
            if(colour=="Green"){ colour = "Red"; }
            else { colour="Green"; }
        }
    }
    /**
     * @brief Метод для получения текущего значения переменной colour
     * @return Значения переменной colour
     */
    std::string GetColour() {
        return colour;
    }
    /**
     * @brief Конструктор класса Light
     * @param mediator Объект класса Mediator
     */
    explicit Light (Mediator* mediator):Colleague(mediator){}
    /**
     * @brief Метод ля отправки ткущего цвета
     * @param colour Текущий цвет
     */
    void SendColour(std::string const& colour) {
        mediator_->Send(colour, this);
    }
};

/**
 * @brief Класс "Конкретный посредник"
 */
class ConcreteMediator: public Mediator {
protected:
    GreenObjects *m_Colleague1;
    RedObjects *m_Colleague2;
    Light *m_Colleague3;
public:
    /**
     * @param c Объект класса GreenObjects
     */
    void SetColleague1(GreenObjects *c) { m_Colleague1=c; }
    /**
     * @param c Объект класса RedObjects
     */
    void SetColleague2(RedObjects *c) { m_Colleague2=c; }
    /**
     * @param c Объект класса Light
     */
    void SetColleague3(Light *c) { m_Colleague3=c; }
    /**
     * Метод для отправки сообщения
     * @param message Отправляемое сообщение
     * @param colleague Коллега, отправляющий сообщение
     */
    virtual void Send(std::string const& message, Colleague *colleague) const {
        if (colleague==m_Colleague3) {
            if (message == "Green"){
                m_Colleague1->Notify(1);
                m_Colleague2->Notify(0);
            } else {
                m_Colleague2->Notify(1);
                m_Colleague1->Notify(0);
            }
        }
    }
};
#endif //LABA_MEDIATOR_H
