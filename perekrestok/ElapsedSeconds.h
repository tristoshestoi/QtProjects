/**
 * @file ElapseSeconds.h
 * @author Ivakhiuk Valeriy <topkekhs1337@gmail.com>
 * @brief функция для вычисления времени работы программы
 */
#ifndef LABA_ELAPSEDSECONDS_H
#define LABA_ELAPSEDSECONDS_H
#include <ctime>

/**
 * @param zeroTime текущее время системы
 * @return Время работы
 */
int ElapsedSeconds(time_t zeroTime ) {
    return time(0) - zeroTime;
}

#endif //LABA_ELAPSEDSECONDS_H
