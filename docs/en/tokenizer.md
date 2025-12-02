# 🔍 Tokenizer (Lexical Analysis)

## What is a Tokenizer?

The **tokenizer** (also called **lexer**) is the first stage of any compiler or interpreter. Its job is to read raw source code and break it into meaningful pieces called **tokens**.

Think of it like reading a sentence: before you can understand grammar, you need to identify individual words and punctuation marks.

### Example

```jc
keep age = 25;
```

The tokenizer converts this into:

```text
TOKEN_KEEP       → "keep"
TOKEN_IDENTIFIER → "age"
TOKEN_EQUALS     → "="
TOKEN_NUMBER     → "25"
TOKEN_SEMICOLON  → ";"
```

Each token has a **type** (what kind of element it is) and a **value** (the actual text).

---

## 📄 Implementation in JECH

### File Structure

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "core/tokenizer.h"
```

Standard C libraries for string manipulation, character classification, and memory allocation.

---

## 🔤 Token Types

JECH recognizes these token types:

### Keywords
| Token | Keyword | Description |
|-------|---------|-------------|
| `TOKEN_SAY` | `say` | Output command |
| `TOKEN_KEEP` | `keep` | Variable declaration |
| `TOKEN_WHEN` | `when` | Conditional statement |
| `TOKEN_ELSE` | `else` | Alternative branch |

### Literals
| Token | Example | Description |
|-------|---------|-------------|
| `TOKEN_STRING` | `"hello"` | Text in quotes |
| `TOKEN_NUMBER` | `42`, `3.14` | Integer or float |
| `TOKEN_BOOL` | `true`, `false` | Boolean values |
| `TOKEN_IDENTIFIER` | `myVar` | Variable names |

### Operators & Symbols
| Token | Symbol | Description |
|-------|--------|-------------|
| `TOKEN_EQUALS` | `=` | Assignment |
| `TOKEN_EQEQ` | `==` | Equality comparison |
| `TOKEN_GT` | `>` | Greater than |
| `TOKEN_LT` | `<` | Less than |
| `TOKEN_LPAREN` | `(` | Left parenthesis |
| `TOKEN_RPAREN` | `)` | Right parenthesis |
| `TOKEN_LBRACE` | `{` | Left brace |
| `TOKEN_RBRACE` | `}` | Right brace |
| `TOKEN_SEMICOLON` | `;` | Statement terminator |

---

## 🔧 Keyword Mapping

```c
typedef struct {
    const char *keyword;
    JechTokenType type;
} KeywordMap;

KeywordMap keywords[] = {
    {"say", TOKEN_SAY},
    {"keep", TOKEN_KEEP},
    {"when", TOKEN_WHEN},
    {"else", TOKEN_ELSE},
    {NULL, TOKEN_UNKNOWN}
};
```

This table maps keyword strings to their token types. When the tokenizer reads a word, it checks this table to determine if it's a keyword or a regular identifier.

---

## 🧠 Core Functions

### `match_keyword`

```c
JechTokenType match_keyword(const char *word)
```

Checks if a word is a recognized keyword. Returns the corresponding token type, or `TOKEN_IDENTIFIER` if it's not a keyword.

**How it works:**
```c
// Iterates through the keywords table
for (int i = 0; keywords[i].keyword != NULL; i++) {
    if (strcmp(word, keywords[i].keyword) == 0) {
        return keywords[i].type;  // Found a keyword!
    }
}
return TOKEN_IDENTIFIER;  // Not a keyword, must be a variable name
```

---

### `create_token`

```c
JechToken create_token(JechTokenType type, const char *value)
```

Factory function that creates a new token with the given type and value. Also tracks line and column numbers for error reporting.

---

## 🔧 Reading Functions

### Skipping Whitespace and Comments

```c
static void skip_whitespace_and_comments(const char **p)
```

Advances the source pointer past:
- Spaces, tabs, newlines
- Single-line comments (`//` or `#`)

This ensures the tokenizer only processes meaningful characters.

---

### `read_word`

```c
static JechToken read_word(const char **p)
```

Reads alphabetic sequences that could be:
- **Keywords**: `say`, `keep`, `when`, `else`
- **Booleans**: `true`, `false`
- **Identifiers**: variable names like `myVar`, `age`

---

### `read_number`

```c
static JechToken read_number(const char **p)
```

Reads numeric literals:
- **Integers**: `42`, `100`
- **Floats**: `3.14`, `0.5`

---

### `read_string`

```c
static JechToken read_string(const char **p)
```

Reads string literals enclosed in double quotes: `"Hello, World!"`

If the closing quote is missing, reports an "Unterminated string" error.

---

## 🎯 Main Entry Point

```c
JechTokenList _JechTokenizer_Lex(const char *source)
```

This is the **public API** of the tokenizer. It orchestrates the entire lexical analysis:

1. **Initialize** an empty token list
2. **Loop** through the source code character by character
3. **Dispatch** to the appropriate reader based on the current character:
   - Letter → `read_word()`
   - Digit → `read_number()`
   - Quote → `read_string()`
   - Symbol → create symbol token directly
4. **Append** `TOKEN_EOF` to mark the end
5. **Return** the complete token list

### Example Walkthrough

Input:
```jc
when (age > 18) { say("adult"); }
```

Output tokens:
```text
[0] TOKEN_WHEN       "when"
[1] TOKEN_LPAREN     "("
[2] TOKEN_IDENTIFIER "age"
[3] TOKEN_GT         ">"
[4] TOKEN_NUMBER     "18"
[5] TOKEN_RPAREN     ")"
[6] TOKEN_LBRACE     "{"
[7] TOKEN_SAY        "say"
[8] TOKEN_LPAREN     "("
[9] TOKEN_STRING     "adult"
[10] TOKEN_RPAREN    ")"
[11] TOKEN_SEMICOLON ";"
[12] TOKEN_RBRACE    "}"
[13] TOKEN_EOF
```

---

## 💡 Key Concepts for Learners

1. **Tokens are the atoms of your language** — everything starts here
2. **Order matters** — check for `==` before `=` to avoid mismatches
3. **Track position** — line/column info is crucial for helpful error messages
4. **Fail early** — report errors as soon as you detect them

---
