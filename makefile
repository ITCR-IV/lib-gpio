CC=gcc
CFLAGS=-Wall -Wextra

SRCDIR=.

LIBS=-lgpiod

libcasagpio.so: casa_gpio.c
	$(CC) -shared -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core *~ $(INCDIR)/*~ 
	rmdir $(ODIR)
