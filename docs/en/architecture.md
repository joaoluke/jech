# 📐 JECH Lang Architecture Overview

This document explains the **complete compilation and execution pipeline** of the JECH language. We'll trace how source code transforms into output, step by step.

## 🎯 The Big Picture

```text
┌──────────────┐    ┌───────────┐    ┌────────┐    ┌──────────┐    ┌─────┐
│ Source Code  │ → │ Tokenizer │ → │ Parser │ → │ Bytecode │ → │ VM  │ → Output
└──────────────┘    └───────────┘    └────────┘    └──────────┘    └─────┘
     .jc file         Tokens          AST         Instructions    Execution
```

Let's trace this complete example through every stage:

```jc
keep age = 25;
when (age > 18) {
    say("adult");
}
else {
    say("minor");
}
```

---

## 1. 🧾 Tokenizer (Lexical Analysis)

**File:** `tokenizer.c`  
**Function:** `_JechTokenizer_Lex`

### 🔧 What it does:

Reads the source code character by character and groups them into **tokens** — the smallest meaningful units of the language.

### Our Example Becomes:

```text
[0]  TOKEN_KEEP       "keep"
[1]  TOKEN_IDENTIFIER "age"
[2]  TOKEN_EQUALS     "="
[3]  TOKEN_NUMBER     "25"
[4]  TOKEN_SEMICOLON  ";"
[5]  TOKEN_WHEN       "when"
[6]  TOKEN_LPAREN     "("
[7]  TOKEN_IDENTIFIER "age"
[8]  TOKEN_GT         ">"
[9]  TOKEN_NUMBER     "18"
[10] TOKEN_RPAREN     ")"
[11] TOKEN_LBRACE     "{"
[12] TOKEN_SAY        "say"
[13] TOKEN_LPAREN     "("
[14] TOKEN_STRING     "adult"
[15] TOKEN_RPAREN     ")"
[16] TOKEN_SEMICOLON  ";"
[17] TOKEN_RBRACE     "}"
[18] TOKEN_ELSE       "else"
[19] TOKEN_LBRACE     "{"
[20] TOKEN_SAY        "say"
[21] TOKEN_LPAREN     "("
[22] TOKEN_STRING     "minor"
[23] TOKEN_RPAREN     ")"
[24] TOKEN_SEMICOLON  ";"
[25] TOKEN_RBRACE     "}"
[26] TOKEN_EOF
```

📚 [Tokenizer Documentation](tokenizer.md)

---

## 2. 🧱 Parser

**File:** `parser.c`  
**Function:** `_JechParser_ParseAll`

### 🔧 What it does:

Validates that tokens form correct **syntax patterns** and creates **AST nodes** representing the program structure.

### Our Example Becomes:

The parser recognizes two statements and creates two AST root nodes:

```text
roots[0] = JECH_AST_KEEP
           ├── name: "age"
           └── value: "25"

roots[1] = JECH_AST_WHEN
           ├── left (condition): JECH_AST_BIN_OP (>)
           │                     ├── left: JECH_AST_IDENTIFIER ("age")
           │                     └── right: JECH_AST_NUMBER_LITERAL ("18")
           ├── right (then): JECH_AST_SAY ("adult")
           └── else_branch: JECH_AST_SAY ("minor")
```

📚 [Parser Documentation](parser.md)

---

## 3. 🌳 AST (Abstract Syntax Tree)

**File:** `ast.c`  
**Function:** `_JechAST_CreateNode`

### 🔧 What it does:

Provides the **data structure** for representing program elements as a tree. Each node contains:
- **Type** — what kind of element (SAY, KEEP, WHEN, etc.)
- **Value/Name** — associated data
- **Children** — left, right, and else_branch pointers

### Why Trees?

Trees capture **hierarchical relationships**. The `when` statement contains a condition AND a body AND an else branch — this nesting is natural in a tree structure.

📚 [AST Documentation](ast.md)

---

## 4. 🔤 Bytecode Compiler

**File:** `bytecode.c`  
**Function:** `_JechBytecode_CompileAll`

### 🔧 What it does:

Transforms the AST into a **linear sequence of instructions** that the VM can execute.

### Our Example Becomes:

```text
[0] OP_KEEP
    name: "age"
    operand: "25"
    token_type: TOKEN_NUMBER

[1] OP_WHEN
    name: "age"              // Variable to compare
    bin_op: TOKEN_GT         // > operator
    operand: "18"            // Compare against
    operand_right: "adult"   // Then-branch output
    has_else: 1
    else_operand: "minor"    // Else-branch output

[2] OP_END
```

📚 [Bytecode Documentation](bytecode.md)

---

## 5. 🧠 Virtual Machine (VM)

**File:** `vm.c`  
**Function:** `_JechVM_Execute`

### 🔧 What it does:

Executes bytecode instructions one by one, managing variables and producing output.

### Our Example Executes:

```text
Step 1: OP_KEEP
        → Store variable: age = "25"
        → Variables: [{ name: "age", value: "25" }]

Step 2: OP_WHEN
        → Get variable "age" → "25"
        → Compare: 25 > 18 → true
        → Execute then-branch: print "adult"

Step 3: OP_END
        → Stop execution
```

### Terminal Output:

```
adult
```

📚 [VM Documentation](vm.md)

---

## ✅ Summary

Our complete journey:

```text
Source Code (.jc)
       │
       ▼
┌─────────────┐
│  Tokenizer  │  "keep age = 25;" → [KEEP, IDENTIFIER, EQUALS, NUMBER, SEMICOLON]
└──────┬──────┘
       ▼
┌─────────────┐
│   Parser    │  Tokens → AST nodes with structure
└──────┬──────┘
       ▼
┌─────────────┐
│  Bytecode   │  AST → [OP_KEEP, OP_WHEN, OP_END]
└──────┬──────┘
       ▼
┌─────────────┐
│     VM      │  Execute instructions → "adult"
└─────────────┘
```

---

## 🧩 File Responsibility Summary

| Stage | File | Key Function | Purpose |
|-------|------|--------------|---------|
| **Tokenizer** | `tokenizer.c` | `_JechTokenizer_Lex` | Break source into tokens |
| **Parser** | `parser.c` | `_JechParser_ParseAll` | Validate syntax, create AST |
| **AST** | `ast.c` | `_JechAST_CreateNode` | Tree structure for program |
| **Bytecode** | `bytecode.c` | `_JechBytecode_CompileAll` | Compile AST to instructions |
| **VM** | `vm.c` | `_JechVM_Execute` | Execute bytecode |

---

## 💡 Why This Architecture?

1. **Modularity** — each stage is independent and testable
2. **Debuggability** — you can inspect output at any stage
3. **Extensibility** — add new features without rewriting everything
4. **Educational** — mirrors how real languages (Python, JavaScript) work

> This modular setup makes JECH an excellent educational tool for understanding compilers and interpreters.

---

## 🔗 Deep Dive Links

- [Tokenizer](tokenizer.md) — Lexical analysis details
- [Parser](parser.md) — Syntax validation and AST generation
- [AST](ast.md) — Tree structure and memory management
- [Bytecode](bytecode.md) — Instruction compilation
- [VM](vm.md) — Bytecode execution
