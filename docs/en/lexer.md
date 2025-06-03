# Lexer - JECH Language

The **lexer** (also called lexical analyzer or tokenizer) is the first stage in the JECH language interpreter pipeline. Its main responsibility is to transform the raw text from a `.jc` source file into a sequence of **tokens**.

## 📌 What is a Token?

A token is a categorized block of text. For example, in the instruction:

```jc
say("Olá, JECH!");
```

The lexer produces these tokens:

* `say` → a **keyword**
* `(` → an **opening parenthesis**
* `"Olá, JECH!"` → a **string literal**
* `)` → a **closing parenthesis**
* `;` → a **semicolon (end of statement)**

## 🛠 How it Works in JECH

The lexer reads the input character by character and tries to recognize valid tokens.

### Token Types Defined:

```c
typedef enum {
    TOKEN_SAY,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_STRING,
    TOKEN_EOF
} TokenType;
```

### Token Representation:

```c
typedef struct {
    TokenType type;
    char value[256];
} Token;
```

Each token has a type and a value (for example, a string literal).

### Tokenization Example:

When given the input line:

```jc
say("Hello!");
```

The lexer produces:

```
Token: Type=TOKEN_SAY        Value="say"
Token: Type=TOKEN_LPAREN     Value="("
Token: Type=TOKEN_STRING     Value="Hello!"
Token: Type=TOKEN_RPAREN     Value=")"
Token: Type=TOKEN_SEMICOLON  Value=";"
Token: Type=TOKEN_EOF        Value=""
```

## ⚙️ Lexer Logic (Summary)

* `strncmp(p, "say", 3)` checks for the command `say`
* `*p == '('`, `')'`, or `';'` identifies punctuation tokens
* `*p == '"'` captures everything between `"..."` as a string literal
* Any unrecognized or malformed input results in an error or is skipped (to be improved)

## ✅ Output

The lexer outputs a `TokenList`, which will then be consumed by the **parser**.

```c
typedef struct {
    Token tokens[128];
    int count;
} TokenList;
```

---

Next step: [Parser and AST](./parser.md)
