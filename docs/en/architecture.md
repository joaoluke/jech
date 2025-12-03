# 📐 JECH Lang Architecture Overview

This document explains the full compilation and execution pipeline of the JECH language, from raw source code to final output — using the example:

```jc
say("Hello, World!");
```

We'll break down how this code passes through each stage:

---

## 1. 🧾 Tokenizer (Lexical Analysis)

**File:** `tokenizer.c`
**Function:** `_JechTokenizer_Lex`

### 🔧 What it does:

Converts raw source code into a stream of **tokens**.

### Example:

```c
say("Hello, World!");
```

becomes:

```text
TOKEN_SAY       → "say"
TOKEN_LPAREN    → "("
TOKEN_STRING    → "Hello, World!"
TOKEN_RPAREN    → ")"
TOKEN_SEMICOLON → ";"
```

- [Tokenizer Documentation](tokenizer.md)

---

## 2. 🧱 Parser

**File:** `parser.c`
**Function:** `_JechParser_ParseAll`

### 🔧 What it does:

Reads the tokens and identifies **instruction patterns**. It creates a list of **AST root nodes**.

### Output:

One AST node representing the `say("Hello, World!")` instruction.

- [Parser Documentation](parser.md)

---

## 3. 🌳 AST (Abstract Syntax Tree)

**File:** `ast.c`
**Function:** `_JechAST_CreateNode`

### 🔧 What it does:

Builds structured trees to represent the meaning of the code.
Each instruction becomes a node, possibly with children (not yet in this version).

### Example:

```text
• JECH_AST_SAY ("Hello, World!")
```

The AST for our example has just one node.

- [Ast Documentation](ast.md)

---

## 4. 🔤 Bytecode Compiler

**File:** `bytecode.c`
**Function:** `_JechBytecode_CompileAll`

### 🔧 What it does:

Converts AST nodes into **bytecode instructions**.

### Example:

```text
[0] OP_SAY  → operand: "Hello, World!"
[1] OP_END
```

This bytecode can be stored, optimized, or executed directly.

- [Bytecode Documentation](bytecode.md)

---

## 5. 🧠 Virtual Machine (VM)

**File:** `vm.c`
**Function:** `_JechVM_Execute`

### 🔧 What it does:

Reads and executes bytecode instructions.

### Example:

Executes:

```text
OP_SAY  → prints "Hello, World!"
OP_END  → stops execution
```

Terminal output:

```
Hello, World!
```

- [VM Documentation](vm.md)

---

## ✅ Summary

```text
say("Hello, World!");
       │
       ▼
[Tokenizer] → [Parser] → [AST] → [Bytecode] → [VM Execution]
```

Each step in JECH is modular and extensible. You can inspect or modify any stage of this pipeline independently, making it a great tool for learning or experimenting with language design.

---

## 🧩 File Responsibility Summary

| Stage           | File          | Key Function               |
| --------------- | ------------- | -------------------------- |
| Tokenizer       | `tokenizer.c` | `_JechTokenizer_Lex`       |
| Parser          | `parser.c`    | `_JechParser_ParseAll`     |
| AST Builder     | `ast.c`       | `_JechAST_CreateNode`      |
| Bytecode Gen    | `bytecode.c`  | `_JechBytecode_CompileAll` |
| Virtual Machine | `vm.c`        | `_JechVM_Execute`          |

> This modular setup makes JECH an excellent educational tool for understanding compilers and interpreters.
