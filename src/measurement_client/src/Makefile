CC=gcc
CFLAGS=-I.
DEPS = measurement_client.h
OBJ = measurement_client.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

measurement_client_make: measurement_client.o
	gcc -o measurement_client measurement_client.o -I.

.PHONY: clean

clean:
	rm -f measurement_client.o measurement_client
