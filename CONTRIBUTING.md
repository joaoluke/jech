# Contributing to Jech

Thank you for your interest in contributing to Jech! This document provides guidelines and instructions for contributing.

## 🧪 Testing

### Running Tests

We have a comprehensive test suite covering all core components. To run tests:

```bash
# Make the test script executable (first time only)
chmod +x run_tests.sh

# Run all tests
./run_tests.sh
```

### Test Structure

Our tests are organized into four categories:

1. **Tokenizer Tests** (`tests/test_tokenizer.c`)
   - Tests lexical analysis and token generation
   - Covers keywords, operators, literals, and arrays

2. **Parser Tests** (`tests/test_parser.c`)
   - Tests AST generation from tokens
   - Covers all statement types and array syntax

3. **VM Tests** (`tests/test_vm.c`)
   - Tests bytecode execution
   - Covers variable management and array operations

4. **Integration Tests** (`tests/test_integration.c`)
   - End-to-end tests of the complete pipeline
   - Tests real-world usage scenarios

### Writing New Tests

When adding new features, please add corresponding tests:

```c
#include "test_framework.h"

TEST(test_your_feature)
{
    // Arrange
    const char *source = "your jech code;";
    
    // Act
    // ... execute your code
    
    // Assert
    ASSERT_EQ(actual, expected, "Description of what should happen");
    ASSERT_STR_EQ(actual_str, expected_str, "String comparison");
    ASSERT(condition, "General condition check");
}
```

Then add your test to the appropriate test suite in `tests/run_tests.c`.

## 🪝 Git Hooks

### Installing Pre-Commit Hook

We provide a pre-commit hook that automatically runs tests before each commit:

```bash
# Install the hook (one-time setup)
./install_hooks.sh
```

### What the Hook Does

When you run `git commit`, the hook will:

1. ✅ Compile the project
2. ✅ Run all tests (70 assertions)
3. ✅ Block the commit if tests fail
4. ✅ Allow the commit if tests pass

### Example Output

```bash
$ git commit -m "Add new feature"
🔍 Running pre-commit checks...

🔨 Compiling Jech...
✓ Compilation successful

🧪 Running test suite...
✓ All tests passed!

════════════════════════════════════════
  ✓ Pre-commit checks passed!
  Proceeding with commit...
════════════════════════════════════════
```

### Bypassing the Hook

If you need to commit without running tests (not recommended):

```bash
git commit --no-verify -m "Your message"
```

### Uninstalling

```bash
rm .git/hooks/pre-commit
```

## 🔧 Development Workflow

1. **Create a branch** for your feature/fix
2. **Write tests first** (TDD approach recommended)
3. **Implement your changes**
4. **Run tests** to ensure nothing broke
5. **Update documentation** if needed
6. **Submit a pull request**

## 📝 Code Style

- Use tabs for indentation (existing codebase convention)
- Keep functions focused and small
- Add comments for complex logic
- Follow existing naming conventions:
  - `_JechModule_FunctionName` for public functions
  - `function_name` for static/private functions

## 🐛 Reporting Bugs

When reporting bugs, please include:

1. **Description** of the issue
2. **Steps to reproduce**
3. **Expected behavior**
4. **Actual behavior**
5. **Jech version** (from `./build/jech --version` if available)
6. **Test case** demonstrating the bug (if possible)

## ✨ Feature Requests

We welcome feature requests! Please:

1. Check existing issues/roadmap first
2. Describe the use case
3. Provide example syntax (if applicable)
4. Explain why it would benefit Jech users

## 🎯 Areas Needing Help

- [ ] More test coverage (edge cases)
- [ ] Performance benchmarks
- [ ] Documentation improvements
- [ ] Example programs
- [ ] Error message improvements
- [ ] REPL enhancements

## 📚 Resources

- [Architecture Documentation](docs/en/architecture.md)
- [Tokenizer Guide](docs/en/tokenizer.md)
- [Parser Guide](docs/en/parser.md)
- [VM Guide](docs/en/vm.md)

## ⚖️ License

By contributing, you agree that your contributions will be licensed under the same license as the project.

---

Thank you for contributing to Jech! 🚀
