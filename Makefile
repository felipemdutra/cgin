# Paths
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin
LIB_DIR := /usr/lib
INCLUDE_INSTALL_DIR := /usr/include/cgin

# Compiler
CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -std=c11 -I$(INCLUDE_DIR)

# Find all .c files recursively
SRCS := $(shell find $(SRC_DIR) -name '*.c')
# Convert to corresponding object files in build/
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Output static library
TARGET := $(BIN_DIR)/libcgin.a  # Set to bin/ directory

# Default rule
all: $(TARGET)

# Create the static library
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)  # Ensure bin/ exists
	$(AR) rcs $@ $^

# Compile .c files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(TARGET)

# Install the library and headers
install: $(TARGET)
	sudo mkdir -p $(LIB_DIR)
	sudo cp $(BIN_DIR)/libcgin.a $(LIB_DIR)
	sudo mkdir -p $(INCLUDE_INSTALL_DIR)
	sudo cp -r $(INCLUDE_DIR)/* $(INCLUDE_INSTALL_DIR)

# Build the tests
tests:
	$(CC) $(CFLAGS) tests/server_test.c -L$(BIN_DIR) -lcgin -o bin/random_test

.PHONY: all clean install tests

