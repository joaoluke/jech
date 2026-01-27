# ===============
# Variables
# ===============
CC = gcc
EMCC = emcc
SRC = $(wildcard src/*.c src/core/*.c src/core/parser/*.c src/debug/*.c src/utils/*.c src/errors/*.c)
SRC_WASM = src/wasm/jech_wasm.c
INCLUDE = -Iinclude

BUILD_DIR = build
SRC_DEBUG = src/debug/debug.c
OUTPUT = $(BUILD_DIR)/jech
OUTPUT_DEBUG = $(BUILD_DIR)/jech_debug
OUTPUT_WASM_JS = $(BUILD_DIR)/jech.js
OUTPUT_WASM = $(BUILD_DIR)/jech.wasm

CFLAGS = -Wall $(INCLUDE)
LDFLAGS = -lreadline
DEBUG_FLAGS = -g -DJECH_DEBUG=1
WASM_FLAGS = -O3 -s WASM=1 \
	-s EXPORTED_FUNCTIONS='["_jech_execute","_jech_clear","_jech_version","_append_output","_get_output","_malloc","_free"]' \
	-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","UTF8ToString","stringToUTF8"]' \
	-s MODULARIZE=1 \
	-s EXPORT_NAME='JechModule' \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s INITIAL_MEMORY=16777216 \
	-s MAXIMUM_MEMORY=33554432 \
	-s NO_EXIT_RUNTIME=1 \
	-s ASSERTIONS=0 \
	-s EXIT_RUNTIME=0

# ===============
# Main Targets
# ===============
all: $(OUTPUT)

debug: $(OUTPUT_DEBUG)

wasm: $(OUTPUT_WASM_JS)

# ===============
# Compilations
# ===============
$(OUTPUT): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OUTPUT_DEBUG): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@ $(LDFLAGS)

$(OUTPUT_WASM_JS): $(SRC_WASM) $(SRC) | $(BUILD_DIR)
	$(EMCC) $(CFLAGS) $(WASM_FLAGS) $(SRC_WASM) $(filter-out src/main.c src/core/repl.c, $(SRC)) -o $@

# ===============
# Infra
# ===============
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
