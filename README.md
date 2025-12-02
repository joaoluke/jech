<div align="center">

[![Create Go App][repo_logo_img]][repo_url]

# Welcome to JECH Lang

[![Wiki][repo_wiki_img]][repo_wiki_url]
[![License][repo_license_img]][repo_license_url]

A programming language created with love, as a tribute to the next generation — and an invitation to anyone who wants to learn how languages are born, grow and become real.

</div>

## 📘 Introduction

> I bet you already know how to program. Maybe you’ve built cool things in Python, JavaScript, or even C. But... have you ever wondered how those languages actually work under the hood?
>
> How does a command like `print("Hello")` turn into instructions your machine can understand?
>
> JECH was created for exactly that curiosity — and for you. A language made by a programmer, for programmers. A step-by-step, simple, and accessible journey from raw code to running output, even if you’ve never touched compilers, interpreters, or low-level programming before.

The JECH Lang project was created to demonstrate, step by step, how a programming language can be built from scratch — in a simple, clear, and didactic way.
It’s designed for programming enthusiasts who want to dive into the fascinating world of language design, using C as a foundation, much like Python is built on CPython.

## 🎯 Purpose

JECH is a programming language created with the goal of **teaching, exploring, and celebrating the process of building a language from the ground up**.

It is designed to be simple, readable, and modular — enabling anyone, even with minimal experience in low-level programming, to follow its development and understand how a full interpreter works, from the lexer to the virtual machine.

JECH does not aim to compete with existing languages. Instead, it serves as a learning platform, a documented journey, and a source of inspiration for developers curious about compilers, language design, and the inner workings of interpreters.

## 📖 History

JECH was born from a personal desire to learn how a programming language is built — from the most fundamental concepts to a working interpreter.

But this project is not just for me.

JECH was also created to serve as a teaching resource — a **transparent, well-documented, and step-by-step guide** to how programming languages work internally. I wanted to share this learning experience with other developers who, like me, are curious about what happens under the hood.

## 💡 Why the name “JECH”?

The name "JECH" is a tribute to my two sons: **Jonathan Edwards** and **Charles Haddon**.
It combines the initials of their names as a symbolic gesture — representing not only the technical creation of a language, but also a legacy of love, curiosity, and inspiration.

## 🧠 Commands & Language Features

### ✅ `say(...)` — Output

> Prints a value to the terminal.

**Supported types:**

- ✅ **String** → `say("Hello, JECH!");`
- ✅ **Boolean** → `say(true);`, `say(false);`
- ✅ **Integer** → `say(42);`
- ✅ **Float** → `say(3.14);`
- ✅ **Variables** → `keep x = "Hi!"; say(x);`

---

### ✅ `keep` — Variable Declaration

> Declares a new variable that can be reused throughout the program.

```jc
keep name = "JECH";
keep age = 25;
keep active = true;

say(name);  // Output: JECH
say(age);   // Output: 25
```

---

### ✅ Variable Reassignment

> After declaring a variable with `keep`, you can reassign its value.

```jc
keep status = true;
status = false;
say(status);  // Output: false
```

---

### ✅ `when` — Conditional Structures

> Executes a block of code based on a condition.

#### Boolean Conditions

```jc
keep show = true;

when (show) {
    say("Hello!");
}
```

#### Comparison Operators (`==`, `>`, `<`)

```jc
keep age = 25;

when (age > 18) {
    say("You are an adult");
}
```

```jc
keep name = "João";

when (name == "João") {
    say("Welcome, João!");
}
```

---

### ✅ `else` — Alternative Branch

> Executes a block when the `when` condition is `false`.

```jc
keep age = 15;

when (age > 18) {
    say("adult");
}
else {
    say("minor");
}
// Output: minor
```

```jc
keep logged = false;

when (logged) {
    say("Welcome back!");
}
else {
    say("Please log in");
}
// Output: Please log in
```

## 📎 Error Handling Architecture (Preview)

Errors in JECH are modularized and categorized for clarity:

* `errors/error.h` → main error reporting function
* `errors/parser_error.c` → custom messages like "Missing semicolon after `keep`"
* `errors/lexer_error.c` → syntax issues like "Unterminated string"

This structure helps maintain clean separation between:

* Logic (e.g., `keep.c`)
* Presentation of messages (e.g., `parser_error.c`)

Example usage:

```c
if (t[i + 4].type != TOKEN_SEMICOLON) {
    report_missing_semicolon(&t[i + 4]);
    return NULL;
}
```

## 🚀 Quick Start

### Building JECH

```bash
# Clone the repository
git clone https://github.com/joaoluke/jech.git
cd jech

# Build the compiler
make

# Run a JECH program
./build/jech main.jc
```

### Your First Program

Create a file called `hello.jc`:

```jc
keep name = "World";
say("Hello, JECH!");
say(name);
```

Run it:

```bash
./build/jech hello.jc
# Output:
# Hello, JECH!
# World
```

---

## ⚙️ Architecture Pipeline

JECH implements a **fully modular interpreter pipeline**, inspired by how CPython works:

```text
┌─────────────────┐
│   Source Code   │  →  keep x = 10; say(x);
└────────┬────────┘
         ▼
┌─────────────────┐
│    Tokenizer    │  →  Breaks code into tokens: KEEP, IDENTIFIER, EQUALS, NUMBER...
└────────┬────────┘
         ▼
┌─────────────────┐
│     Parser      │  →  Validates syntax and creates AST nodes
└────────┬────────┘
         ▼
┌─────────────────┐
│       AST       │  →  Tree structure representing the program
└────────┬────────┘
         ▼
┌─────────────────┐
│    Bytecode     │  →  Converts AST to instructions: OP_KEEP, OP_SAY...
└────────┬────────┘
         ▼
┌─────────────────┐
│  Virtual Machine│  →  Executes bytecode and produces output
└─────────────────┘
```

### 🔬 Understanding Each Stage

Each stage is **fully modular** — you can inspect, modify, or replace any component independently. This makes JECH perfect for learning how interpreters work.

| Stage | File | Purpose |
|-------|------|---------|
| **Tokenizer** | `tokenizer.c` | Converts source code into tokens |
| **Parser** | `parser.c` | Validates syntax, creates AST |
| **AST** | `ast.c` | Tree structure for program representation |
| **Bytecode** | `bytecode.c` | Compiles AST into VM instructions |
| **VM** | `vm.c` | Executes bytecode instructions |

### 📂 Deep Dive Documentation

- [Architecture Overview](docs/en/architecture.md) — Full pipeline walkthrough
- [Tokenizer Design](docs/en/tokenizer.md) — How lexical analysis works
- [Parser](docs/en/parser.md) — Syntax validation and AST generation
- [AST](docs/en/ast.md) — Abstract Syntax Tree structure
- [Bytecode](docs/en/bytecode.md) — Instruction compilation
- [Virtual Machine](docs/en/vm.md) — Bytecode execution

## 🌐 JECH

📘 Available Languages:

- [🇺🇸 English (en)](README.md)
- [🇧🇷 Português (pt-BR)](docs/pt-BR/README.md)
- [🇪🇸 Español (es-ES)](docs/es-ES/README.md)

## 🤝 Contributors

Thanks goes to these wonderful people (🔥):

<table>
  <tr>
    <td align="center"><a href="https://github.com/joaoluke"><img src="https://avatars.githubusercontent.com/u/62743404?v=4?s=100" width="100px;" alt=""/><br /><sub><b>João Lucas</b></sub></a><br /><a href="https://github.com/joaoluke/react-dropdown-tree-select/issues?q=author%3ABaarishRain" title="Bug reports">Creator and Maintainer</a></td>
  </tr>
</table>

## ⚠️ License

[`Create Go App CLI`][repo_url] is free and open-source software licensed under
the [Apache 2.0 License][repo_license_url]. Official [logo][repo_logo_url] was
created by \[Vic Shóstak]\[author] and distributed under
[Creative Commons][repo_cc_url] license (CC BY-SA 4.0 International).

<!-- Repository -->

[repo_url]: https://github.com/create-go-app/cli
[repo_logo_url]: https://github.com/create-go-app/cli/wiki/Logo
[repo_logo_img]: images/jc_logo.png
[repo_license_url]: https://github.com/create-go-app/cli/blob/main/LICENSE
[repo_license_img]: https://img.shields.io/badge/license-Apache_2.0-red?style=for-the-badge&logo=none
[repo_cc_url]: https://creativecommons.org/licenses/by-sa/4.0/
[repo_v2_url]: https://github.com/create-go-app/cli/tree/v2
[repo_v3_url]: https://github.com/create-go-app/cli/tree/v3
[repo_issues_url]: https://github.com/create-go-app/cli/issues
[repo_pull_request_url]: https://github.com/create-go-app/cli/pulls
[repo_discussions_url]: https://github.com/create-go-app/cli/discussions
[repo_releases_url]: https://github.com/create-go-app/cli/releases
[repo_wiki_url]: https://github.com/create-go-app/cli/wiki
[repo_wiki_img]: https://img.shields.io/badge/docs-wiki_page-blue?style=for-the-badge&logo=none
[repo_wiki_faq_url]: https://github.com/create-go-app/cli/wiki/FAQ
