# JECH Language - Lexer Documentation

The **lexer** (also called the lexical analyzer or tokenizer) is the first step in the JECH language interpreter. It reads raw source code and breaks it into a sequence of **tokens**, which represent meaningful components of the language.

---

## 📌 What is a Token?

A token is a categorized piece of text such as a keyword, symbol, or literal value. For example, given this JECH code:

```jc
say("Hello, JECH!");
say(42);
say(3.14);
say(true);
```

The lexer will generate the following tokens:

* `say` → **keyword**
* `(` → **left parenthesis**
* `"Hello, JECH!"` → **string literal**
* `42` → **integer number**
* `3.14` → **real number (float)**
* `true` / `false` → **boolean literal**
* `)` → **right parenthesis**
* `;` → **semicolon**

---

## 🧾 Token Types

The lexer recognizes the following token types:

```c
typedef enum {
    TOKEN_SAY,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_BOOLEAN,
    TOKEN_EOF
} TokenType;
```

Each token has a **type** and a **value**. For example:

```c
typedef struct {
    TokenType type;
    char value[256];
} Token;
```

---

## 🛠 Lexer Operation

The lexer scans the source input character by character and applies rules to classify tokens. Here’s how it identifies them:

* `strncmp(p, "say", 3)` → recognizes the `say` keyword
* `*p == '('`, `')'`, `';'` → detects punctuation symbols
* `*p == '"'` → captures string literals until the next `"`
* `isdigit(*p)` or `*p == '.'` → parses integer or float numbers
* `strncmp(p, "true", 4)` or `"false"` → parses boolean literals
* Whitespace is ignored
* Invalid characters may trigger errors (error handling is planned)

---

## 📋 Example Output

Given:

```jc
say("Hello!");
say(99);
say(3.14);
say(false);
```

The lexer will output:

```
Token: Type=TOKEN_SAY        Value="say"
Token: Type=TOKEN_LPAREN     Value="("
Token: Type=TOKEN_STRING     Value="Hello!"
Token: Type=TOKEN_RPAREN     Value=")"
Token: Type=TOKEN_SEMICOLON  Value=";"

Token: Type=TOKEN_SAY        Value="say"
Token: Type=TOKEN_LPAREN     Value="("
Token: Type=TOKEN_NUMBER     Value="99"
Token: Type=TOKEN_RPAREN     Value=")"
Token: Type=TOKEN_SEMICOLON  Value=";"

Token: Type=TOKEN_SAY        Value="say"
Token: Type=TOKEN_LPAREN     Value="("
Token: Type=TOKEN_NUMBER     Value="3.14"
Token: Type=TOKEN_RPAREN     Value=")"
Token: Type=TOKEN_SEMICOLON  Value=";"

Token: Type=TOKEN_SAY        Value="say"
Token: Type=TOKEN_LPAREN     Value="("
Token: Type=TOKEN_BOOLEAN    Value="false"
Token: Type=TOKEN_RPAREN     Value=")"
Token: Type=TOKEN_SEMICOLON  Value=";"

Token: Type=TOKEN_EOF        Value=""
```

---

## ✅ Output Data Structure

```c
typedef struct {
    Token tokens[128];
    int count;
} TokenList;
```

This list of tokens is passed to the **parser**, which builds the Abstract Syntax Tree (AST) from the sequence.

---

**Next step:** [Parser and AST](./parser.md)
