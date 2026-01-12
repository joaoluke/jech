## 🧠 Purpose of `vm.c`

> Interpret bytecode instructions sequentially and execute their effects in the JECH language execution environment.

---

## 🔍 Full Code Analysis

### 1. **Variable Table**

```c
typedef struct {
	char name[MAX_STRING];
	char value[MAX_STRING];
} JechVariable;

static JechVariable variables[MAX_VARS];
static int var_count = 0;
```

* Stores variables declared with `keep`.
* Uses a fixed list of up to 64 variables (`MAX_VARS`).
* Each variable has `name` and `value`, both as strings (even if it is a number or boolean).

---

### 2. **`set_variable(...)` function**

```c
static void set_variable(const char *name, const char *value)
```

* Checks if the variable already exists:

* If yes, updates the value.
* If no, adds a new entry to the table.
* Ensures that the variable name is unique in the list.

🧠 Example:

```jc
keep x = "hello";
keep x = "world"; // overwrites "hello"
```

---

### 3. **Function `get_variable(...)`**

```c
static const char *get_variable(const char *name)
```

* Returns the value of the variable, if found.
* If not found, returns `NULL`.

> ⚠️ It is not yet used in `say(x)`, but it will be useful for that in the future.

---

### 4. **Main Function: `_JechVM_Execute(...)`**

```c
void _JechVM_Execute(const Bytecode *bc)
```

This function:

* Iterates linearly through the instruction array (`bc->instructions[i]`).
* For each instruction, executes based on the `inst.op`:

| Opcode    | Action                                             |
| --------- | -------------------------------------------------- |
| `OP_SAY`  | Prints `inst.operand` to the terminal              |
| `OP_KEEP` | Saves `inst.name = inst.operand` to the vars table |
| `OP_END`  | Ends execution                                     |
| `default` | Error: unknown opcode                              |

---

### 💡 Execution Example

Given this JECH code:

```jc
keep name = "JECH";
say("Welcome!");
```

After going through all the steps:

1. **Bytecode generated:**

```text
[0] OP_KEEP → name = "JECH"
[1] OP_SAY  → "Welcome!"
[2] OP_END
```

2. **Running the VM:**

```bash
> Welcome!
```

---
