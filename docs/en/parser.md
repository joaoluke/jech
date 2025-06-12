## 🔧 Role of `parsec` in the Pipeline

The parser transforms a linear list of tokens (coming from the tokenizer) into a tree structure: the AST (Abstract Syntax Tree). This tree is the ideal format for later parsing and compilation.

---

## 📂 Structure of `parser.c`

### 1. **Inclusions and definition of the root limit**

```c
#define MAX_AST_ROOTS 128
```

Defines the maximum number of root nodes that can be generated (e.g. a sequence of `say(...); keep ...;` commands etc.).

---

### 2. **Function `create_say_node`**

```c
static JechASTNode *create_say_node(const JechToken *value_token)
```

Creates an AST node for commands like:

```jc
say("Olá!");
```

Internally it calls `_JechAST_CreateNode` with type `JECH_AST_SAY` and the value as content.

---

### 3. **Function `create_keep_node`**

```c
static JechASTNode *create_keep_node(const JechToken *name_token, const JechToken *value_token)
```

Handles instructions like:

```jc
keep x = 42;
```

Passes the variable name and value as separate fields in the AST.

---

### 4. **Main function: `_JechParser_ParseAll`**

```c
JechASTNode **_JechParser_ParseAll(const JechTokenList *tokens, int *out_count)
```

#### 📌 Main steps:

1. **Declare a fixed vector of AST roots:**

   ```c
   static JechASTNode *roots[MAX_AST_ROOTS];
   ```

2. **Iterate through tokens with `i`** and try to find valid patterns:

#### ✅ Pattern 1: `say(...)`

Check exact sequence:

```jc
say ( STRING/NUMBER/BOOL/IDENTIFIER ) ;
```

#### ✅ Pattern 2: `keep x = 123;`

Check:

```jc
keep IDENTIFIER = VALUE ;
```

#### ⚠️ Invalid case:

If no pattern matches, print error:

```c
Parser error: unexpected token near '...'
```

---

## 🎯 Result

Returns an array of pointers to AST nodes and fills `*out_count` with the total.
