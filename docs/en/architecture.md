# 🧱 Project Architecture - JECH Language

This document outlines the architecture and folder structure of the JECH Language interpreter.
It is designed to be **modular**, **educational**, and easy to scale as the language grows.

---

## 🗂 Folder Structure

```
jech-lang/
├── include/              # Header files for project-wide access
│   ├── jech.h            # Main project header
│   ├── utils.h
│   ├── errors.h
│   
│   ├── core/
│   │   ├── lexer.h
│   │   ├── parser.h
│   │   ├── bytecode.h
│   │   └── vm.h
│
│   ├── commands/         # Shared interface for language commands
│   │   └── say.h
│
├── src/
│   ├── main.c            # Entry point of the interpreter
│   ├── utils.c           # Utility functions (e.g., file reading)
│
│   ├── core/             # Core interpreter logic
│   │   ├── lexer.c
│   │   ├── parser.c
│   │   ├── bytecode.c
│   │   ├── vm.c
│   │   └── errors.c
│
│   └── commands/         # Language-specific command implementations
│       └── say.c         # Handles say(...) execution
│
├── examples/             # Example .jc programs for testing and showcasing
│   └── say.jc
│
├── docs/                 # Project documentation
│   ├── en/
│   ├── es-ES/
│   └── pt-BR/
│
├── README.md
├── CHANGELOG.md
└── jech (compiled binary)
```

---

## 🔄 Interpreter Flow

The interpreter follows the classical compilation pipeline:

```
📁 .jc source file
   ↓
🔍 Lexer (tokenizer)        →   Produces TokenList
   ↓
🧠 Parser                   →   Builds AST (Abstract Syntax Tree)
   ↓
⚙️  Bytecode Compiler       →   Converts AST into bytecode instructions
   ↓
🖥 Virtual Machine (VM)     →   Executes bytecode instruction-by-instruction
```

Each step is modular and separated into its own file for clarity and ease of maintenance.

---

## 🧱 Compiler Modules (src/compiler/)

* `lexer.c` — Responsible for breaking raw text into tokens.
* `parser.c` — Converts the stream of tokens into AST nodes.
* `bytecode.c` — Compiles AST nodes into instructions.
* `vm.c` — Executes instructions one by one.
* `errors.c` — Centralized error handling and reporting.

---

## 🧩 Language Commands (src/commands/)

Each command in JECH is treated as a modular component. These live in the `commands/` folder.

* `say.c` — Implements behavior for the `say(...)` instruction, currently supporting:

  * Strings
  * Numbers
  * Floats
  * Booleans

More commands like `keep` and `when` will follow the same structure.

---

## 🔧 Utilities (src/utils.c)

Helper functions like `read_file_content`, string manipulation, and file handling.

---

## 📌 Goals of the Architecture

* **Clarity:** Separate responsibilities for educational purposes.
* **Scalability:** Easy to add new commands or extend compiler phases.
* **Maintainability:** Isolated and reusable modules.
* **Documentation-first:** Well-documented for those learning language implementation.

---

## ✅ Next Steps

* Implement modules for `keep` and `when`
* Improve error reporting (line numbers, clearer messages)
* Add testing suite for each compiler phase
* Add memory management and variable support

---
