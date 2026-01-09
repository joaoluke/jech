# Jech Test Suite

Comprehensive test suite for the Jech programming language.

## 📊 Test Coverage

| Component | Tests | Coverage |
|-----------|-------|----------|
| **Tokenizer** | 5 tests (32 assertions) | Lexical analysis, keywords, operators, arrays |
| **Parser** | 6 tests (25 assertions) | AST generation, all statement types |
| **VM** | 5 tests (6 assertions) | Bytecode execution, variables, arrays |
| **Integration** | 7 tests (7 assertions) | End-to-end pipeline tests |
| **Total** | **23 tests (70 assertions)** | ✅ All passing |

## 🚀 Running Tests

### Quick Start

```bash
# Run all tests
./run_tests.sh
```

### Manual Compilation

```bash
# Compile test suite
gcc -Wall -Iinclude \
    tests/run_tests.c \
    tests/test_tokenizer.c \
    tests/test_parser.c \
    tests/test_vm.c \
    tests/test_integration.c \
    src/core/*.c \
    src/core/parser/*.c \
    src/utils/*.c \
    src/errors/*.c \
    -o build/test_runner

# Run tests
./build/test_runner
```

## 📝 Test Structure

### Tokenizer Tests (`test_tokenizer.c`)
- ✅ String literals in say statements
- ✅ Variable declarations with numbers
- ✅ Array literal syntax `[1, 2, 3]`
- ✅ Array indexing `arr[0]`
- ✅ When conditions with operators

### Parser Tests (`test_parser.c`)
- ✅ Say statement AST generation
- ✅ Keep statement parsing
- ✅ Array literal parsing
- ✅ Array indexing in expressions
- ✅ Variable assignment
- ✅ Multiple statements in sequence

### VM Tests (`test_vm.c`)
- ✅ Variable creation and retrieval
- ✅ Variable reassignment
- ✅ Array creation and element access
- ✅ Arrays with string elements
- ✅ State clearing (for REPL)

### Integration Tests (`test_integration.c`)
- ✅ Hello World program
- ✅ Variable flow and scoping
- ✅ Array operations end-to-end
- ✅ Mixed-type arrays
- ✅ Empty arrays
- ✅ Variables and arrays together
- ✅ Multiple reassignments

## 🧪 Writing New Tests

Use the test framework macros:

```c
#include "test_framework.h"

TEST(test_my_feature)
{
    // Arrange
    const char *source = "keep x = 10;";
    
    // Act
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    // Assert
    ASSERT_EQ(tokens.count, 5, "Should have 5 tokens");
    ASSERT_STR_EQ(tokens.tokens[1].value, "x", "Variable name should be 'x'");
}
```

### Available Assertions

- `ASSERT(condition, message)` - General boolean assertion
- `ASSERT_EQ(actual, expected, message)` - Equality check
- `ASSERT_STR_EQ(actual, expected, message)` - String comparison

### Adding Tests to Suite

1. Create test function using `TEST()` macro
2. Add to appropriate test file
3. Register in `run_tests.c`:

```c
int run_my_tests()
{
    TEST_SUITE_BEGIN("My Test Suite");
    
    RUN_TEST(test_my_feature);
    
    TEST_SUITE_END();
}
```

## 🔄 Continuous Integration

Tests run automatically on:
- Push to `main` or `develop` branches
- Pull requests to `main` or `develop`

See `.github/workflows/tests.yml` for CI configuration.

## 🐛 Regression Testing

All new features should include tests to prevent regressions:

- **Arrays** - Covered by parser, VM, and integration tests
- **REPL** - Covered by VM state clearing tests
- **Variable reassignment** - Covered by integration tests

## 📈 Future Improvements

- [ ] Add performance benchmarks
- [ ] Add memory leak detection (valgrind)
- [ ] Add fuzzing tests
- [ ] Increase edge case coverage
- [ ] Add error handling tests
- [ ] Add REPL-specific integration tests

## 🤝 Contributing

See [CONTRIBUTING.md](../CONTRIBUTING.md) for guidelines on writing and submitting tests.

---

**Last Updated:** January 2026  
**Test Framework Version:** 1.0
