TARGET    = bf
SRC_FILES = bf.c
CC        = gcc
CFLAGS    = -Wall -pedantic -O3

$(TARGET):
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET)
