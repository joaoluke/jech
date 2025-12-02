# 🌳 AST (Árvore Sintática Abstrata)

## O que é uma AST?

A **Árvore Sintática Abstrata** é uma representação hierárquica da estrutura do seu programa. Diferente da lista plana de tokens, a AST captura os **relacionamentos** entre elementos.

Pense nisso como uma árvore genealógica: ela mostra não apenas quem existe, mas como estão conectados.

### Por que "Abstrata"?

A AST remove detalhes desnecessários (como parênteses e ponto e vírgula) e mantém apenas o **significado semântico** do código.

---

## 📊 Tipos de Nó no JECH

```c
typedef enum {
    JECH_AST_SAY,            // declaração say(...)
    JECH_AST_KEEP,           // keep x = valor
    JECH_AST_WHEN,           // when (...) { }
    JECH_AST_ASSIGN,         // x = valor
    JECH_AST_BIN_OP,         // operação binária (>, <, ==)
    JECH_AST_IDENTIFIER,     // referência a variável
    JECH_AST_NUMBER_LITERAL, // valor numérico
    JECH_AST_STRING_LITERAL, // valor string
    JECH_AST_BOOL_LITERAL,   // true/false
    JECH_AST_UNKNOWN
} JechASTType;
```

---

## 🏗️ Estrutura do Nó

```c
typedef struct JechASTNode {
    JechASTType type;           // Que tipo de nó
    char value[MAX_STRING];     // O valor (ex: "42", "olá")
    char name[MAX_STRING];      // Nome da variável (para keep/assign)
    JechTokenType token_type;   // Tipo do token original
    
    struct JechASTNode *left;        // Filho esquerdo
    struct JechASTNode *right;       // Filho direito
    struct JechASTNode *else_branch; // Para when/else
    
    JechTokenType op;           // Operador para BIN_OP
} JechASTNode;
```

### Exemplo Visual

Para este código:
```jc
when (idade > 18) {
    say("adulto");
}
else {
    say("menor");
}
```

A AST fica assim:
```text
JECH_AST_WHEN
├── left: JECH_AST_BIN_OP (op: >)
│         ├── left: JECH_AST_IDENTIFIER ("idade")
│         └── right: JECH_AST_NUMBER_LITERAL ("18")
├── right: JECH_AST_SAY ("adulto")
└── else_branch: JECH_AST_SAY ("menor")
```

---

## 🔧 Funções Principais

### `_JechAST_CreateNode`

```c
JechASTNode *_JechAST_CreateNode(
    JechASTType type, 
    const char *value, 
    const char *name, 
    JechTokenType token_type
)
```

**Função fábrica** que cria um novo nó da AST:

1. **Aloca memória** usando `malloc`
2. **Define o tipo** (SAY, KEEP, WHEN, etc.)
3. **Copia strings com segurança** usando `strncpy`
4. **Inicializa filhos** como `NULL`

```c
// Exemplo: criando um nó SAY
JechASTNode *say_node = _JechAST_CreateNode(
    JECH_AST_SAY,      // tipo
    "Olá!",            // valor
    NULL,              // nome (não necessário para say)
    TOKEN_STRING       // token_type
);
```

**Medidas de segurança:**
- Usa `strncpy` para prevenir buffer overflows
- Termina todas as strings com null
- Verifica falha do `malloc`

---

### `_JechAST_Free`

```c
void _JechAST_Free(JechASTNode *node)
```

**Libera recursivamente** toda a árvore para prevenir vazamentos de memória:

```c
void _JechAST_Free(JechASTNode *node) {
    if (node == NULL) return;
    
    _JechAST_Free(node->left);        // Libera subárvore esquerda
    _JechAST_Free(node->right);       // Libera subárvore direita
    _JechAST_Free(node->else_branch); // Libera bloco else
    free(node);                        // Libera este nó
}
```

Isso usa **travessia pós-ordem** (filhos primeiro, depois pai) para desalocar memória com segurança.

---

### `_JechAST_Print`

```c
void _JechAST_Print(const JechASTNode *node, int depth)
```

**Função de debug** que imprime a árvore com indentação:

```text
• JECH_AST_KEEP (name = "idade", value = "25")
  • JECH_AST_WHEN
    • JECH_AST_BIN_OP (>)
      • JECH_AST_IDENTIFIER ("idade")
      • JECH_AST_NUMBER_LITERAL ("18")
    • JECH_AST_SAY ("adulto")
```

Ótimo para debugging e entender como seu código está sendo parseado!

---

## 💡 Conceitos-Chave para Aprendizes

1. **Árvores são recursivas** — cada nó pode ter filhos que também são nós
2. **Gerenciamento de memória é crucial** — sempre libere o que você alocou
3. **A AST é a "verdade"** — é o que o compilador realmente vê
4. **Nós diferentes, mesma estrutura** — polimorfismo através do campo `type`

---

## 🔬 Como a AST Conecta com Outras Etapas

```text
Tokens → Parser → AST → Bytecode → VM
                   ↑
              Você está aqui
```

A AST é a **ponte** entre parsing e execução. O parser a cria, e o compilador de bytecode a lê para gerar instruções.

---
