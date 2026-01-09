# Git Hooks for Jech

This directory contains Git hooks to maintain code quality.

## 🪝 Available Hooks

### Pre-Commit Hook

Automatically runs before every commit to ensure:
- ✅ Code compiles successfully
- ✅ All tests pass (70 assertions)
- ✅ No broken code enters the repository

## 📦 Installation

### Quick Install

```bash
./install_hooks.sh
```

### Manual Install

```bash
chmod +x .git/hooks/pre-commit
```

## 🚀 Usage

Once installed, the hook runs automatically:

```bash
# Normal commit - hook runs automatically
git commit -m "Add new feature"

# Output:
# 🔍 Running pre-commit checks...
# 🔨 Compiling Jech...
# ✓ Compilation successful
# 🧪 Running test suite...
# ✓ All tests passed!
# ✓ Pre-commit checks passed!
```

## ⚠️ When Tests Fail

If tests fail, the commit is blocked:

```bash
$ git commit -m "Broken code"
🔍 Running pre-commit checks...
🔨 Compiling Jech...
✓ Compilation successful
🧪 Running test suite...
✗ Tests failed!

════════════════════════════════════════
  Commit blocked - fix failing tests
════════════════════════════════════════
```

Fix the tests, then commit again.

## 🔧 Advanced Usage

### Skip Hook (Emergency Only)

```bash
# Not recommended - only for emergencies
git commit --no-verify -m "Emergency fix"
```

### Temporarily Disable

```bash
# Rename to disable
mv .git/hooks/pre-commit .git/hooks/pre-commit.disabled

# Rename back to enable
mv .git/hooks/pre-commit.disabled .git/hooks/pre-commit
```

### Uninstall

```bash
rm .git/hooks/pre-commit
```

## 📊 What Gets Tested

The pre-commit hook runs the full test suite:

| Suite | Tests | Assertions |
|-------|-------|------------|
| Tokenizer | 5 | 32 |
| Parser | 6 | 25 |
| VM | 5 | 6 |
| Integration | 7 | 7 |
| **Total** | **23** | **70** |

## 🎯 Benefits

1. **Catch bugs early** - Before they enter the repository
2. **Maintain quality** - Every commit is tested
3. **Save time** - No broken builds in CI/CD
4. **Team confidence** - Everyone's commits are validated
5. **Clean history** - No "fix tests" commits

## 🔮 Future Hooks

Planned hooks:
- [ ] `pre-push` - Run extended tests before push
- [ ] `commit-msg` - Validate commit message format
- [ ] `post-merge` - Rebuild after merges

## 📚 Resources

- [Git Hooks Documentation](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)
- [Jech Contributing Guide](../CONTRIBUTING.md)
- [Test Suite Documentation](../tests/README.md)

---

**Maintained by:** Jech Team  
**Last Updated:** January 2026
