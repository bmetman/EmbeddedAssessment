IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../obj
LDIR =../lib

LIBS=-lm

_RUN_DEPS = main.h measurement_client.h 
RUN_DEPS = $(patsubst %,$(IDIR)/%,$(_RUN_DEPS))

_RUN_OBJ = main.o measurement_client.o 
RUN_OBJ = $(patsubst %,$(ODIR)/%,$(_RUN_OBJ))

$(ODIR)/%.o: %.c $(RUN_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

_TEST_DEPS =  test_measurement_client.h measurement_client.h 
TEST_DEPS = $(patsubst %,$(IDIR)/%,$(_TEST_DEPS))

_TEST_OBJ = test_measurement_client.o measurement_client.o 
TEST_OBJ = $(patsubst %,$(ODIR)/%,$(_TEST_OBJ))

$(ODIR)/%.o: %.c $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: run test

run: $(RUN_OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: $(TEST_OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f run test