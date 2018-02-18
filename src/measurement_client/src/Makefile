IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -g

ODIR=../obj
LDIR =../lib

LIBS=-lm

_START_DEPS = main.h measurement_client.h sensor_interface.h
START_DEPS = $(patsubst %,$(IDIR)/%,$(_START_DEPS))

_START_OBJ = main.o measurement_client.o sensor_interface.o
START_OBJ = $(patsubst %,$(ODIR)/%,$(_START_OBJ))

$(ODIR)/%.o: %.c $(START_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

_TEST_DEPS =  test_measurement_client.h measurement_client.h sensor_interface.h
TEST_DEPS = $(patsubst %,$(IDIR)/%,$(_TEST_DEPS))

_TEST_OBJ = test_measurement_client.o measurement_client.o sensor_interface.o
TEST_OBJ = $(patsubst %,$(ODIR)/%,$(_TEST_OBJ))

$(ODIR)/%.o: %.c $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: start test

start: $(START_OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: $(TEST_OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f start test