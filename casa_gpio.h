#ifndef CASA_GPIO_H
#define CASA_GPIO_H

#include <stddef.h>

// Retorna código de salida (0 == OK)
int init_gpio();

void close_gpio();

enum PinMode { INPUT, OUTPUT };

// Retorna código de salida (0 == OK)
int pinMode(size_t pin, enum PinMode MODE);

// Retorna código de salida (0 == OK)
int digital_write(size_t pin, int value);

// Retorna código de salida (0 == OK)
int digital_read(size_t pin, int *read_value);

// freq interpretada en Hz, duration en segundos
int blink(size_t pin, float freq, float duration);

#endif
