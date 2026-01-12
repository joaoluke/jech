# 📐 Visão Geral da Arquitetura do JECH Lang

Este documento explica a pipeline completa de compilação e execução da linguagem JECH, desde o código-fonte bruto até a saída final — usando o exemplo:

```jc
say("Olá, Mundo!");
```

Vamos detalhar como este código passa por cada estágio:

---

## 1. 🧾 Tokenizer (Análise Léxica)

**Arquivo:** `tokenizer.c`
**Função:** `_JechTokenizer_Lex`

### 🔧 O que faz:

Converte o código-fonte bruto em um fluxo de **tokens**.

### Exemplo:

```c
say("Olá, Mundo!");
```

torna-se:

```text
TOKEN_SAY       → "say"
TOKEN_LPAREN    → "("
TOKEN_STRING    → "Olá, Mundo!"
TOKEN_RPAREN    → ")"
TOKEN_SEMICOLON → ";"
```

- [Documentação do Tokenizer](tokenizer.md)

---

## 2. 🧱 Parser

**Arquivo:** `parser.c`
**Função:** `_JechParser_ParseAll`

### 🔧 O que faz:

Lê os tokens e identifica **padrões de instruções**. Cria uma lista de **nós raiz da AST**.

### Saída:

Um nó AST representando a instrução `say("Olá, Mundo!")`.

- [Documentação do Parser](parser.md)

---

## 3. 🌳 AST (Árvore de Sintaxe Abstrata)

**Arquivo:** `ast.c`
**Função:** `_JechAST_CreateNode`

### 🔧 O que faz:

Constrói árvores estruturadas para representar o significado do código.
Cada instrução torna-se um nó, possivelmente com filhos (ainda não nesta versão).

### Exemplo:

```text
• JECH_AST_SAY ("Olá, Mundo!")
```

A AST para nosso exemplo tem apenas um nó.

- [Documentação da AST](ast.md)

---

## 4. 🔤 Compilador de Bytecode

**Arquivo:** `bytecode.c`
**Função:** `_JechBytecode_CompileAll`

### 🔧 O que faz:

Converte nós da AST em **instruções de bytecode**.

### Exemplo:

```text
[0] OP_SAY  → operando: "Olá, Mundo!"
[1] OP_END
```

Este bytecode pode ser armazenado, otimizado ou executado diretamente.

- [Documentação do Bytecode](bytecode.md)

---

## 5. 🧠 Máquina Virtual (VM)

**Arquivo:** `vm.c`
**Função:** `_JechVM_Execute`

### 🔧 O que faz:

Lê e executa instruções de bytecode.

### Exemplo:

Executa:

```text
OP_SAY  → imprime "Olá, Mundo!"
OP_END  → para a execução
```

Saída no terminal:

```
Olá, Mundo!
```

- [Documentação da VM](vm.md)

---

## ✅ Resumo

```text
say("Olá, Mundo!");
       │
       ▼
[Tokenizer] → [Parser] → [AST] → [Bytecode] → [Execução VM]
```

Cada etapa no JECH é modular e extensível. Você pode inspecionar ou modificar qualquer estágio desta pipeline independentemente, tornando-a uma ótima ferramenta para aprender ou experimentar com design de linguagens.

---

## 🧩 Resumo de Responsabilidades dos Arquivos

| Estágio         | Arquivo       | Função Principal           |
| --------------- | ------------- | -------------------------- |
| Tokenizer       | `tokenizer.c` | `_JechTokenizer_Lex`       |
| Parser          | `parser.c`    | `_JechParser_ParseAll`     |
| Construtor AST  | `ast.c`       | `_JechAST_CreateNode`      |
| Gerador Bytecode| `bytecode.c`  | `_JechBytecode_CompileAll` |
| Máquina Virtual | `vm.c`        | `_JechVM_Execute`          |

> Esta configuração modular torna o JECH uma excelente ferramenta educacional para entender compiladores e interpretadores.
