## 🗺 JECH Language – Roadmap to v1.0.0

> This roadmap organizes the main steps to achieve a functional language with a complete and usable structure, based on what has already been implemented and what remains to be built.

---

### ✅ Step 1: Language Fundamentals

* [x] `say(...)` supports string, bool, int, float
* [x] Lexer (tokenization)
* [x] Parser (syntactic analysis)
* [x] AST (tree structure)
* [x] Bytecode
* [x] VM
* [x] System of lexical and syntactic errors
* [x] Modular folder architecture (src/, include/, commands/, core/, etc)
* [x] Automated testing system (`test-runner`)
* [x] Initial documentation (`README`, `architecture.md`, etc)

---

### 🚧 Step 2: Variables with `keep`

* [ ] Implement `keep` command in parser and AST
* [ ] Store variables in a map/symbol table
* [ ] Allow `say(variable_name);`
* [ ] Support assignment: `name = new_value;`

---

### 🔁 Step 3: Flow Control

* [ ] Conditional `when(expr) { ... }`

  * Comparison support: `==`, `!=`, `<`, `>` etc.
  * Boolean evaluation
* [ ] Repetition `repeat(n) { ... }`

  * Execute block N times

---

### 🧮 Step 4: Types, Arrays, and Operations

* [ ] Arrays: `keep list = [1, 2, 3];`
* [ ] Indexing support: `list[0]`
* [ ] Mathematical operators: `+`, `-`, `*`, `/`
* [ ] Logical operators: `and`, `or`, `not`

---

### 🧠 Step 5: Functions

* [ ] Declaration: `fn nome() { ... }`
* [ ] Execution: `nome();`
* [ ] Parameter support: `fn hello(name) { say(name); }`
* [ ] Variable scope

---

### 🧪 Step 6: Testing and Documentation

* [ ] Create tests for each command, type, and control structure
* [ ] Update `docs/` with technical explanations for:

  * `keep`
  * `when`
  * `repeat`
  * functions
  * arrays
* [ ] Writing real JECH program examples with multiple features together

---

### 🚀 Release v1.0.0

* [ ] Tag no GitHub
* [ ] Release notes no `CHANGELOG.md`
* [ ] Explanatory post in README

---

