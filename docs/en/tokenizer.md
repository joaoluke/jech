### 🔍 Overview

The **tokenizer** (or **lexer**) is responsible for transforming the source text into **tokens** — categorized blocks that represent keywords, symbols, numbers, strings, etc.

---

### 📄 General Structure of `tokenizer.c`

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "core/tokenizer.h"
```

Import of the standard C libraries and the JECH language header.

---

### 🔤 Keyword Table

```c
typedef struct {
	const char *keyword;
	JechTokenType type;
} KeywordMap;

KeywordMap keywords[] = {
	{"say", TOKEN_SAY},
	{"keep", TOKEN_KEEP},
	{"when", TOKEN_WHEN},
	{NULL, TOKEN_UNKNOWN}
};
```

Here we define the **mapping between strings and their token types**. This allows `say`, for example, to be interpreted as a token of type `TOKEN_SAY`.

---

### 🧠 Auxiliary functions

#### 🔍 `match_keyword`

```c
JechTokenType match_keyword(const char *word)
```

Checks if the word read is a recognized keyword. If so, returns the corresponding type. Otherwise, assumes it is an identifier (`TOKEN_IDENTIFIER`).

---

#### 🧱 `create_token`

```c
JechToken create_token(JechTokenType type, const char *value)
```

Creates a new token with type and value. It is used in practically all reading functions (strings, numbers, symbols...).

---

### 🔧 Reading the source code

#### Ignoring spaces and comments

```c
static void skip_whitespace_and_comments(const char **p)
```

Advances the pointer `p` ignoring:

* whitespace
* comments starting with `#` or `//`

---

#### 🧾 `read_word`

```c
static JechToken read_word(const char **p)
```

Reads a word that can be:

* a keyword (`say`, `keep`, etc.)
* a boolean (`true`, `false`)
* a generic identifier

---

#### 🔢 `read_number`

```c
static JechToken read_number(const char **p)
```

Reads integer or floating point numbers, such as `42` or `3.14`.

---

#### 📝 `read_string`

```c
static JechToken read_string(const char **p)
```

Reads quoted strings (`"something"`). If it doesn't find the final quote, it throws an error.

---

### 🎯 Main function

```c
JechTokenList _JechTokenizer_Lex(const char *source)
```

This is the **main public function of the lexer**. It:

1. Creates the list of tokens.
2. Reads the code character by character.
3. Calls the appropriate reading function:
* `read_word`, `read_number`, `read_string`, etc.
4. Adds a `TOKEN_EOF` to the end.

---
