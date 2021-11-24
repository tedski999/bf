TARGET    = bf
SRC_FILES = bf.c
CC        = gcc
CFLAGS    = -Wall -pedantic -O3

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET)
