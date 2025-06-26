# Diretórios
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Arquivos principais
MAIN_SRC = $(SRC_DIR)/main.c
CORE_SRCS = $(wildcard $(SRC_DIR)/core/*.c)
UTILS_SRCS = $(wildcard $(SRC_DIR)/utils/*.c)
ERRORS_SRCS = $(wildcard $(SRC_DIR)/errors/*.c)
DEBUG_SRCS = $(wildcard $(SRC_DIR)/debug/*.c)

# Compilador
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall

# Binários
JECH_BIN = $(BUILD_DIR)/jech
TEST_BIN = $(BUILD_DIR)/test_runner

# ======================
# COMANDOS PRINCIPAIS
# ======================

all: jech

# Compilar o projeto principal
jech:
	mkdir -p build
	gcc src/*.c src/core/*.c src/core/parser/*.c src/debug/*.c src/errors/*.c src/utils/*.c -Iinclude -o build/jech


# Compilar e rodar os testes
test: tests/main.c tests/tokenizer_tests.c $(SRC_DIR)/core/tokenizer.c $(SRC_DIR)/errors/error.c | $(BUILD_DIR)
	$(CC) $^ $(CFLAGS) -o $(TEST_BIN)
	@echo "Running JECH internal tests..."
	@./$(TEST_BIN)

# Criar pasta de build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpar os binários
clean:
	rm -rf $(BUILD_DIR)
