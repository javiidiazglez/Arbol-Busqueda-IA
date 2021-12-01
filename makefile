CC=g++
CXXFLAGS=-g -std=c++14

OBJS = main.o mapa.o celda.o coche.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o cocheAutonomo ${OBJS}

clean: 
	rm -rf *.o cocheAutonomo