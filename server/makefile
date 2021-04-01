CC = gcc
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
EXECUTABLE_FILE = server

all: Server

Server: $(BUILD_DIR)/Main.o
	$(CC) $(BUILD_DIR)/Main.o -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.c
	$(CC) -c $(SRC_DIR)/Main.c -o $(BUILD_DIR)/Main.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out