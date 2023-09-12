#ifndef CASA_GPIO_H
#define CASA_GPIO_H

#include <stddef.h>

int init_gpio();

void close_gpio();


int write_pin(size_t pin_number, int value);

int read_pin(size_t pin_number, int *read_value);

#endif
