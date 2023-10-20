#include "casa_gpio.h"
#include <gpiod.h>

static struct gpiod_chip *CHIP;

int init_gpio() {
  CHIP = gpiod_chip_open_by_number(0);
  return CHIP == NULL;
}

void close_gpio() {
  if (CHIP != NULL)
    gpiod_chip_close(CHIP);
}

int digital_write(size_t pin, int value) {
  if (CHIP == NULL) {
    return -1;
  }

  struct gpiod_line *line = gpiod_chip_get_line(CHIP, pin);

  if (line == NULL) {
    return 1;
  }

  if (gpiod_line_set_value(line, value)) {
    return 3;
  }

  gpiod_line_release(line);

  return 0;
}

int digital_read(size_t pin, int *read_value) {
  if (CHIP == NULL) {
    return -1;
  }

  struct gpiod_line *line = gpiod_chip_get_line(CHIP, pin);

  if (line == NULL) {
    return 1;
  }

  int value = gpiod_line_get_value(line);

  if (value == -1) {
    return 3;
  }

  *read_value = value;

  gpiod_line_release(line);

  return 0;
}

int pinMode(size_t pin, enum PinMode MODE) {
  if (CHIP == NULL) {
    return -1;
  }

  struct gpiod_line *line = gpiod_chip_get_line(CHIP, pin);

  if (line == NULL) {
    return 1;
  }

  switch (MODE) {
  case INPUT:
    if (gpiod_line_request_input(line, "lib_casa_gpio")) {
      return 2;
    }

  case OUTPUT:
    if (gpiod_line_request_output(line, "lib_casa_gpio", 0)) {
      return 2;
    }
  }

  return 0;
}

int blink(size_t pin, float freq, float duration) {
  if (CHIP == NULL) {
    return -1;
  }

  struct gpiod_line *line = gpiod_chip_get_line(CHIP, pin);

  struct timespec delay;
  delay.tv_sec = 1 / freq;
  delay.tv_nsec = (1000000000 / (long)freq) % 1000000000;

  size_t loops = duration * freq;

  for (size_t i = 0; i < loops; i++) {
    if (nanosleep(&delay, NULL) == -1) {
      return 10;
    }
    digital_write(pin, i % 2);
  }

  return 0;
}
