/**
 * @file Fabric.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>
 * @brief Содержит объявление и реализацию классов Object, Cars, People, Fabric
 */
#ifndef LABA_FABRIC_H
#define LABA_FABRIC_H
#include <iostream>

class RedObjects;
class GreenObjects;
/**
 * @brief Класс объектов
 */
class Object {
protected:
    int x, y, light;
    std::string direction;
public:
    /**
     * @brief Метод для получения значения переменной light
     * @return Значенеие переменной light
     */
    int GetLight() {
        return light;
    }
    /**
     * @brief Перегрузка оператора "="
     * @param object Объект класса Object, значение которого присваивается
     * @return Объект класса Object с присвоенным значением
     */
    Object& operator=(const Object& object){
        this->x=object.x;
        this->y=object.y;
        this->light=object.light;
        return *this;
    }
    friend void Screen(GreenObjects c, RedObjects p, std::string light);
    friend class RedObjects;
    friend class GreenObjects;
};

/**
 * @brief Класс пешеходов, наследуемый от класса Object
 */
class People: public Object {
public:
    /**
     * @brief Конструктор с параметрами класса People
     * @param x Координата по ОХ
     * @param y Координата по OY
     * @param light Значение светофора, от которого зависит объект
     */
    People (int x, int y, int light) {
        this->x=x;
        this->y=y;
        this->light=light;
        if(light==1){
            if(x==13){
                this->direction="r";
            } else { this->direction="l";}
        } else {
            if(y==3){
                this->direction="l";
            } else { this->direction="r";}
        }
    }
};

/**
 * @brief Класс машин, наследуемый от класса Object
 */
class Cars: public Object {
public:
    /**
     * @brief Конструктор с параметрами класса Cars
     * @param x Координата по ОХ
     * @param y Координата по OY
     * @param light Значение светофора, от которого зависит объект
     */
    Cars (int x, int y, int light){
        this->x=x;
        this->y=y;
        this->light=light;
    }
};

/**
 * @brief Класс-фабрика
 */
class Fabric {
public:
    /**
     * @brief Метод для создания объектов классов Cars и People
     * @param type Тип создаваемого объекта
     * @return Объект класса Cars или People
     */
    Object* CreateObject(std::string type){
        int a = rand() % 4;
        int i = rand() % 2;
        if (type == "Person") {
            switch (a) {
                case 0: return new People(13, 3, i);
                case 1: return new People(29, 3, i);
                case 2: return new People(13, 9, i);
                case 3: return new People(29, 9, i);
            }
        } else {
            if (type == "Car") {
                switch (a) {
                    case 0: return new Cars(18, 1, 0);
                    case 1: return new Cars(42, 5, 1);
                    case 2: return new Cars(0, 7, 1);
                    case 3: return new Cars(24, 11, 0);
                }
            } else { throw std::exception(); }
        }
    }
};
#endif //LABA_FABRIC_H
