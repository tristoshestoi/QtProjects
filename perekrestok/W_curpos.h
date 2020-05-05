/**
 * @file W_curpos.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>
 * @brief Содержит функцию для передвижения курсора
 */
#ifndef LABA_W_CURPOS_H
#define LABA_W_CURPOS_H
#include <windows.h>

/**
 * @param x Координата по ОХ
 * @param y Координата по OY
 */
void W_curspoz(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cor={x,y};
    SetConsoleCursorPosition(hConsole,cor);
}
#endif //LABA_W_CURPOS_H
