# 🧱 Parser (Análise Sintática)

## O que é um Parser?

O **parser** é o segundo estágio da pipeline de compilação. Ele pega o fluxo de tokens do tokenizer e valida que eles formam **padrões de sintaxe** válidos.

Pense nisso como verificar gramática: o tokenizer identificou as palavras, agora o parser verifica se elas formam sentenças válidas.

### O que o Parser Faz

1. **Valida sintaxe** — garante que os tokens aparecem na ordem correta
2. **Cria nós AST** — constrói uma estrutura em árvore representando o programa
3. **Reporta erros** — te diz exatamente o que está errado e onde

---

## 📂 Estrutura do Arquivo

```c
#include "core/ast.h"
#include "core/parser/parser.h"
#include "errors/error.h"

#define MAX_AST_ROOTS 128
```

O parser depende do módulo AST para criar nós e do módulo de erros para reportar problemas.

---

## 🔍 Correspondência de Padrões

O parser reconhece estes padrões:

### Padrão 1: `say(...)` — Instrução de Saída

```jc
say("Olá!");
say(42);
say(minhaVar);
```

**Sequência de tokens:**
```text
TOKEN_SAY → TOKEN_LPAREN → VALOR → TOKEN_RPAREN → TOKEN_SEMICOLON
```

Onde VALOR pode ser: `TOKEN_STRING`, `TOKEN_NUMBER`, `TOKEN_BOOL`, ou `TOKEN_IDENTIFIER`

---

### Padrão 2: `keep` — Declaração de Variável

```jc
keep nome = "João";
keep idade = 25;
keep ativo = true;
```

**Sequência de tokens:**
```text
TOKEN_KEEP → TOKEN_IDENTIFIER → TOKEN_EQUALS → VALOR → TOKEN_SEMICOLON
```

---

### Padrão 3: Reatribuição de Variável

```jc
nome = "Maria";
idade = 30;
```

**Sequência de tokens:**
```text
TOKEN_IDENTIFIER → TOKEN_EQUALS → VALOR → TOKEN_SEMICOLON
```

---

### Padrão 4: `when` — Instrução Condicional

#### Condição booleana simples:
```jc
when (ativo) {
    say("Sim!");
}
```

**Sequência de tokens:**
```text
TOKEN_WHEN → TOKEN_LPAREN → TOKEN_IDENTIFIER/TOKEN_BOOL → TOKEN_RPAREN → TOKEN_LBRACE → ... → TOKEN_RBRACE
```

#### Condição de comparação:
```jc
when (idade > 18) {
    say("Adulto");
}
```

**Sequência de tokens:**
```text
TOKEN_WHEN → TOKEN_LPAREN → TOKEN_IDENTIFIER → OPERADOR → VALOR → TOKEN_RPAREN → TOKEN_LBRACE → ... → TOKEN_RBRACE
```

Onde OPERADOR pode ser: `TOKEN_GT` (`>`), `TOKEN_LT` (`<`), ou `TOKEN_EQEQ` (`==`)

---

### Padrão 5: `else` — Ramo Alternativo

```jc
when (idade > 18) {
    say("Adulto");
}
else {
    say("Menor");
}
```

O bloco `else` é opcional e segue imediatamente após a chave de fechamento do bloco `when`.

---

## 🔧 Funções Principais

### `parse_say`

```c
JechASTNode *parse_say(const JechToken *t, int remaining)
```

Analisa uma instrução `say(...)`. Valida a sequência de tokens e cria um nó AST do tipo `JECH_AST_SAY`.

---

### `parse_keep`

```c
JechASTNode *parse_keep(const JechToken *t, int remaining)
```

Analisa uma instrução `keep x = valor;`. Cria um nó AST com:
- `name` = identificador da variável
- `value` = valor atribuído

---

### `parse_when`

```c
JechASTNode *parse_when(const JechToken *t, int remaining)
```

Analisa instruções condicionais. Esta é a função de parser mais complexa porque lida com:

1. **Condições booleanas**: `when (flag) { ... }`
2. **Condições de comparação**: `when (x > 10) { ... }`
3. **Blocos else opcionais**: `... else { ... }`

O nó AST resultante tem:
- `left` → nó de condição
- `right` → ramo then (o que executar se verdadeiro)
- `else_branch` → ramo else (o que executar se falso)

---

### `parse_assign`

```c
JechASTNode *parse_assign(const JechToken *t, int remaining)
```

Analisa reatribuição de variável: `x = novoValor;`

---

## 🎯 Ponto de Entrada Principal

```c
JechASTNode **_JechParser_ParseAll(const JechTokenList *tokens, int *out_count)
```

Esta função orquestra todo o processo de parsing:

1. **Aloca** array para nós raiz da AST
2. **Itera** através dos tokens
3. **Corresponde** cada token contra padrões conhecidos
4. **Despacha** para a função de parse apropriada
5. **Coleta** nós AST resultantes
6. **Retorna** array de raízes e contagem

### Exemplo Passo a Passo

Tokens de entrada (do tokenizer):
```text
TOKEN_KEEP "idade"
TOKEN_IDENTIFIER "idade"
TOKEN_EQUALS "="
TOKEN_NUMBER "25"
TOKEN_SEMICOLON ";"
TOKEN_WHEN "when"
...
```

Saída AST:
```text
roots[0] = JECH_AST_KEEP (name="idade", value="25")
roots[1] = JECH_AST_WHEN
           ├── left: JECH_AST_BIN_OP (>)
           │         ├── left: JECH_AST_IDENTIFIER ("idade")
           │         └── right: JECH_AST_NUMBER_LITERAL ("18")
           ├── right: JECH_AST_SAY ("adulto")
           └── else_branch: JECH_AST_SAY ("menor")
```

---

## ⚠️ Tratamento de Erros

O parser fornece mensagens de erro detalhadas:

```c
report_syntax_error("Esperado '(' após 'when'", token.line, token.column);
report_syntax_error("Faltando ponto e vírgula após 'say'", token.line, token.column);
report_syntax_error("Condição inválida na instrução 'when'", token.line, token.column);
```

Cada erro inclui:
- **O que deu errado** — descrição clara
- **Onde aconteceu** — número da linha e coluna

---

## 💡 Conceitos-Chave para Aprendizes

1. **Descida recursiva** — cada regra gramatical torna-se uma função
2. **Lookahead** — espiar tokens futuros para decidir qual regra aplicar
3. **Consumo de tokens** — avançar pelos tokens conforme você os corresponde
4. **Recuperação de erros** — reportar erros claramente e parar graciosamente

---
