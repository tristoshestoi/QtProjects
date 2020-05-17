/**
 * @file W_curpos.h
 * @author Ivakhiuk Valeriy <topkekhs1337@gmail.com>
 * @brief функция для передвижения курсора
 */
#ifndef LABA_W_CURPOS_H
#define LABA_W_CURPOS_H
#include <windows.h>

/**
 * @param x координата Х
 * @param y Координата Y
 */
void W_curspoz(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cor={x,y};
    SetConsoleCursorPosition(hConsole,cor);
}
#endif //LABA_W_CURPOS_H
