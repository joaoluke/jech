# 📐 Visão Geral da Arquitetura do JECH Lang

Este documento explica o **pipeline completo de compilação e execução** da linguagem JECH. Vamos rastrear como o código fonte se transforma em saída, passo a passo.

## 🎯 A Visão Geral

```text
┌──────────────┐    ┌─────────────┐    ┌────────┐    ┌──────────┐    ┌─────┐
│ Código Fonte │ → │ Tokenizador │ → │ Parser │ → │ Bytecode │ → │ VM  │ → Saída
└──────────────┘    └─────────────┘    └────────┘    └──────────┘    └─────┘
   arquivo .jc         Tokens           AST        Instruções     Execução
```

Vamos rastrear este exemplo completo através de cada etapa:

```jc
keep idade = 25;
when (idade > 18) {
    say("adulto");
}
else {
    say("menor");
}
```

---

## 1. 🧾 Tokenizador (Análise Léxica)

**Arquivo:** `tokenizer.c`  
**Função:** `_JechTokenizer_Lex`

### 🔧 O que faz:

Lê o código fonte caractere por caractere e agrupa em **tokens** — as menores unidades significativas da linguagem.

### Nosso Exemplo Se Torna:

```text
[0]  TOKEN_KEEP       "keep"
[1]  TOKEN_IDENTIFIER "idade"
[2]  TOKEN_EQUALS     "="
[3]  TOKEN_NUMBER     "25"
[4]  TOKEN_SEMICOLON  ";"
[5]  TOKEN_WHEN       "when"
[6]  TOKEN_LPAREN     "("
[7]  TOKEN_IDENTIFIER "idade"
[8]  TOKEN_GT         ">"
[9]  TOKEN_NUMBER     "18"
[10] TOKEN_RPAREN     ")"
[11] TOKEN_LBRACE     "{"
[12] TOKEN_SAY        "say"
[13] TOKEN_LPAREN     "("
[14] TOKEN_STRING     "adulto"
[15] TOKEN_RPAREN     ")"
[16] TOKEN_SEMICOLON  ";"
[17] TOKEN_RBRACE     "}"
[18] TOKEN_ELSE       "else"
[19] TOKEN_LBRACE     "{"
[20] TOKEN_SAY        "say"
[21] TOKEN_LPAREN     "("
[22] TOKEN_STRING     "menor"
[23] TOKEN_RPAREN     ")"
[24] TOKEN_SEMICOLON  ";"
[25] TOKEN_RBRACE     "}"
[26] TOKEN_EOF
```

📚 [Documentação do Tokenizador](tokenizador.md)

---

## 2. 🧱 Parser

**Arquivo:** `parser.c`  
**Função:** `_JechParser_ParseAll`

### 🔧 O que faz:

Valida que os tokens formam **padrões de sintaxe** corretos e cria **nós da AST** representando a estrutura do programa.

### Nosso Exemplo Se Torna:

O parser reconhece duas declarações e cria dois nós raiz da AST:

```text
roots[0] = JECH_AST_KEEP
           ├── name: "idade"
           └── value: "25"

roots[1] = JECH_AST_WHEN
           ├── left (condição): JECH_AST_BIN_OP (>)
           │                    ├── left: JECH_AST_IDENTIFIER ("idade")
           │                    └── right: JECH_AST_NUMBER_LITERAL ("18")
           ├── right (então): JECH_AST_SAY ("adulto")
           └── else_branch: JECH_AST_SAY ("menor")
```

📚 [Documentação do Parser](parser.md)

---

## 3. 🌳 AST (Árvore Sintática Abstrata)

**Arquivo:** `ast.c`  
**Função:** `_JechAST_CreateNode`

### 🔧 O que faz:

Fornece a **estrutura de dados** para representar elementos do programa como uma árvore. Cada nó contém:
- **Tipo** — que tipo de elemento (SAY, KEEP, WHEN, etc.)
- **Valor/Nome** — dados associados
- **Filhos** — ponteiros left, right e else_branch

### Por que Árvores?

Árvores capturam **relacionamentos hierárquicos**. A declaração `when` contém uma condição E um corpo E um bloco else — esse aninhamento é natural em uma estrutura de árvore.

📚 [Documentação da AST](ast.md)

---

## 4. 🔤 Compilador de Bytecode

**Arquivo:** `bytecode.c`  
**Função:** `_JechBytecode_CompileAll`

### 🔧 O que faz:

Transforma a AST em uma **sequência linear de instruções** que a VM pode executar.

### Nosso Exemplo Se Torna:

```text
[0] OP_KEEP
    name: "idade"
    operand: "25"
    token_type: TOKEN_NUMBER

[1] OP_WHEN
    name: "idade"            // Variável a comparar
    bin_op: TOKEN_GT         // Operador >
    operand: "18"            // Comparar contra
    operand_right: "adulto"  // Saída do bloco então
    has_else: 1
    else_operand: "menor"    // Saída do bloco else

[2] OP_END
```

📚 [Documentação do Bytecode](bytecode.md)

---

## 5. 🧠 Máquina Virtual (VM)

**Arquivo:** `vm.c`  
**Função:** `_JechVM_Execute`

### 🔧 O que faz:

Executa instruções de bytecode uma por uma, gerenciando variáveis e produzindo saída.

### Nosso Exemplo Executa:

```text
Passo 1: OP_KEEP
         → Armazenar variável: idade = "25"
         → Variáveis: [{ name: "idade", value: "25" }]

Passo 2: OP_WHEN
         → Obter variável "idade" → "25"
         → Comparar: 25 > 18 → true
         → Executar bloco então: imprimir "adulto"

Passo 3: OP_END
         → Parar execução
```

### Saída no Terminal:

```
adulto
```

📚 [Documentação da VM](vm.md)

---

## ✅ Resumo

Nossa jornada completa:

```text
Código Fonte (.jc)
       │
       ▼
┌─────────────┐
│ Tokenizador │  "keep idade = 25;" → [KEEP, IDENTIFIER, EQUALS, NUMBER, SEMICOLON]
└──────┬──────┘
       ▼
┌─────────────┐
│   Parser    │  Tokens → Nós da AST com estrutura
└──────┬──────┘
       ▼
┌─────────────┐
│  Bytecode   │  AST → [OP_KEEP, OP_WHEN, OP_END]
└──────┬──────┘
       ▼
┌─────────────┐
│     VM      │  Executar instruções → "adulto"
└─────────────┘
```

---

## 🧩 Resumo de Responsabilidade dos Arquivos

| Etapa | Arquivo | Função Principal | Propósito |
|-------|---------|------------------|-----------|
| **Tokenizador** | `tokenizer.c` | `_JechTokenizer_Lex` | Quebrar fonte em tokens |
| **Parser** | `parser.c` | `_JechParser_ParseAll` | Validar sintaxe, criar AST |
| **AST** | `ast.c` | `_JechAST_CreateNode` | Estrutura em árvore para programa |
| **Bytecode** | `bytecode.c` | `_JechBytecode_CompileAll` | Compilar AST em instruções |
| **VM** | `vm.c` | `_JechVM_Execute` | Executar bytecode |

---

## 💡 Por que Esta Arquitetura?

1. **Modularidade** — cada etapa é independente e testável
2. **Debugabilidade** — você pode inspecionar a saída em qualquer etapa
3. **Extensibilidade** — adicione novas funcionalidades sem reescrever tudo
4. **Educacional** — espelha como linguagens reais (Python, JavaScript) funcionam

> Esta configuração modular torna o JECH uma excelente ferramenta educacional para entender compiladores e interpretadores.

---

## 🔗 Links para Aprofundamento

- [Tokenizador](tokenizador.md) — Detalhes da análise léxica
- [Parser](parser.md) — Validação de sintaxe e geração da AST
- [AST](ast.md) — Estrutura em árvore e gerenciamento de memória
- [Bytecode](bytecode.md) — Compilação de instruções
- [VM](vm.md) — Execução do bytecode
