#include <stdio.h>
#include <unistd.h>

#include "casa_gpio.h"

int main() {
  int ret;

  if ((ret = init_gpio())) {
    fprintf(stderr, "No se pudo inicializar el GPIO (Error: %d)\n", ret);
    return ret;
  }

  if ((ret = pinMode(20, OUTPUT))) {
    fprintf(stderr, "No se pudo setear el pin 20 como output (Error: %d)\n",
            ret);
    return ret;
  }

  if ((ret = pinMode(21, OUTPUT))) {
    fprintf(stderr, "No se pudo setear el pin 21 como output (Error: %d)\n",
            ret);
    return ret;
  }

  if ((ret = pinMode(16, INPUT))) {
    fprintf(stderr, "No se pudo setear el pin 16 como input (Error: %d)\n",
            ret);
    return ret;
  }

  printf("Seteando el pin 20 en alto (1)\n");

  if ((ret = digital_write(20, 1))) {
    fprintf(stderr, "No se pudo setear el pin 20 alto (1) (Error: %d)\n", ret);
    return ret;
  }
	usleep(1000000);
  if ((ret = digital_write(20, 0))) {
    fprintf(stderr, "No se pudo setear el pin 20 bajo (0) (Error: %d)\n", ret);
    return ret;
  }

  printf("Iniciando blink de 0.5Hz por 3 segundos en pin 21\n");

  if ((ret = blink(21, 1, 3))) {
    fprintf(stderr, "Falló el blink del pin 21 (Error: %d)\n", ret);
    return ret;
  }

  printf("Leyendo pin 16:\n");
  int valor;

  if ((ret = digital_read(16, &valor))) {
    fprintf(stderr, "Fallo al leer el pin 16 (Error: %d)\n", ret);
    return ret;
  }

  printf("Valor leído: %d\n", valor);

  return 0;
}
