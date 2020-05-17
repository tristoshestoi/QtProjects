/**
 * @file Screen.h
 * @author Ivakhiuk Valeriy <topkekhs1337@gmail.com>
 * @brief Содержит функцию для вывода перекрестка с объектами
 */
#ifndef LABA_SCREEN_H
#define LABA_SCREEN_H
#include <iostream>
#include "Fabric.h"
#include "Mediator.h"
#include "W_curpos.h"

/**
 * @param c Объект класса GreenObjects
 * @param p  Объект класса RedObjects
 * @param light Текущий цвет светофора
 */
void Screen(GreenObjects c, RedObjects p, std::string light) {
    std::string F, S;
    if(light=="Green"){
        F="R";
        S="G";
    } else {
        S="R";
        F="G"; }
    for (int j=1; j<12; j++){
        for (int i=0; i<43; i++){
            if(i==21){
                W_curspoz(i,j); std::cout<<'|';
            } else {
                W_curspoz(i,j); std::cout<<' ';
            }
            if((((i==15)||(i==27))&&((j<=4)||(j>=9))) || (((j==4)||(j==8))&&((i<=15)||(i>=27)))){
                W_curspoz(i,j); std::cout<<'*';
            }
            if(j==6){
                W_curspoz(i,j); std::cout<<'-';
            }
            if(((i==11)||(i==31))&&((j==3)||(j==9))){
                W_curspoz(i,j); std::cout<<F;
            }
            if(((i==13)||(i==29))&&((j==2)||(j==10))){
                W_curspoz(i,j); std::cout<<S;
            }
            for(auto a:c.GCars){
                if((i==a.x)&&(j==a.y)){
                    W_curspoz(i,j); std::cout<<'C';
                }}
            for(auto a:c.GPeople){
                if((i==a.x)&&(j==a.y)){
                    W_curspoz(i,j); std::cout<<'P';
                }}
            for(auto a:p.RCars){
                if((i==a.x)&&(j==a.y)){
                    W_curspoz(i,j); std::cout<<'C';
                }}
            for(auto a:p.RPeople){
                if((i==a.x)&&(j==a.y)){
                    W_curspoz(i,j); std::cout<<'P';
                }}
        }
    }
    std::cout<<std::endl;
}
#endif //LABA_SCREEN_H
