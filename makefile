CC=gcc
CFLAGS=-I
DEPS = Heap.h
OBJ = Main.o Heap.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

randmst: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
