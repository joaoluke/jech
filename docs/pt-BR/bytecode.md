# ⚙️ Compilador de Bytecode

## O que é Bytecode?

**Bytecode** é uma representação intermediária entre seu código fonte e a execução na máquina. É uma sequência de instruções simples que a Máquina Virtual pode executar eficientemente.

Pense nisso como linguagem assembly, mas projetada especificamente para a VM da sua linguagem.

### Por que Bytecode?

1. **Mais simples que código de máquina** — mais fácil de gerar e debugar
2. **Portável** — roda em qualquer plataforma com a VM
3. **Otimizável** — pode ser analisado e melhorado antes da execução

---

## 📊 Tipos de Instrução (OpCodes)

```c
typedef enum {
    OP_SAY,       // Imprimir um valor
    OP_KEEP,      // Declarar uma variável
    OP_ASSIGN,    // Reatribuir uma variável
    OP_BIN_OP,    // Operação binária (+, -, *, /)
    OP_WHEN,      // Condicional com comparação (>, <, ==)
    OP_WHEN_BOOL, // Condicional com booleano/identificador
    OP_END        // Fim do programa
} OpCode;
```

---

## 🏗️ Estrutura da Instrução

```c
typedef struct {
    OpCode op;                    // Qual operação executar
    char name[MAX_STRING];        // Nome da variável ou var de condição
    char operand[MAX_STRING];     // Valor primário
    char operand_right[MAX_STRING]; // Valor secundário (para comparações)
    char else_operand[MAX_STRING];  // Valor do bloco else
    JechTokenType bin_op;         // Tipo do operador (>, <, ==, +, -)
    JechTokenType token_type;     // Tipo do valor (STRING, NUMBER, etc.)
    JechTokenType cmp_operand_type; // Tipo do operando de comparação
    JechTokenType else_token_type;  // Tipo do valor else
    int has_else;                 // Flag para bloco else
    int line, column;             // Localização no fonte para erros
} Instruction;
```

---

## 🔧 Funções de Compilação

### `compile_say`

```c
static void compile_say(Bytecode *bc, const JechASTNode *node)
```

Compila uma declaração `say(...)`:

```jc
say("Olá!");
```

Se torna:
```text
{ op: OP_SAY, operand: "Olá!", token_type: TOKEN_STRING }
```

---

### `compile_keep`

```c
static void compile_keep(Bytecode *bc, const JechASTNode *node)
```

Compila uma declaração de variável:

```jc
keep idade = 25;
```

Se torna:
```text
{ op: OP_KEEP, name: "idade", operand: "25", token_type: TOKEN_NUMBER }
```

---

### `compile_assign`

```c
static void compile_assign(Bytecode *bc, const JechASTNode *node)
```

Compila uma reatribuição de variável:

```jc
idade = 30;
```

Se torna:
```text
{ op: OP_ASSIGN, name: "idade", operand: "30", token_type: TOKEN_NUMBER }
```

---

### `compile_when`

```c
static void compile_when(Bytecode *bc, const JechASTNode *node)
```

Compila declarações condicionais. Esta é a função mais complexa porque lida com múltiplos casos:

#### Caso 1: Condição de comparação
```jc
when (idade > 18) { say("adulto"); } else { say("menor"); }
```

Se torna:
```text
{
    op: OP_WHEN,
    name: "idade",           // Variável a comparar
    bin_op: TOKEN_GT,        // Operador >
    operand: "18",           // Comparar contra
    operand_right: "adulto", // Valor do bloco então
    has_else: 1,
    else_operand: "menor"    // Valor do bloco else
}
```

#### Caso 2: Condição booleana/identificador
```jc
when (ativo) { say("sim"); } else { say("não"); }
```

Se torna:
```text
{
    op: OP_WHEN_BOOL,
    name: "ativo",         // Variável a verificar
    operand: "sim",        // Valor do bloco então
    has_else: 1,
    else_operand: "não"    // Valor do bloco else
}
```

---

## 🎯 Ponto de Entrada Principal

```c
Bytecode _JechBytecode_CompileAll(JechASTNode **roots, int count)
```

Orquestra a compilação de todos os nós da AST:

1. **Inicializa** estrutura de bytecode vazia
2. **Itera** pelas raízes da AST
3. **Despacha** para função de compilação apropriada baseada no tipo do nó
4. **Adiciona** instrução `OP_END`
5. **Retorna** bytecode completo

### Exemplo Completo

Código fonte:
```jc
keep idade = 25;
when (idade > 18) {
    say("adulto");
}
else {
    say("menor");
}
```

Bytecode gerado:
```text
[0] OP_KEEP      name="idade", operand="25"
[1] OP_WHEN      name="idade", bin_op=GT, operand="18", 
                 operand_right="adulto", has_else=1, else_operand="menor"
[2] OP_END
```

---

## 💡 Conceitos-Chave para Aprendizes

1. **Linearização** — árvores se tornam sequências planas de instruções
2. **Todos os dados são strings** — a VM interpreta tipos em tempo de execução
3. **Uma instrução por declaração** — mantém a execução simples
4. **Metadados importam** — tipos de token ajudam a VM a tomar decisões

---

## 🔬 Como o Bytecode Conecta com Outras Etapas

```text
Tokens → Parser → AST → Bytecode → VM
                          ↑
                     Você está aqui
```

O compilador de bytecode lê a AST e produz instruções que a VM pode executar diretamente.

---
