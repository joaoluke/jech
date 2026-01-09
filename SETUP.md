# Jech Development Setup

Quick setup guide for Jech contributors.

## 🚀 Quick Start

```bash
# 1. Clone the repository
git clone <repository-url>
cd jech

# 2. Build the project
make

# 3. Run tests
./run_tests.sh

# 4. Install Git hooks (recommended)
./install_hooks.sh

# 5. Try the REPL
./build/jech
```

## 📋 Prerequisites

- **GCC** - C compiler
- **Make** - Build automation
- **Git** - Version control
- **Bash** - For scripts

## 🔨 Building

```bash
# Clean build
make clean && make

# Debug build (with debug symbols)
make debug
```

## 🧪 Testing

```bash
# Run all tests
./run_tests.sh

# Expected output:
# ✓ All test suites passed!
# 70/70 assertions passing
```

## 🪝 Git Hooks Setup

**Highly recommended** - Automatically runs tests before commits:

```bash
./install_hooks.sh
```

This prevents broken code from being committed.

## 📁 Project Structure

```
jech/
├── src/              # Source code
│   ├── core/         # Core language components
│   │   ├── tokenizer.c
│   │   ├── parser/
│   │   ├── bytecode.c
│   │   ├── vm.c
│   │   └── repl.c
│   ├── utils/        # Utilities
│   └── errors/       # Error handling
├── include/          # Header files
├── tests/            # Test suite
├── examples/         # Example programs
├── docs/             # Documentation
└── build/            # Compiled binaries
```

## 🎯 Development Workflow

1. Install hooks: `./install_hooks.sh`
2. Create feature branch: `git checkout -b feature/my-feature`
3. Write tests first (TDD)
4. Implement feature
5. Tests run automatically on commit
6. Push and create PR

## 📚 Documentation

- [Contributing Guide](CONTRIBUTING.md)
- [Test Documentation](tests/README.md)
- [Architecture](docs/en/architecture.md)
- [Git Hooks](hooks/README.md)

## 🐛 Troubleshooting

### Tests failing?
```bash
# Check compilation
make clean && make

# Run tests with verbose output
./run_tests.sh
```

### Hook not working?
```bash
# Reinstall
./install_hooks.sh

# Check permissions
ls -la .git/hooks/pre-commit
```

### Build errors?
```bash
# Clean and rebuild
make clean
make
```

## 💡 Tips

- Use REPL for quick testing: `./build/jech`
- Run specific examples: `./build/jech examples/17_arrays_basic.jc`
- Skip hook in emergencies: `git commit --no-verify`
- Check test coverage in `tests/README.md`

## 🤝 Getting Help

- Check [CONTRIBUTING.md](CONTRIBUTING.md)
- Review existing tests in `tests/`
- Look at examples in `examples/`
- Read architecture docs in `docs/`

---

**Ready to contribute?** Start with [CONTRIBUTING.md](CONTRIBUTING.md)!
