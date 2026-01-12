## 🧠 Papel do `ast.c`

Enquanto `parser.c` define a **lógica de como gerar a AST a partir dos tokens**, `ast.c` lida com **como esta árvore é representada, criada, destruída e impressa**.

É essencial manter a AST estruturada e manipulável como uma árvore real (com ponteiros para `left` e `right`).

---

## 🔍 Análise do `ast.c`

### 1. **Função `_JechAST_CreateNode`**

```c
JechASTNode *_JechAST_CreateNode(JechASTType type, const char *value, const char *name, JechTokenType token_type)
```

#### ✔️ Função principal para criar nós da AST.

* Usa `malloc` para alocar dinamicamente um novo nó.
* Preenche:
    * `type` → tipo do nó (ex: `JECH_AST_SAY`, `JECH_AST_KEEP`).
    * `value` e `name` → strings opcionais, como `"42"` ou `"x"`.
    * `token_type` → para manter a origem dos dados (útil no bytecode).
* Inicializa `left` e `right` como `NULL`, tornando o nó uma **folha** inicialmente.

🔐 **Segurança:**

* Usa `strncpy` para evitar overflows.
* Garante `\0` no final das strings.
* Verifica falha do `malloc`.

---

### 2. **Função `_JechAST_Free`**

```c
void _JechAST_Free(JechASTNode *node)
```

#### 🧹 Libera recursivamente a memória de toda a árvore.

* Caminhamento em profundidade (`DFS`) à esquerda e à direita.
* Libera a memória de cada nó.

🔁 **Importante para evitar vazamentos de memória**, especialmente em uma linguagem como C sem GC.

---

### 3. **Função `_JechAST_Print`**

```c
void _JechAST_Print(const JechASTNode *node, int depth)
```

#### 🖨️ Imprime a árvore com indentação de profundidade.

* Para cada nível de profundidade, imprime dois espaços.
* Mostra o tipo do nó, e se existir:

* O nome (`name`)
* O valor (`value`)
* Um `=` entre eles se ambos estiverem presentes

**Exemplo de saída:**

```
• 1 (x = "Olá")
• 0 ("Mundo")
```

✅ Ótimo para depuração visual no terminal.

---
