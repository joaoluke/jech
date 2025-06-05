# 🧠 Interpreter Flow — JECH Language

This document explains the full execution pipeline of the JECH programming language — from reading the source file to executing instructions like `say("Hello")`. Understanding this flow helps you navigate the architecture and extend the language with new commands.

---

## 🔁 Step-by-Step Flow

Let's walk through what happens when the interpreter runs a command like:

```jc
say("Hello");
```

### 1. 📄 File Reading

* **File:** `src/utils.c` → `read_file_content()`
* The `.jc` file is loaded into memory as a single string.

---

### 2. 🧹 Lexer (Tokenization)

* **File:** `src/compiler/lexer.c`
* Converts the raw string into a list of **tokens**, such as:

```text
Token: Type=TOKEN_SAY, Value="say"
Token: Type=TOKEN_LPAREN, Value="("
Token: Type=TOKEN_STRING, Value="Hello"
Token: Type=TOKEN_RPAREN, Value=")"
Token: Type=TOKEN_SEMICOLON, Value=";"
```

---

### 3. 🌲 Parser (AST Construction)

* **File:** `src/compiler/parser.c`
* Transforms the token list into an **AST** (Abstract Syntax Tree), which represents the structure of the command:

```c
ASTNode {
  type: AST_SAY,
  value: "Hello"
}
```

---

### 4. 🧱 Bytecode Compiler

* **File:** `src/compiler/bytecode.c`
* Converts the AST into a sequence of **bytecode instructions**:

```c
Instruction {
  op: OP_SAY,
  operand: "Hello"
}
Instruction {
  op: OP_END
}
```

---

### 5. 🧠 Virtual Machine (VM Execution)

* **File:** `src/compiler/vm.c`
* The VM iterates through the bytecode and executes each instruction.
* For `OP_SAY`, it prints the value:

```c
printf("%s\n", operand);
```

Output:

```text
Hello
```

---

## 🗂️ Summary of Files Involved

| Step | Responsibility       | File(s)                   |
| ---- | -------------------- | ------------------------- |
| 1    | Read `.jc` file      | `src/utils.c`             |
| 2    | Tokenize input       | `src/compiler/lexer.c`    |
| 3    | Build AST            | `src/compiler/parser.c`   |
| 4    | Compile to bytecode  | `src/compiler/bytecode.c` |
| 5    | Execute instructions | `src/compiler/vm.c`       |

---

## 📌 Notes

* This architecture is modular, so adding new commands like `keep` or `when` only requires updates to:

  * Lexer: recognize new tokens
  * Parser: understand new syntax
  * Bytecode: compile it
  * VM: execute it

* Errors are handled in:

  * `src/compiler/errors.c` (e.g., unknown tokens)
  * `src/commands/say.c` (e.g., malformed say command)

---

## ✅ Example Use Case

Given this file `examples/hello.jc`:

```jc
say("Hello, JECH!");
```

Running:

```bash
./jech examples/hello.jc
```

