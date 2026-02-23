CC = gcc
CFLAGS = -Wall -Wextra -I include

SRC = src/test-suite/test-suite.c
SRC_TEST = tests/main.c tests/tests.c

SRC_OBJ = $(SRC:.c=.o)
TEST_OBJ = $(SRC_TEST:.c=.o)

TARGET = build/sea-float

all: test

test: $(SRC_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)
	./$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_OBJ) $(TEST_OBJ) $(TARGET)


