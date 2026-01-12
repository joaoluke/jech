<div align="center">

[![JECH Logo][repo_logo_img]][repo_url]

# JECH Programming Language

[![Wiki][repo_wiki_img]][repo_wiki_url]
[![License][repo_license_img]][repo_license_url]

📖 **Read this in other languages:** [English](README_NEW.md) | [Português (Brasil)](README_pt-BR.md)

**Ever wondered how Python, JavaScript, or PHP actually work under the hood?**

JECH is a programming language built from scratch to teach you exactly that — in a clear, documented, and accessible way.

</div>

---

## 🎯 Who Is This For?

**You're a developer who:**
- ✅ Knows Python, JavaScript, or PHP
- ✅ Writes code every day
- ✅ Wonders "how does `print()` actually work?"
- ❌ Has never touched C or compilers
- ❌ Doesn't know what "bytecode" means
- ❌ Thinks "lexer" sounds intimidating

**Perfect!** JECH was built specifically for you.

---

## 🤔 What Problem Does JECH Solve?

### The Problem

You know how to use Python:
```python
print("Hello")
x = 10
if x > 5:
    print(x)
```

But you have **no idea** how Python actually executes this. It's magic! ✨

### The Solution

JECH shows you **exactly** how it works, step by step:

```
Your Code → Tokenizer → Parser → AST → Bytecode → VM → Output
   📝          🔤         🧱      🌳       🔧       ⚡      ✨
```

Every stage is:
- ✅ **Documented** with examples
- ✅ **Explained** in terms you already know
- ✅ **Visible** - you can see it happen
- ✅ **Modular** - each piece is independent

---

## 🚀 Quick Start (5 minutes)

### 1. Install

```bash
git clone https://github.com/yourusername/jech
cd jech
make
```

### 2. Try the REPL (Interactive Mode)

```bash
./build/jech
```

```jc
>>> keep x = 10;
>>> say(x);
10

>>> keep name = "JECH";
>>> say(name);
JECH

>>> keep numbers = [1, 2, 3];
>>> say(numbers[0]);
1
```

**It's like Python's interactive mode!**

### 3. Run a Program

```bash
./build/jech examples/17_arrays_basic.jc
```

---

## 📖 Learn How Languages Work

### For Python Developers

**You know this:**
```python
print("Hello")
```

**JECH shows you this happens:**

```
1. Tokenizer breaks it into: [print] [(] ["Hello"] [)] 
2. Parser understands: "This is a print statement"
3. Compiler generates: OP_PRINT "Hello"
4. VM executes: Output "Hello" to screen
```

**Same process Python uses!** (CPython does exactly this)

### For JavaScript Developers

**You know this:**
```javascript
const x = 10;
console.log(x);
```

**JECH shows you:**
- How V8 tokenizes your code
- How the parser builds an AST
- How bytecode is generated
- How the VM executes it

**Same principles, different syntax!**

### For PHP Developers

**You know this:**
```php
$x = 10;
echo $x;
```

**JECH reveals:**
- How Zend Engine processes your code
- How opcodes are generated
- How the executor runs them

**Same architecture!**

---

## 🎓 Learning Path

### Level 1: Use It (Start Here!)

**Goal:** Get comfortable with JECH syntax

```bash
# Try the REPL
./build/jech

# Run examples
./build/jech examples/01_hello_world.jc
./build/jech examples/17_arrays_basic.jc
```

**Time:** 15 minutes  
**Docs:** [Language Features](#-language-features)

---

### Level 2: Understand the Concepts

**Goal:** Learn how languages work (no C required!)

**Read:** [For Beginners Guide](docs/en/FOR_BEGINNERS.md)

This guide explains:
- What is a tokenizer? (with Python analogies)
- What is a parser? (with JavaScript examples)
- What is bytecode? (like Python's `.pyc` files)
- What is a VM? (like CPython)

**Time:** 30 minutes  
**Prerequisites:** None! Just curiosity

---

### Level 3: See It In Action

**Goal:** Watch code transform through each stage

**Read:** [Architecture Overview](docs/en/architecture.md)

Follow a single line of code:
```jc
say("Hello");
```

Through all 5 stages:
1. Tokenizer → `[say] [(] ["Hello"] [)] [;]`
2. Parser → `SAY_STATEMENT`
3. AST → `SAY_NODE { value: "Hello" }`
4. Bytecode → `OP_SAY "Hello"`
5. VM → `print("Hello")`

**Time:** 45 minutes  
**Prerequisites:** Level 2

---

### Level 4: Deep Dive into Components

**Goal:** Understand each component in detail

**Read:**
- [Tokenizer](docs/en/tokenizer.md) - How code becomes tokens
- [Parser](docs/en/parser.md) - How tokens become structure
- [AST](docs/en/ast.md) - How structure becomes trees
- [Bytecode](docs/en/bytecode.md) - How trees become instructions
- [VM](docs/en/vm.md) - How instructions become execution

**Time:** 2-3 hours  
**Prerequisites:** Level 3

---

### Level 5: Contribute

**Goal:** Add features, fix bugs, improve docs

**Read:** [Contributing Guide](CONTRIBUTING.md)

You can contribute even without knowing C:
- Write example programs
- Improve documentation
- Report bugs
- Suggest features
- Write tests

**Time:** Ongoing  
**Prerequisites:** Enthusiasm!

---

## 🧠 Language Features

### Variables

```jc
keep x = 10;
keep name = "João";
keep active = true;

say(x);        // 10
say(name);     // João
say(active);   // true
```

**Like:** Python's `x = 10`, JavaScript's `const x = 10`, PHP's `$x = 10`

---

### Arrays

```jc
keep numbers = [1, 2, 3, 4, 5];
keep names = ["Alice", "Bob", "Charlie"];
keep mixed = [42, "text", true];

say(numbers[0]);  // 1
say(names[1]);    // Bob
say(mixed[2]);    // true
```

**Like:** Python lists, JavaScript arrays, PHP arrays

---

### Conditionals

```jc
keep age = 20;

when (age > 18) {
    say("Adult");
}
else {
    say("Minor");
}
```

**Like:** Python's `if`, JavaScript's `if`, PHP's `if`

---

### Output

```jc
say("Hello, World!");
say(42);
say(true);
say(myVariable);
say(myArray[0]);
```

**Like:** Python's `print()`, JavaScript's `console.log()`, PHP's `echo`

---

## 🏗️ Architecture (The Magic Revealed)

### The Pipeline

Every line of code goes through 5 stages:

```
┌─────────────┐
│ Source Code │  say("Hello");
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Tokenizer  │  [say] [(] ["Hello"] [)] [;]
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Parser    │  SAY_STATEMENT { value: "Hello" }
└──────┬──────┘
       │
       ▼
┌─────────────┐
│     AST     │  SAY_NODE → "Hello"
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Bytecode   │  [OP_SAY "Hello"]
└──────┬──────┘
       │
       ▼
┌─────────────┐
│     VM      │  Execute: print "Hello"
└──────┬──────┘
       │
       ▼
    Output: Hello
```

### Real-World Comparison

**This is exactly how Python works:**

| JECH Stage | Python Equivalent | What It Does |
|------------|-------------------|--------------|
| Tokenizer | `tokenize` module | Breaks code into pieces |
| Parser | `ast.parse()` | Validates syntax |
| AST | `ast.AST` | Creates tree structure |
| Bytecode | `.pyc` files | Compiles to instructions |
| VM | CPython | Executes instructions |

**Mind blown?** 🤯 Now you know how Python works!

---

## 🧪 Testing & Quality

JECH has **70 automated tests** covering:
- ✅ Tokenizer (32 assertions)
- ✅ Parser (25 assertions)
- ✅ VM (6 assertions)
- ✅ Integration (7 assertions)

### Run Tests

```bash
./run_tests.sh
```

### Pre-Commit Hooks

Automatically run tests before every commit:

```bash
./install_hooks.sh
```

**Like:** Python's `pytest`, JavaScript's `jest`, PHP's `PHPUnit`

---

## 📚 Documentation

### For Beginners (Start Here!)

- **[For Beginners Guide](docs/en/FOR_BEGINNERS.md)** ⭐
  - No C knowledge required
  - Uses Python/JavaScript analogies
  - Explains every concept simply

### Architecture

- **[Architecture Overview](docs/en/architecture.md)**
  - Complete pipeline explanation
  - Visual diagrams
  - Step-by-step examples

### Components (Deep Dive)

- **[Tokenizer](docs/en/tokenizer.md)** - Lexical analysis
- **[Parser](docs/en/parser.md)** - Syntax analysis
- **[AST](docs/en/ast.md)** - Tree structures
- **[Bytecode](docs/en/bytecode.md)** - Compilation
- **[VM](docs/en/vm.md)** - Execution

### Contributing

- **[Contributing Guide](CONTRIBUTING.md)**
- **[Setup Guide](SETUP.md)**
- **[Test Documentation](tests/README.md)**

---

## 💡 Why JECH?

### Educational

**Learn how your favorite languages work:**
- Python (CPython)
- JavaScript (V8, SpiderMonkey)
- PHP (Zend Engine)
- Ruby (YARV)

All use the same principles JECH demonstrates!

### Transparent

**Every stage is visible:**
```bash
# See tokens
./build/jech --debug-tokens myfile.jc

# See AST
./build/jech --debug-ast myfile.jc

# See bytecode
./build/jech --debug-bytecode myfile.jc
```

### Practical

**Real features:**
- ✅ Variables
- ✅ Arrays
- ✅ Conditionals
- ✅ REPL
- ✅ Error messages
- ✅ Type system (coming soon)

### Simple

**Small codebase:**
- ~3,000 lines of C
- Well-documented
- Modular design
- Easy to understand

---

## 🎯 Project Goals

### Primary Goal: Education

JECH exists to teach how programming languages work. Every design decision prioritizes **clarity** over **performance**.

### Secondary Goal: Inspiration

Show that building a language is **achievable**. You don't need a PhD or 10 years of C experience.

### Non-Goal: Production Use

JECH is **not** meant to replace Python, JavaScript, or PHP. It's a learning tool.

---

## 💖 The Story Behind JECH

JECH was created as:
1. **A learning journey** - Understanding how languages work
2. **A teaching tool** - Sharing that knowledge with others
3. **A tribute** - To my sons Jonathan Edwards and Charles Haddon (J-E-C-H)

It's built with love, for learners, by a learner.

---

## 🤝 Contributing

We welcome contributions from developers of **all experience levels**!

### You Can Help By:

- 📝 Writing example programs
- 📖 Improving documentation
- 🐛 Reporting bugs
- 💡 Suggesting features
- 🧪 Writing tests
- 🌍 Translating docs

**No C experience required!**

See [CONTRIBUTING.md](CONTRIBUTING.md) for details.

---

## 📊 Project Stats

- **Language:** C
- **Lines of Code:** ~3,000
- **Tests:** 70 (100% passing)
- **Documentation:** 6 detailed guides
- **Examples:** 22 programs
- **Contributors:** Growing!

---

## 🗺️ Roadmap

### ✅ Completed

- [x] Tokenizer
- [x] Parser
- [x] AST
- [x] Bytecode compiler
- [x] Virtual Machine
- [x] Variables
- [x] Arrays
- [x] Conditionals
- [x] REPL
- [x] Comprehensive tests
- [x] Documentation

### 🚧 In Progress

- [ ] Functions
- [ ] Loops
- [ ] Type system
- [ ] Standard library

### 🔮 Future

- [ ] Garbage collection
- [ ] Optimization passes
- [ ] JIT compilation
- [ ] Package manager

See [roadmap.md](roadmap.md) for details.

---

## 📖 Learn More

### Recommended Reading Order

1. **[For Beginners](docs/en/FOR_BEGINNERS.md)** - Start here!
2. **[Architecture](docs/en/architecture.md)** - See the big picture
3. **[Tokenizer](docs/en/tokenizer.md)** - First stage
4. **[Parser](docs/en/parser.md)** - Second stage
5. **[VM](docs/en/vm.md)** - Final stage

### External Resources

- [Crafting Interpreters](https://craftinginterpreters.com/) - Excellent book
- [CPython Internals](https://realpython.com/cpython-source-code-guide/) - How Python works
- [V8 Blog](https://v8.dev/blog) - How JavaScript works

---

## ⚖️ License

JECH is free and open-source software licensed under the [Apache 2.0 License][repo_license_url].

---

## 🙏 Acknowledgments

- **Python** - For inspiration and design patterns
- **Crafting Interpreters** - For educational approach
- **The community** - For feedback and contributions

---

<div align="center">

**Ready to learn how languages work?**

[Get Started](docs/en/FOR_BEGINNERS.md) | [Documentation](docs/en/architecture.md) | [Contribute](CONTRIBUTING.md)

Made with ❤️ for curious developers

</div>

<!-- Links -->
[repo_url]: https://github.com/yourusername/jech
[repo_logo_img]: images/jc_logo.png
[repo_license_url]: https://github.com/yourusername/jech/blob/main/LICENSE
[repo_license_img]: https://img.shields.io/badge/license-Apache_2.0-red?style=for-the-badge&logo=none
[repo_wiki_url]: https://github.com/yourusername/jech/wiki
[repo_wiki_img]: https://img.shields.io/badge/docs-wiki_page-blue?style=for-the-badge&logo=none
