# Makefile for math-calc-lib project

# Compiler
CC = gcc

# Project name
TARGET = calculator

# Folders
SRC_DIR = ../../src
INTERNAL_DIR = ../../internal
CALC_DIR = ./

# Source files
SRC = \
    $(SRC_DIR)/mathParser/mathParser.c \
    $(INTERNAL_DIR)/tokenizer/tokenizer.c \
    $(INTERNAL_DIR)/shuntingYard/shuntingYard.c \
    $(INTERNAL_DIR)/evaluator/evaluator.c \
    $(INTERNAL_DIR)/unitConversion/unitConversion.c \
    $(INTERNAL_DIR)/utils/utils.c \
    $(CALC_DIR)/main.c

# Include directories
INCLUDES = \
    -I$(SRC_DIR)/mathParser \
    -I$(SRC_DIR)/mathStructs \
    -I$(INTERNAL_DIR)/tokenizer \
    -I$(INTERNAL_DIR)/shuntingYard \
    -I$(INTERNAL_DIR)/evaluator \
    -I$(INTERNAL_DIR)/unitConversion \
    -I$(INTERNAL_DIR)/utils

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 $(INCLUDES)

# Linker flags
LDFLAGS = -lm   # for math library if needed (sin, cos, etc.)

# Build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Clean
clean:
	rm -f $(TARGET)
