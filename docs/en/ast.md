# 🌳 AST (Abstract Syntax Tree)

## What is an AST?

The **Abstract Syntax Tree** is a hierarchical representation of your program's structure. Unlike the flat list of tokens, the AST captures the **relationships** between elements.

Think of it like a family tree: it shows not just who exists, but how they're connected.

### Why "Abstract"?

The AST removes unnecessary details (like parentheses and semicolons) and keeps only the **semantic meaning** of the code.

---

## 📊 Node Types in JECH

```c
typedef enum {
    JECH_AST_SAY,            // say(...) statement
    JECH_AST_KEEP,           // keep x = value
    JECH_AST_WHEN,           // when (...) { }
    JECH_AST_ASSIGN,         // x = value
    JECH_AST_BIN_OP,         // binary operation (>, <, ==)
    JECH_AST_IDENTIFIER,     // variable reference
    JECH_AST_NUMBER_LITERAL, // numeric value
    JECH_AST_STRING_LITERAL, // string value
    JECH_AST_BOOL_LITERAL,   // true/false
    JECH_AST_UNKNOWN
} JechASTType;
```

---

## 🏗️ Node Structure

```c
typedef struct JechASTNode {
    JechASTType type;           // What kind of node
    char value[MAX_STRING];     // The value (e.g., "42", "hello")
    char name[MAX_STRING];      // Variable name (for keep/assign)
    JechTokenType token_type;   // Original token type
    
    struct JechASTNode *left;        // Left child
    struct JechASTNode *right;       // Right child
    struct JechASTNode *else_branch; // For when/else
    
    JechTokenType op;           // Operator for BIN_OP
} JechASTNode;
```

### Visual Example

For this code:
```jc
when (age > 18) {
    say("adult");
}
else {
    say("minor");
}
```

The AST looks like:
```text
JECH_AST_WHEN
├── left: JECH_AST_BIN_OP (op: >)
│         ├── left: JECH_AST_IDENTIFIER ("age")
│         └── right: JECH_AST_NUMBER_LITERAL ("18")
├── right: JECH_AST_SAY ("adult")
└── else_branch: JECH_AST_SAY ("minor")
```

---

## 🔧 Core Functions

### `_JechAST_CreateNode`

```c
JechASTNode *_JechAST_CreateNode(
    JechASTType type, 
    const char *value, 
    const char *name, 
    JechTokenType token_type
)
```

**Factory function** that creates a new AST node:

1. **Allocates memory** using `malloc`
2. **Sets the type** (SAY, KEEP, WHEN, etc.)
3. **Copies strings safely** using `strncpy`
4. **Initializes children** to `NULL`

```c
// Example: creating a SAY node
JechASTNode *say_node = _JechAST_CreateNode(
    JECH_AST_SAY,      // type
    "Hello!",          // value
    NULL,              // name (not needed for say)
    TOKEN_STRING       // token_type
);
```

**Security measures:**
- Uses `strncpy` to prevent buffer overflows
- Null-terminates all strings
- Checks for `malloc` failure

---

### `_JechAST_Free`

```c
void _JechAST_Free(JechASTNode *node)
```

**Recursively frees** the entire tree to prevent memory leaks:

```c
void _JechAST_Free(JechASTNode *node) {
    if (node == NULL) return;
    
    _JechAST_Free(node->left);        // Free left subtree
    _JechAST_Free(node->right);       // Free right subtree
    _JechAST_Free(node->else_branch); // Free else branch
    free(node);                        // Free this node
}
```

This uses **post-order traversal** (children first, then parent) to safely deallocate memory.

---

### `_JechAST_Print`

```c
void _JechAST_Print(const JechASTNode *node, int depth)
```

**Debug function** that prints the tree with indentation:

```text
• JECH_AST_KEEP (name = "age", value = "25")
  • JECH_AST_WHEN
    • JECH_AST_BIN_OP (>)
      • JECH_AST_IDENTIFIER ("age")
      • JECH_AST_NUMBER_LITERAL ("18")
    • JECH_AST_SAY ("adult")
```

Great for debugging and understanding how your code is being parsed!

---

## 💡 Key Concepts for Learners

1. **Trees are recursive** — each node can have children that are also nodes
2. **Memory management is crucial** — always free what you allocate
3. **The AST is the "truth"** — it's what the compiler actually sees
4. **Different nodes, same structure** — polymorphism through the `type` field

---

## 🔬 How AST Connects to Other Stages

```text
Tokens → Parser → AST → Bytecode → VM
                   ↑
              You are here
```

The AST is the **bridge** between parsing and execution. The parser creates it, and the bytecode compiler reads it to generate instructions.

---

