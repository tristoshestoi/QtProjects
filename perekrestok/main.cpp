#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include "Fabric.h"
#include "Mediator.h"
#include "Screen.h"
#include "ElapsedSeconds.h"

time_t zeroTime = time(0);

int main() {
    srand(time(NULL));
    int b, t;
    Fabric f;
    Object *temp;
    ConcreteMediator m;
    GreenObjects G(&m);
    RedObjects R(&m);
    Light L(&m);
    m.SetColleague1(&G);
    m.SetColleague2(&R);
    m.SetColleague3(&L);
    for ( ; ; ){
        t=ElapsedSeconds(zeroTime);
        if(t%10==0){
            for (int i=0; i<3; i++){
                b = rand() % 2;
                if (b==0){
                    temp=f.CreateObject("Person");
                    if(temp->GetLight()==1) {
                        G.AddP(*temp);
                    } else { R.AddP(*temp); }
                } else {
                    temp=f.CreateObject("Car");
                    if(temp->GetLight()==1) {
                        G.AddC(*temp);
                    } else { R.AddC(*temp); }
                }
            }
        }
        L.ChangeColour(t);
        Screen(G, R, L.GetColour());
        L.SendColour(L.GetColour());
        Sleep(1000);
        system("cls");
    }
    delete temp;
    return 0;
}