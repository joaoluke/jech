## 🧠 Role of `ast.c`

While `parser.c` defines the **logic of how to generate the AST from tokens**, `ast.c` handles **how this tree is represented, created, destroyed and printed**.

It is essential to keep the AST structured and manipulable like a real tree (with pointers to `left` and `right`).

---

## 🔍 Analysis of `ast.c`

### 1. **Function `_JechAST_CreateNode`**

```c
JechASTNode *_JechAST_CreateNode(JechASTType type, const char *value, const char *name, JechTokenType token_type)
```

#### ✔️ Main function to create AST nodes.

* Uses `malloc` to dynamically allocate a new node.
* Fills in:
    * `type` → node type (e.g. `JECH_AST_SAY`, `JECH_AST_KEEP`).
    * `value` and `name` → optional strings, such as `"42"` or `"x"`.
    * `token_type` → to keep the origin of the data (useful in bytecode).
* Initializes `left` and `right` to `NULL`, making the node a **leaf** initially.

🔐 **Security:**

* Uses `strncpy` to avoid overflows.
* Ensures `\0` at the end of strings.
* Checks for `malloc` failure.

---

### 2. **`_JechAST_Free` function**

```c
void _JechAST_Free(JechASTNode *node)
```

#### 🧹 Recursively frees memory from the entire tree.

* Depth-first walk (`DFS`) left and right.
* Frees memory from each node.

🔁 **Important to avoid memory leaks**, especially in a language like C without GC.

---

### 3. **`_JechAST_Print` function**

```c
void _JechAST_Print(const JechASTNode *node, int depth)
```

#### 🖨️ Prints the tree with depth indentation.

* For each level of depth, prints two spaces.
* Shows the type of the node, and if it exists:

* The name (`name`)
* The value (`value`)
* An `=` between them if both are present

**Example output:**

```
• 1 (x = "Hello")
• 0 ("World")
```

✅ Great for visual debugging in the terminal.

---

