# 📖 JECH Glossary for High-Level Developers

A comprehensive guide to compiler/interpreter terminology, explained with analogies from Python, JavaScript, and PHP.

---

## 🔤 A

### Abstract Syntax Tree (AST)

**What it is:** A tree representation of your code's structure.

**Python equivalent:**
```python
import ast
tree = ast.parse("x = 10")
# Creates a tree structure representing the assignment
```

**Real-world analogy:** Like a family tree, but for code. Shows parent-child relationships between code elements.

**Example:**
```jc
keep x = 10;
```
Becomes:
```
KEEP_NODE
├── name: "x"
└── value: 10
```

---

### Assignment

**What it is:** Giving a value to a variable.

**Examples:**
```jc
x = 20;           // JECH
```
```python
x = 20            # Python
```
```javascript
x = 20;           // JavaScript
```
```php
$x = 20;          // PHP
```

---

## 🅱️ B

### Bytecode

**What it is:** Simplified, machine-friendly instructions that the VM executes.

**Python equivalent:** The `.pyc` files Python creates. You can see them with:
```python
import dis
dis.dis(lambda: print("hello"))
```

**Real-world analogy:** Like translating a recipe from English to a numbered list:
- Recipe: "Mix flour and water"
- Bytecode: "1. GET flour, 2. GET water, 3. MIX"

**JECH example:**
```jc
say("Hello");
```
Becomes:
```
OP_SAY "Hello"
```

---

## 🅲 C

### Compilation

**What it is:** Converting code from one form to another (usually human-readable to machine-readable).

**Types:**
1. **Ahead-of-Time (AOT):** Compile before running (C, Go)
2. **Just-in-Time (JIT):** Compile while running (Java, JavaScript V8)
3. **Bytecode:** Compile to intermediate form (Python, JECH)

**JECH uses:** Bytecode compilation (like Python)

---

### Compiler

**What it is:** A program that converts source code to another form.

**Examples:**
- **C compiler:** `gcc` converts C to machine code
- **Python compiler:** Converts Python to bytecode
- **JECH compiler:** Converts JECH to bytecode

**Not the same as:** Interpreter (which executes directly)

---

## 🅳 D

### Declaration

**What it is:** Introducing a new variable.

**JECH:**
```jc
keep x = 10;  // Declaration
```

**Python:**
```python
x = 10  # Declaration (implicit)
```

**JavaScript:**
```javascript
const x = 10;  // Declaration (explicit)
let y = 20;    // Declaration (explicit)
```

---

## 🅴 E

### Execution

**What it is:** Actually running the code and producing results.

**The journey:**
```
Source Code → Compilation → Execution → Output
```

**JECH:**
```jc
say("Hello");  // Source
↓ (compilation)
OP_SAY "Hello" // Bytecode
↓ (execution)
Hello          // Output
```

---

### Expression

**What it is:** Code that produces a value.

**Examples:**
```jc
10              // Number expression
"hello"         // String expression
x + 5           // Binary expression
arr[0]          // Index expression
```

**Contrast with:** Statement (which performs an action)

---

## 🅻 L

### Lexer

**What it is:** Another name for Tokenizer. Breaks code into tokens.

**Origin:** "Lexical analysis" = analyzing the vocabulary/words

**Python equivalent:**
```python
import tokenize
# Python's tokenizer
```

**See also:** Tokenizer

---

### Literal

**What it is:** A fixed value written directly in code.

**Examples:**
```jc
42              // Number literal
"hello"         // String literal
true            // Boolean literal
[1, 2, 3]       // Array literal
```

**Contrast with:** Variable (which holds a value)

---

## 🅾️ O

### Opcode

**What it is:** Short for "operation code". A bytecode instruction.

**JECH opcodes:**
```c
OP_SAY          // Print to screen
OP_KEEP         // Create variable
OP_ASSIGN       // Update variable
OP_ARRAY_NEW    // Create array
OP_WHEN         // Conditional
```

**Python equivalent:**
```python
import dis
# Python opcodes: LOAD_CONST, STORE_NAME, etc.
```

---

## 🅿️ P

### Parser

**What it is:** Validates syntax and creates structure from tokens.

**Real-world analogy:** A grammar checker that ensures sentences make sense.

**What it checks:**
- ✅ Correct order of tokens
- ✅ Matching parentheses/brackets
- ✅ Proper statement endings
- ✅ Valid expressions

**Example:**
```jc
say("Hello");  // ✓ Valid
say "Hello";   // ✗ Missing parentheses
```

---

### Pipeline

**What it is:** The series of stages code goes through.

**JECH pipeline:**
```
Source → Tokenizer → Parser → AST → Bytecode → VM
```

**Python pipeline:**
```
Source → Tokenizer → Parser → AST → Bytecode → CPython VM
```

**They're the same!**

---

## 🆁 R

### REPL

**What it is:** Read-Eval-Print Loop. Interactive programming mode.

**Examples:**
- Python: Type `python` in terminal
- Node.js: Type `node` in terminal
- JECH: Type `./build/jech` in terminal

**What it does:**
1. **Read** your input
2. **Eval**uate (execute) it
3. **Print** the result
4. **Loop** back to step 1

---

### Runtime

**What it is:** When your code is actually executing.

**Phases:**
1. **Compile-time:** When code is being compiled
2. **Runtime:** When code is being executed

**Example:**
```jc
keep x = 10;    // Compile-time: create variable
say(x);         // Runtime: look up and print x
```

---

## 🆂 S

### Statement

**What it is:** A complete instruction that performs an action.

**Examples:**
```jc
say("Hello");           // Statement
keep x = 10;            // Statement
when (x > 5) { ... }    // Statement
```

**Contrast with:** Expression (which produces a value)

---

### Syntax

**What it is:** The rules for writing valid code.

**Examples of syntax rules:**
- Statements end with `;`
- Strings use quotes `"..."`
- Blocks use braces `{ ... }`
- Arrays use brackets `[ ... ]`

**Syntax error:** Breaking these rules
```jc
say("Hello"  // ✗ Missing )
```

---

## 🆃 T

### Token

**What it is:** A categorized piece of code.

**Types:**
- **Keywords:** `say`, `keep`, `when`
- **Identifiers:** Variable names
- **Literals:** `42`, `"hello"`, `true`
- **Operators:** `+`, `-`, `>`, `==`
- **Punctuation:** `(`, `)`, `;`, `{`, `}`

**Example:**
```jc
say("Hello");
```
Tokens:
```
[say] [(] ["Hello"] [)] [;]
```

---

### Tokenizer

**What it is:** The first stage of compilation. Breaks code into tokens.

**Real-world analogy:** Reading a sentence and identifying: noun, verb, punctuation.

**Python equivalent:**
```python
import tokenize
import io

code = 'print("hello")'
tokens = tokenize.tokenize(io.BytesIO(code.encode()).readline)
for token in tokens:
    print(token)
```

**See also:** Lexer

---

### Type

**What it is:** The kind of value (number, string, boolean, etc.)

**JECH types:**
```jc
10              // Number
"hello"         // String
true            // Boolean
[1, 2, 3]       // Array
```

**Type systems:**
- **Static:** Types checked at compile-time (C, Java)
- **Dynamic:** Types checked at runtime (Python, JavaScript, JECH)

---

## 🆅 V

### Variable

**What it is:** A named storage location for a value.

**JECH:**
```jc
keep x = 10;    // Create variable
x = 20;         // Update variable
say(x);         // Use variable
```

**Analogy:** Like a labeled box where you can store things.

---

### Virtual Machine (VM)

**What it is:** Software that executes bytecode instructions.

**Examples:**
- **CPython:** Python's VM
- **JVM:** Java Virtual Machine
- **V8:** JavaScript VM (in Chrome)
- **JECH VM:** JECH's VM

**What it does:**
1. Reads bytecode instructions
2. Executes them one by one
3. Manages memory (variables, arrays)
4. Produces output

**Real-world analogy:** A chef following a recipe (bytecode) step by step.

---

## 📊 Comparison Table

| Term | Python | JavaScript | PHP | JECH |
|------|--------|------------|-----|------|
| **Print** | `print()` | `console.log()` | `echo` | `say()` |
| **Variable** | `x = 10` | `const x = 10` | `$x = 10` | `keep x = 10` |
| **Array** | `[1, 2, 3]` | `[1, 2, 3]` | `[1, 2, 3]` | `[1, 2, 3]` |
| **If** | `if x > 5:` | `if (x > 5)` | `if ($x > 5)` | `when (x > 5)` |
| **Bytecode** | `.pyc` files | V8 bytecode | Opcache | JECH bytecode |
| **VM** | CPython | V8/SpiderMonkey | Zend Engine | JECH VM |

---

## 🎓 Learning Tips

### Start Here
1. **Token** - Understand what tokens are
2. **Tokenizer** - See how code becomes tokens
3. **Parser** - Learn how tokens become structure
4. **AST** - Understand tree representation
5. **Bytecode** - See simplified instructions
6. **VM** - Watch execution happen

### Use Analogies
- **Tokenizer** = Reading and identifying words
- **Parser** = Grammar checking
- **AST** = Family tree for code
- **Bytecode** = Numbered recipe steps
- **VM** = Chef following the recipe

### Compare to What You Know
Every concept has a Python/JavaScript/PHP equivalent. Use that knowledge!

---

## 🔗 Related Documentation

- **[For Beginners](FOR_BEGINNERS.md)** - Concepts explained simply
- **[Architecture](architecture.md)** - How everything fits together
- **[Tokenizer](tokenizer.md)** - Deep dive into tokenization
- **[Parser](parser.md)** - Deep dive into parsing
- **[VM](vm.md)** - Deep dive into execution

---

**Remember:** These terms sound scary, but they're just names for simple concepts you already understand from using Python, JavaScript, or PHP!
