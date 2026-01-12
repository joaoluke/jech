## ⚙️ Role of `bytecode.c`

This file is responsible for:

> 🚧 **Converting the AST (command tree) into linear bytecode**
> which will later be executed by the virtual machine.

---

## 🔍 Code Analysis

### 1. **Helper function: `compile_say`**

```c
static void compile_say(Bytecode *bc, const JechASTNode *node)
```

* Creates an instruction of type `OP_SAY`.
* Copies the value (`node->value`) to the `operand` field.
* Stores the original token type (e.g. `TOKEN_STRING`, `TOKEN_NUMBER`).
* Increments the instruction counter.

📦 This transforms the `say("hello")` command into:

```text
{ op: OP_SAY, operand: "hello", token_type: TOKEN_STRING }
```

---

### 2. **Helper function: `compile_keep`**

```c
static void compile_keep(Bytecode *bc, const JechASTNode *node)
```

* Creates an `OP_KEEP` instruction.
* Sets `name` to the variable identifier.
* Sets `operand` to the assigned value.
* Also stores the value type.

🧠 Example:

```jc
keep x = 42;
```

turns:

```text
{ op: OP_KEEP, name: "x", operand: "42", token_type: TOKEN_NUMBER }
```

---

### 3. **Main function: `_JechBytecode_CompileAll`**

```c
Bytecode _JechBytecode_CompileAll(JechASTNode **roots, int count)
```

#### 🚀 This is the function that scans the entire AST and compiles each node into an instruction:

* Initializes a new `Bytecode` structure with counter 0.
* Iterates over all the nodes in the AST (`roots[i]`).
* For each node, checks its type (`JECH_AST_SAY`, `JECH_AST_KEEP`...).

* Calls the corresponding compilation function.
* Manually adds the final `OP_END` instruction to the end of the program (marking the end of execution for the VM).

🧱 Example of an instruction sequence:

```text
[0] OP_KEEP ("x" = "42")
[1] OP_SAY ("x")
[2] OP_END
```

---
