CC = gcc
CFLAGS = -Wall -Iinclude

SRC = src/main.c src/integracion.c src/densidades.c
OBJ = $(SRC:.c=.o)
TARGET = triple_integral

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

clean:
	rm -f $(OBJ) $(TARGET)

