# 🧠 Virtual Machine (VM)

## What is a Virtual Machine?

The **Virtual Machine** is the final stage of the pipeline. It reads bytecode instructions and executes them, producing the actual program output.

Think of it like a CPU, but implemented in software and designed specifically for your language.

### Why a VM?

1. **Abstraction** — hides hardware complexity
2. **Portability** — same bytecode runs everywhere
3. **Safety** — controlled execution environment
4. **Simplicity** — easier to implement than native code generation

---

## 📊 Runtime Environment

### Variable Storage

```c
typedef struct {
    char name[MAX_STRING];
    char value[MAX_STRING];
} JechVariable;

static JechVariable variables[MAX_VARS];  // Up to 64 variables
static int var_count = 0;
```

Variables are stored as **name-value pairs** in a simple array. All values are strings internally — the VM interprets them based on context.

---

## 🔧 Core Functions

### `_JechVM_SetVariable`

```c
void _JechVM_SetVariable(const char *name, const char *value)
```

Stores or updates a variable:
- If variable exists → update its value
- If variable is new → add to the table

---

### `_JechVM_GetVariable`

```c
const char *_JechVM_GetVariable(const char *name)
```

Retrieves a variable's value by name. Returns `NULL` if not found.

---

### `variable_exists`

```c
bool variable_exists(const char *name)
```

Checks if a variable has been declared. Used to prevent assignment to undeclared variables.

---

## 🎯 Main Execution Loop

```c
void _JechVM_Execute(const Bytecode *bc)
```

The heart of the VM — a simple loop that processes each instruction:

```c
for (int i = 0; i < bc->count; i++) {
    Instruction inst = bc->instructions[i];
    
    switch (inst.op) {
        case OP_SAY:    // Handle output
        case OP_KEEP:   // Handle declaration
        case OP_ASSIGN: // Handle reassignment
        case OP_WHEN:   // Handle comparison conditionals
        case OP_WHEN_BOOL: // Handle boolean conditionals
        case OP_END:    // Stop execution
    }
}
```

---

## 📋 Instruction Handlers

### `OP_SAY` — Output

Prints a value to the terminal:

```c
case OP_SAY:
    if (inst.token_type == TOKEN_IDENTIFIER) {
        // It's a variable — look up its value
        const char *value = _JechVM_GetVariable(inst.operand);
        printf("%s\n", value);
    } else {
        // It's a literal — print directly
        printf("%s\n", inst.operand);
    }
```

---

### `OP_KEEP` — Variable Declaration

Creates a new variable:

```c
case OP_KEEP:
    if (_JechVM_GetVariable(inst.name) != NULL) {
        // Error: variable already exists!
        report_runtime_error("Variable already declared", ...);
    }
    _JechVM_SetVariable(inst.name, inst.operand);
```

---

### `OP_ASSIGN` — Reassignment

Updates an existing variable:

```c
case OP_ASSIGN:
    if (!variable_exists(inst.name)) {
        // Error: can't assign to undeclared variable!
        report_runtime_error("Cannot assign to undeclared variable", ...);
    }
    _JechVM_SetVariable(inst.name, inst.operand);
```

---

### `OP_WHEN` — Comparison Conditionals

Handles conditions like `age > 18` or `name == "João"`:

```c
case OP_WHEN:
    // Get left value (variable)
    const char *left_val = _JechVM_GetVariable(inst.name);
    
    // Get right value (literal or variable)
    const char *right_val = inst.operand;
    
    // Compare based on type
    if (inst.cmp_operand_type == TOKEN_STRING) {
        // String comparison
        is_true = (strcmp(left_val, right_val) == 0);
    } else {
        // Numeric comparison
        is_true = (atof(left_val) > atof(right_val));
    }
    
    // Execute appropriate branch
    if (is_true) {
        printf("%s\n", inst.operand_right);  // Then branch
    } else if (inst.has_else) {
        printf("%s\n", inst.else_operand);   // Else branch
    }
```

---

### `OP_WHEN_BOOL` — Boolean Conditionals

Handles conditions like `when (active)` or `when (true)`:

```c
case OP_WHEN_BOOL:
    bool is_true;
    
    if (inst.bin_op == TOKEN_BOOL) {
        // Literal: true or false
        is_true = strcmp(inst.name, "true") == 0;
    } else {
        // Variable: look up its value
        const char *val = _JechVM_GetVariable(inst.name);
        is_true = strcmp(val, "true") == 0;
    }
    
    // Execute appropriate branch
    if (is_true) {
        printf("%s\n", inst.operand);
    } else if (inst.has_else) {
        printf("%s\n", inst.else_operand);
    }
```

---

## 💡 Complete Execution Example

Source code:
```jc
keep age = 25;
when (age > 18) {
    say("adult");
}
else {
    say("minor");
}
```

Execution trace:
```text
[0] OP_KEEP: Store variable "age" = "25"
    → variables = [{ name: "age", value: "25" }]

[1] OP_WHEN: Compare age > 18
    → left_val = "25" (from variable lookup)
    → right_val = "18"
    → 25 > 18 = true
    → Execute then-branch: print "adult"

[2] OP_END: Stop execution
```

Output:
```
adult
```

---

## ⚠️ Runtime Errors

The VM catches and reports errors:

| Error | Cause |
|-------|-------|
| `Undefined variable 'x'` | Using a variable that wasn't declared |
| `Variable already declared` | Using `keep` on an existing variable |
| `Cannot assign to undeclared variable` | Assignment without `keep` first |
| `Division by zero` | Dividing by zero in arithmetic |

---

## 💡 Key Concepts for Learners

1. **Stack-less execution** — JECH uses a simple linear model
2. **Dynamic typing** — types are determined at runtime
3. **String-based storage** — everything is a string internally
4. **Fail-fast** — errors stop execution immediately

---

## 🔬 How VM Connects to Other Stages

```text
Tokens → Parser → AST → Bytecode → VM
                                    ↑
                               You are here
```

The VM is the **final destination** — it takes bytecode and produces actual program output.

---
