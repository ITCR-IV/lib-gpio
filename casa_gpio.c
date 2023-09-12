#include "casa_gpio.h"
#include <gpiod.h>

static struct gpiod_chip *CHIP;

int init_gpio() {
  CHIP = gpiod_chip_open_by_number(0);
  return CHIP == NULL;
}

void close_gpio() { gpiod_chip_close(CHIP); }

int write_pin(size_t pin_number, int value) {
	if(CHIP == NULL) {
		return -1;
	}

  struct gpiod_line *line = gpiod_chip_get_line(CHIP, pin_number);

  if (line == NULL) {
    return 1;
  }

  if (gpiod_line_request_output(line, "lib_casa_gpio", value)) {
    return 2;
  }

  if (gpiod_line_set_value(line, value)) {
    return 3;
  }

  gpiod_line_release(line);

  return 0;
}

int read_pin(size_t pin_number, int *read_value) {
	if(CHIP == NULL) {
		return -1;
	}

  struct gpiod_line *line = gpiod_chip_get_line(CHIP, pin_number);

  if (line == NULL) {
    return 1;
  }

  if (gpiod_line_request_input(line, "lib_casa_gpio")) {
    return 2;
  }

  int value = gpiod_line_get_value(line);

  if (value == -1) {
    return 3;
  }

  *read_value = value;

  gpiod_line_release(line);

  return 0;
}
