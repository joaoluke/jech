# 🧱 Parser (Syntax Analysis)

## What is a Parser?

The **parser** is the second stage of the compilation pipeline. It takes the stream of tokens from the tokenizer and validates that they form valid **syntax patterns**.

Think of it like checking grammar: the tokenizer identified the words, now the parser checks if they form valid sentences.

### What the Parser Does

1. **Validates syntax** — ensures tokens appear in the correct order
2. **Creates AST nodes** — builds a tree structure representing the program
3. **Reports errors** — tells you exactly what's wrong and where

---

## 📂 File Structure

```c
#include "core/ast.h"
#include "core/parser/parser.h"
#include "errors/error.h"

#define MAX_AST_ROOTS 128
```

The parser depends on the AST module to create nodes and the error module for reporting issues.

---

## 🔍 Pattern Matching

The parser recognizes these patterns:

### Pattern 1: `say(...)` — Output Statement

```jc
say("Hello!");
say(42);
say(myVar);
```

**Token sequence:**
```text
TOKEN_SAY → TOKEN_LPAREN → VALUE → TOKEN_RPAREN → TOKEN_SEMICOLON
```

Where VALUE can be: `TOKEN_STRING`, `TOKEN_NUMBER`, `TOKEN_BOOL`, or `TOKEN_IDENTIFIER`

---

### Pattern 2: `keep` — Variable Declaration

```jc
keep name = "João";
keep age = 25;
keep active = true;
```

**Token sequence:**
```text
TOKEN_KEEP → TOKEN_IDENTIFIER → TOKEN_EQUALS → VALUE → TOKEN_SEMICOLON
```

---

### Pattern 3: Variable Reassignment

```jc
name = "Maria";
age = 30;
```

**Token sequence:**
```text
TOKEN_IDENTIFIER → TOKEN_EQUALS → VALUE → TOKEN_SEMICOLON
```

---

### Pattern 4: `when` — Conditional Statement

#### Simple boolean condition:
```jc
when (active) {
    say("Yes!");
}
```

**Token sequence:**
```text
TOKEN_WHEN → TOKEN_LPAREN → TOKEN_IDENTIFIER/TOKEN_BOOL → TOKEN_RPAREN → TOKEN_LBRACE → ... → TOKEN_RBRACE
```

#### Comparison condition:
```jc
when (age > 18) {
    say("Adult");
}
```

**Token sequence:**
```text
TOKEN_WHEN → TOKEN_LPAREN → TOKEN_IDENTIFIER → OPERATOR → VALUE → TOKEN_RPAREN → TOKEN_LBRACE → ... → TOKEN_RBRACE
```

Where OPERATOR can be: `TOKEN_GT` (`>`), `TOKEN_LT` (`<`), or `TOKEN_EQEQ` (`==`)

---

### Pattern 5: `else` — Alternative Branch

```jc
when (age > 18) {
    say("Adult");
}
else {
    say("Minor");
}
```

The `else` block is optional and follows immediately after the `when` block's closing brace.

---

## 🔧 Core Functions

### `parse_say`

```c
JechASTNode *parse_say(const JechToken *t, int remaining)
```

Parses a `say(...)` statement. Validates the token sequence and creates an AST node of type `JECH_AST_SAY`.

---

### `parse_keep`

```c
JechASTNode *parse_keep(const JechToken *t, int remaining)
```

Parses a `keep x = value;` statement. Creates an AST node with:
- `name` = variable identifier
- `value` = assigned value

---

### `parse_when`

```c
JechASTNode *parse_when(const JechToken *t, int remaining)
```

Parses conditional statements. This is the most complex parser function because it handles:

1. **Boolean conditions**: `when (flag) { ... }`
2. **Comparison conditions**: `when (x > 10) { ... }`
3. **Optional else blocks**: `... else { ... }`

The resulting AST node has:
- `left` → condition node
- `right` → then-branch (what to execute if true)
- `else_branch` → else-branch (what to execute if false)

---

### `parse_assign`

```c
JechASTNode *parse_assign(const JechToken *t, int remaining)
```

Parses variable reassignment: `x = newValue;`

---

## 🎯 Main Entry Point

```c
JechASTNode **_JechParser_ParseAll(const JechTokenList *tokens, int *out_count)
```

This function orchestrates the entire parsing process:

1. **Allocate** array for AST root nodes
2. **Iterate** through tokens
3. **Match** each token against known patterns
4. **Dispatch** to the appropriate parse function
5. **Collect** resulting AST nodes
6. **Return** array of roots and count

### Example Walkthrough

Input tokens (from tokenizer):
```text
TOKEN_KEEP "age"
TOKEN_IDENTIFIER "age"
TOKEN_EQUALS "="
TOKEN_NUMBER "25"
TOKEN_SEMICOLON ";"
TOKEN_WHEN "when"
...
```

Output AST:
```text
roots[0] = JECH_AST_KEEP (name="age", value="25")
roots[1] = JECH_AST_WHEN
           ├── left: JECH_AST_BIN_OP (>)
           │         ├── left: JECH_AST_IDENTIFIER ("age")
           │         └── right: JECH_AST_NUMBER_LITERAL ("18")
           ├── right: JECH_AST_SAY ("adult")
           └── else_branch: JECH_AST_SAY ("minor")
```

---

## ⚠️ Error Handling

The parser provides detailed error messages:

```c
report_syntax_error("Expected '(' after 'when'", token.line, token.column);
report_syntax_error("Missing semicolon after 'say'", token.line, token.column);
report_syntax_error("Invalid condition in 'when' statement", token.line, token.column);
```

Each error includes:
- **What went wrong** — clear description
- **Where it happened** — line and column number

---

## 💡 Key Concepts for Learners

1. **Recursive descent** — each grammar rule becomes a function
2. **Lookahead** — peek at upcoming tokens to decide which rule to apply
3. **Token consumption** — advance through tokens as you match them
4. **Error recovery** — report errors clearly and stop gracefully

---
