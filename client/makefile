CC = gcc
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes
EXECUTABLE_FILE = client
CFLAGS = -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Client.o \
	$(BUILD_DIR)/Utils.o

all: Client

Client: $(BUILD_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir build

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.c $(INCLUDE_DIR)/Client.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.c -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Client.o: $(SRC_DIR)/Client.c $(INCLUDE_DIR)/Client.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.c -o $(BUILD_DIR)/Client.o

$(BUILD_DIR)/Utils.o: $(SRC_DIR)/Utils.c $(INCLUDE_DIR)/Utils.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utils.c -o $(BUILD_DIR)/Utils.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out