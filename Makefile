CC=g++
CFLAGS=-g -Wall
TARGET=prodcons
SRC=ProdCons.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -std=c++11 -pthread -o $(TARGET) $(SRC)

clean:
	$(RM) $(TARGET)

