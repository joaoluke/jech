# ⚠️ Error Examples

This directory contains examples that demonstrate JECH's error detection and reporting.

Each file is designed to trigger a specific error. Run them to see how JECH handles mistakes.

---

## 🔴 Syntax Errors (Parser)

These errors are caught **before** execution, during the parsing phase.

### Missing Tokens

| File | Error | Description |
|------|-------|-------------|
| `syntax_missing_semicolon.jc` | Missing `;` | Forgot semicolon after say |
| `syntax_keep_missing_semicolon.jc` | Missing `;` | Forgot semicolon after keep |
| `syntax_missing_paren_open.jc` | Missing `(` | Forgot opening parenthesis |
| `syntax_missing_paren_close.jc` | Missing `)` | Forgot closing parenthesis |
| `syntax_missing_equals.jc` | Missing `=` | Forgot equals in declaration |
| `syntax_missing_varname.jc` | Missing name | Forgot variable name after keep |

### Invalid Values

| File | Error | Description |
|------|-------|-------------|
| `syntax_invalid_value_say.jc` | Invalid value | Wrong type in say() |
| `syntax_invalid_value_keep.jc` | Invalid value | Wrong type in keep |

### Incomplete Statements

| File | Error | Description |
|------|-------|-------------|
| `syntax_incomplete_say.jc` | Incomplete | Cut-off say statement |
| `syntax_incomplete_keep.jc` | Incomplete | Cut-off keep statement |

---

## 🟡 Runtime Errors (VM)

These errors are caught **during** execution, when the VM runs the bytecode.

### Undefined Variables

| File | Error | Description |
|------|-------|-------------|
| `runtime_undefined_var.jc` | Undefined | Using variable in say() |
| `runtime_undefined_var_when.jc` | Undefined | Using variable in when condition |
| `runtime_undefined_var_comparison.jc` | Undefined | Using variable in comparison |
| `runtime_undefined_in_arithmetic.jc` | Undefined | Using variable in math |

### Declaration Errors

| File | Error | Description |
|------|-------|-------------|
| `runtime_redeclare.jc` | Redeclaration | Using keep on existing variable |
| `runtime_assign_undeclared.jc` | Undeclared | Assignment without keep first |

### Arithmetic Errors

| File | Error | Description |
|------|-------|-------------|
| `runtime_division_zero.jc` | Division by zero | Dividing by zero |

---

## 🧪 Running Error Examples

```bash
# Run a syntax error example
./build/jech examples/errors/syntax_missing_semicolon.jc
# Output: [SyntaxError] at line 7, col 13: Missing semicolon after 'say' statement

# Run a runtime error example
./build/jech examples/errors/runtime_undefined_var.jc
# Output: Runtime error: undefined variable 'name'

# Run all error examples to see all error messages
for file in examples/errors/*.jc; do
    echo "=== $file ==="
    ./build/jech "$file"
    echo ""
done
```

---

## 📝 Error Types in JECH

| Type | Color | When Caught | Example |
|------|-------|-------------|---------|
| `[SyntaxError]` | 🔴 Red | Parsing | Missing semicolon |
| `[Parser Error]` | 🟣 Purple | Parsing | Invalid statement |
| `[Runtime Error]` | 🟡 Yellow | Execution | Undefined variable |

---

## 💡 Tips for Debugging

1. **Check line and column numbers** — errors tell you exactly where the problem is
2. **Syntax errors first** — fix these before runtime errors can appear
3. **Declare before use** — always use `keep` before using a variable
4. **One `keep` per variable** — use assignment `=` to change values after declaration
