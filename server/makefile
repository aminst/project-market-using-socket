CC = gcc
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
EXECUTABLE_FILE = server
CFLAGS = -I$(INCLUDE_DIR)

all: Server

Server: $(BUILD_DIR)/Server.o $(BUILD_DIR)/Main.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/Main.o $(BUILD_DIR)/Server.o -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.c $(INCLUDE_DIR)/Server.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.c -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Server.o: $(SRC_DIR)/Server.c $(INCLUDE_DIR)/Server.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.c -o $(BUILD_DIR)/Server.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out