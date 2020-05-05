/**
 * @file ElapseSeconds.h
 * @author Levashova Anastasia <nastya.levashova.12@mail.ru>
 * @brief Содержит функцию для вычисления времени работы программы
 */
#ifndef LABA_ELAPSEDSECONDS_H
#define LABA_ELAPSEDSECONDS_H
#include <ctime>

/**
 * @param zeroTime Текущее календарное время системы
 * @return Время работы
 */
int ElapsedSeconds(time_t zeroTime ) {
    return time(0) - zeroTime;
}

#endif //LABA_ELAPSEDSECONDS_H
