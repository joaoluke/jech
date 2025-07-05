# ===============
# Variables
# ===============
CC = gcc
SRC = $(wildcard src/*.c src/core/*.c src/core/parser/*.c src/debug/*.c src/utils/*.c src/errors/*.c)
INCLUDE = -Iinclude

BUILD_DIR = build
SRC_DEBUG = src/debug/debug.c
OUTPUT = $(BUILD_DIR)/jech
OUTPUT_DEBUG = $(BUILD_DIR)/jech_debug

CFLAGS = -Wall $(INCLUDE)
DEBUG_FLAGS = -g -DJECH_DEBUG=1

# ===============
# Main Targets
# ===============
all: $(OUTPUT)

debug: $(OUTPUT_DEBUG)

# ===============
# Compilations
# ===============
$(OUTPUT): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTPUT_DEBUG): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

# ===============
# Infra
# ===============
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
