# 🎓 JECH for High-Level Developers

**Welcome!** If you're a Python, JavaScript, or PHP developer curious about how programming languages actually work, you're in the right place.

## 🤔 "I've never touched C or compilers. Can I still understand this?"

**Absolutely!** This guide is specifically written for you. We'll use analogies from languages you already know.

---

## 🌟 The Big Picture: How Does Code Actually Run?

### In Python/JavaScript/PHP (What you know)

```python
# Python
print("Hello")
```

You write this, hit run, and it works. **But what happens behind the scenes?**

### The Magic Revealed

Your code goes through a **pipeline** (like a factory assembly line):

```
Your Code → Tokenizer → Parser → Compiler → Execution
   📝          🔤         🧱        🔧         ⚡
```

**Think of it like cooking:**
1. **Recipe (Your Code)**: "say('Hello')"
2. **Reading ingredients (Tokenizer)**: Identify "say", "(", "Hello", ")", ";"
3. **Understanding steps (Parser)**: "Oh, this is a print command with a string"
4. **Preparing (Compiler)**: Convert to machine-friendly instructions
5. **Cooking (Execution)**: Actually run it!

---

## 📚 Chapter 1: The Tokenizer (Breaking Code into Pieces)

### What is it?

**In Python terms:** Remember how Python knows that `print("hello")` has a function name, parentheses, and a string? The tokenizer does that!

**Real-world analogy:** Like reading a sentence and identifying: verb, noun, punctuation.

### Example

**Your code:**
```jc
say("Hello, World!");
```

**What the tokenizer sees:**
```
1. "say"     → KEYWORD (like 'print' in Python)
2. "("       → OPENING PARENTHESIS
3. "Hello, World!" → STRING (text in quotes)
4. ")"       → CLOSING PARENTHESIS  
5. ";"       → SEMICOLON (end of statement)
```

### Why is this needed?

Computers don't understand text. The tokenizer converts your code into **labeled pieces** that the next stage can process.

**JavaScript equivalent:**
```javascript
// When you write this:
console.log("Hi");

// JavaScript internally breaks it into:
// - Identifier: "console"
// - Dot: "."
// - Identifier: "log"
// - Parenthesis: "("
// - String: "Hi"
// - Parenthesis: ")"
// - Semicolon: ";"
```

---

## 📚 Chapter 2: The Parser (Understanding Meaning)

### What is it?

**In Python terms:** The parser is like Python checking if your indentation is correct and if `if` statements have colons.

**Real-world analogy:** A grammar checker that ensures your sentence makes sense.

### Example

**Tokens from previous step:**
```
say ( "Hello" ) ;
```

**What the parser does:**
```
✓ Checks: "say" is followed by "("
✓ Checks: Inside parentheses is a valid value
✓ Checks: Statement ends with ";"
✓ Creates: A "SAY instruction" node
```

### Why is this needed?

Just because you have valid words doesn't mean they form a valid sentence!

**Invalid examples:**
```jc
say "Hello";     // ✗ Missing parentheses
say("Hello"      // ✗ Missing closing )
say()Hello";     // ✗ Nonsense order
```

The parser catches these errors and tells you **exactly** what's wrong.

---

## 📚 Chapter 3: The AST (Abstract Syntax Tree)

### What is it?

**In Python terms:** When Python reads `if x > 5: print(x)`, it creates a mental model: "IF condition THEN action". That's an AST!

**Real-world analogy:** A family tree, but for your code.

### Example

**Your code:**
```jc
keep x = 10;
when (x > 5) {
    say(x);
}
```

**The AST (tree structure):**
```
Program
├── KEEP
│   ├── name: "x"
│   └── value: 10
└── WHEN
    ├── condition: (x > 5)
    └── body: SAY(x)
```

### Why is this needed?

Trees make it easy to:
- **Understand relationships**: "This `say` is INSIDE the `when` block"
- **Transform code**: Optimize, compile, analyze
- **Execute in order**: Walk the tree from top to bottom

**JavaScript equivalent:**
```javascript
// When you write:
if (x > 5) {
    console.log(x);
}

// JavaScript creates a similar tree internally:
// IfStatement
//   ├── test: BinaryExpression (x > 5)
//   └── consequent: CallExpression (console.log)
```

---

## 📚 Chapter 4: The Bytecode (Simplified Instructions)

### What is it?

**In Python terms:** Python compiles your code to `.pyc` files (bytecode). JECH does the same!

**Real-world analogy:** Like translating a recipe from English to a numbered list of steps.

### Example

**Your code:**
```jc
keep x = 10;
say(x);
```

**Bytecode (simplified instructions):**
```
[0] OP_KEEP    name="x"  value=10
[1] OP_SAY     operand="x"
[2] OP_END
```

### Why is this needed?

Bytecode is:
- **Faster to execute** than parsing text every time
- **Portable** (can be saved and run later)
- **Optimizable** (can be improved before running)

**Python comparison:**
```python
# Your Python code
x = 10
print(x)

# Gets compiled to bytecode (you can see it with dis.dis()):
# LOAD_CONST    10
# STORE_NAME    x
# LOAD_NAME     x
# PRINT_ITEM
```

---

## 📚 Chapter 5: The Virtual Machine (Actually Running Code)

### What is it?

**In Python terms:** The Python VM (CPython) reads bytecode and executes it. JECH has its own mini-VM!

**Real-world analogy:** A chef following the numbered recipe steps.

### Example

**Bytecode:**
```
[0] OP_KEEP    name="x"  value=10
[1] OP_SAY     operand="x"
```

**What the VM does:**
```
Step 0: OP_KEEP
  → Create variable "x"
  → Store value 10
  → Variables table: { x: 10 }

Step 1: OP_SAY
  → Look up "x" in variables table
  → Found: 10
  → Print to screen: "10"
```

### Why is this needed?

The VM is the **actual executor**. Everything before this was preparation!

---

## 🎯 Putting It All Together

### The Complete Journey

```jc
say("Hello!");
```

**Step-by-step:**

1. **Tokenizer** breaks it into pieces:
   ```
   [say] [(] ["Hello!"] [)] [;]
   ```

2. **Parser** understands the pattern:
   ```
   "This is a SAY command with a string argument"
   ```

3. **AST** creates a tree node:
   ```
   SAY_NODE { value: "Hello!" }
   ```

4. **Bytecode** generates instructions:
   ```
   OP_SAY operand="Hello!"
   ```

5. **VM** executes:
   ```
   Print "Hello!" to screen
   ```

**Output:** `Hello!`

---

## 💡 Key Concepts Explained Simply

### Compilation vs Interpretation

**Compiled (like C):**
```
Code → Compiler → Machine Code → Run
(Happens once)    (Fast!)
```

**Interpreted (like Python):**
```
Code → Interpreter → Run
(Happens every time) (Flexible!)
```

**JECH (hybrid, like Python):**
```
Code → Tokenizer → Parser → Bytecode → VM
       (Compile once)         (Run fast!)
```

### Why C?

**Q:** "Why is JECH written in C if I don't know C?"

**A:** C is like the "assembly language of high-level languages":
- Python (CPython) is written in C
- JavaScript (V8) is written in C++
- PHP is written in C

Learning how JECH works teaches you how **your favorite languages** work internally!

### Static vs Dynamic Typing

**Python (dynamic):**
```python
x = 10      # x is a number
x = "hi"    # now x is a string - no problem!
```

**JECH (currently simple):**
```jc
keep x = 10;
x = "hi";    // This works too! (for now)
```

JECH is designed to be **simple first**, then we can add complexity.

---

## 🚀 Next Steps

Now that you understand the concepts, dive into the detailed docs:

1. **[Tokenizer Deep Dive](tokenizer.md)** - See actual C code with explanations
2. **[Parser Deep Dive](parser.md)** - Learn pattern matching
3. **[VM Deep Dive](vm.md)** - Understand execution

### Try It Yourself!

```bash
# Install JECH
git clone <repo>
cd jech
make

# Run the REPL (like Python's interactive mode)
./build/jech

# Try some code!
>>> keep x = 10;
>>> say(x);
10
>>> keep arr = [1, 2, 3];
>>> say(arr[0]);
1
```

---

## 🤝 Common Questions

### "Do I need to learn C to understand JECH?"

**No!** The concepts are language-agnostic. We explain everything in terms you already know.

### "Is this how Python/JavaScript really work?"

**Yes!** The principles are identical. Python uses:
- Tokenizer (lexer)
- Parser (generates AST)
- Compiler (generates bytecode)
- VM (CPython executes bytecode)

### "Can I contribute without knowing C?"

**Absolutely!** You can:
- Write example programs
- Improve documentation
- Report bugs
- Suggest features
- Write tests

### "What if I want to learn C?"

Great! JECH is an **excellent** C learning project because:
- Small codebase (easy to read)
- Well-documented
- Practical application
- Modular structure

---

## 📖 Glossary for High-Level Developers

| Term | Python Equivalent | Simple Explanation |
|------|-------------------|-------------------|
| **Token** | Lexical unit | A labeled piece of code (keyword, number, string) |
| **AST** | `ast.parse()` result | Tree representation of your code |
| **Bytecode** | `.pyc` file content | Simplified instructions for the VM |
| **VM** | CPython interpreter | The thing that actually runs your code |
| **Lexer** | Tokenizer | Breaks code into pieces |
| **Parser** | Syntax checker | Validates code structure |
| **Compiler** | `compile()` | Converts code to bytecode |
| **Interpreter** | `python` command | Runs code directly |

---

## 🎓 Learning Path

**Level 1: Understand the concepts** (You are here!)
- Read this guide
- Try the REPL
- Run examples

**Level 2: See it in action**
- Read [Architecture Overview](architecture.md)
- Follow code examples
- Trace execution

**Level 3: Understand implementation**
- Read component docs (tokenizer, parser, VM)
- Look at actual C code
- Understand data structures

**Level 4: Contribute**
- Write tests
- Add features
- Improve docs
- Help others

---

**Remember:** Every expert was once a beginner. Python's creator didn't know everything when he started. Neither did JavaScript's or PHP's creators. You're learning the same fundamentals they used!

**Welcome to the world of language design!** 🚀
