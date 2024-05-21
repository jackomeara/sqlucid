CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

#dirs
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BIN_DIR = bin

#src and obj files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#output executable
TARGET = $(BIN_DIR)/db

#default target
all: $(TARGET)

#link obj files to create executables
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

#compile src files into obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

#create dirs if they don't exist
$(BIN_DIR):
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

#clean build
clean:
	@if exist $(OBJ_DIR) rd /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rd /s /q $(BIN_DIR)

#phony targets
.PHONY: all clean