#!/bin/bash

# Jech Test Runner Script
# This script compiles and runs all tests for the Jech language

set -e

echo "🧪 Jech Test Suite Runner"
echo "=========================="
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Clean previous test build
echo "🧹 Cleaning previous test builds..."
rm -f build/test_runner

# Compile test suite
echo "🔨 Compiling test suite..."
gcc -Wall -Iinclude \
    tests/run_tests.c \
    tests/test_tokenizer.c \
    tests/test_parser.c \
    tests/test_vm.c \
    tests/test_integration.c \
    src/core/ast.c \
    src/core/bytecode.c \
    src/core/pipeline.c \
    src/core/tokenizer.c \
    src/core/vm.c \
    src/core/parser/assign.c \
    src/core/parser/function.c \
    src/core/parser/keep.c \
    src/core/parser/map.c \
    src/core/parser/parser.c \
    src/core/parser/say.c \
    src/core/parser/when.c \
    src/utils/read_file.c \
    src/utils/token_utils.c \
    src/errors/error.c \
    -o build/test_runner \
    -lreadline

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Compilation successful${NC}"
    echo ""
else
    echo -e "${RED}✗ Compilation failed${NC}"
    exit 1
fi

# Run tests
echo "🚀 Running tests..."
echo ""
./build/test_runner

# Capture exit code
TEST_EXIT_CODE=$?

echo ""
if [ $TEST_EXIT_CODE -eq 0 ]; then
    echo -e "${GREEN}════════════════════════════════════════${NC}"
    echo -e "${GREEN}  ✓ ALL TESTS PASSED!${NC}"
    echo -e "${GREEN}════════════════════════════════════════${NC}"
    exit 0
else
    echo -e "${RED}════════════════════════════════════════${NC}"
    echo -e "${RED}  ✗ SOME TESTS FAILED${NC}"
    echo -e "${RED}════════════════════════════════════════${NC}"
    exit 1
fi
