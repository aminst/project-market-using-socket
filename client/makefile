CC = gcc
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
EXECUTABLE_FILE = client
CFLAGS = -I$(INCLUDE_DIR)

all: Client

Client: $(BUILD_DIR)/Main.o $(BUILD_DIR)/Client.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/Main.o $(BUILD_DIR)/Client.o -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.c $(INCLUDE_DIR)/Client.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.c -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Client.o: $(SRC_DIR)/Client.c $(INCLUDE_DIR)/Client.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.c -o $(BUILD_DIR)/Client.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out