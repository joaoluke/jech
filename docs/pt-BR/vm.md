# 🧠 Máquina Virtual (VM)

## O que é uma Máquina Virtual?

A **Máquina Virtual** é a etapa final do pipeline. Ela lê instruções de bytecode e as executa, produzindo a saída real do programa.

Pense nela como uma CPU, mas implementada em software e projetada especificamente para sua linguagem.

### Por que uma VM?

1. **Abstração** — esconde a complexidade do hardware
2. **Portabilidade** — mesmo bytecode roda em qualquer lugar
3. **Segurança** — ambiente de execução controlado
4. **Simplicidade** — mais fácil de implementar que geração de código nativo

---

## 📊 Ambiente de Execução

### Armazenamento de Variáveis

```c
typedef struct {
    char name[MAX_STRING];
    char value[MAX_STRING];
} JechVariable;

static JechVariable variables[MAX_VARS];  // Até 64 variáveis
static int var_count = 0;
```

Variáveis são armazenadas como **pares nome-valor** em um array simples. Todos os valores são strings internamente — a VM os interpreta baseado no contexto.

---

## 🔧 Funções Principais

### `_JechVM_SetVariable`

```c
void _JechVM_SetVariable(const char *name, const char *value)
```

Armazena ou atualiza uma variável:
- Se variável existe → atualiza seu valor
- Se variável é nova → adiciona à tabela

---

### `_JechVM_GetVariable`

```c
const char *_JechVM_GetVariable(const char *name)
```

Recupera o valor de uma variável pelo nome. Retorna `NULL` se não encontrada.

---

### `variable_exists`

```c
bool variable_exists(const char *name)
```

Verifica se uma variável foi declarada. Usado para prevenir atribuição a variáveis não declaradas.

---

## 🎯 Loop Principal de Execução

```c
void _JechVM_Execute(const Bytecode *bc)
```

O coração da VM — um loop simples que processa cada instrução:

```c
for (int i = 0; i < bc->count; i++) {
    Instruction inst = bc->instructions[i];
    
    switch (inst.op) {
        case OP_SAY:    // Tratar saída
        case OP_KEEP:   // Tratar declaração
        case OP_ASSIGN: // Tratar reatribuição
        case OP_WHEN:   // Tratar condicionais de comparação
        case OP_WHEN_BOOL: // Tratar condicionais booleanos
        case OP_END:    // Parar execução
    }
}
```

---

## 📋 Handlers de Instrução

### `OP_SAY` — Saída

Imprime um valor no terminal:

```c
case OP_SAY:
    if (inst.token_type == TOKEN_IDENTIFIER) {
        // É uma variável — buscar seu valor
        const char *value = _JechVM_GetVariable(inst.operand);
        printf("%s\n", value);
    } else {
        // É um literal — imprimir diretamente
        printf("%s\n", inst.operand);
    }
```

---

### `OP_KEEP` — Declaração de Variável

Cria uma nova variável:

```c
case OP_KEEP:
    if (_JechVM_GetVariable(inst.name) != NULL) {
        // Erro: variável já existe!
        report_runtime_error("Variável já declarada", ...);
    }
    _JechVM_SetVariable(inst.name, inst.operand);
```

---

### `OP_ASSIGN` — Reatribuição

Atualiza uma variável existente:

```c
case OP_ASSIGN:
    if (!variable_exists(inst.name)) {
        // Erro: não pode atribuir a variável não declarada!
        report_runtime_error("Não pode atribuir a variável não declarada", ...);
    }
    _JechVM_SetVariable(inst.name, inst.operand);
```

---

### `OP_WHEN` — Condicionais de Comparação

Trata condições como `idade > 18` ou `nome == "João"`:

```c
case OP_WHEN:
    // Obter valor esquerdo (variável)
    const char *left_val = _JechVM_GetVariable(inst.name);
    
    // Obter valor direito (literal ou variável)
    const char *right_val = inst.operand;
    
    // Comparar baseado no tipo
    if (inst.cmp_operand_type == TOKEN_STRING) {
        // Comparação de string
        is_true = (strcmp(left_val, right_val) == 0);
    } else {
        // Comparação numérica
        is_true = (atof(left_val) > atof(right_val));
    }
    
    // Executar bloco apropriado
    if (is_true) {
        printf("%s\n", inst.operand_right);  // Bloco então
    } else if (inst.has_else) {
        printf("%s\n", inst.else_operand);   // Bloco else
    }
```

---

### `OP_WHEN_BOOL` — Condicionais Booleanos

Trata condições como `when (ativo)` ou `when (true)`:

```c
case OP_WHEN_BOOL:
    bool is_true;
    
    if (inst.bin_op == TOKEN_BOOL) {
        // Literal: true ou false
        is_true = strcmp(inst.name, "true") == 0;
    } else {
        // Variável: buscar seu valor
        const char *val = _JechVM_GetVariable(inst.name);
        is_true = strcmp(val, "true") == 0;
    }
    
    // Executar bloco apropriado
    if (is_true) {
        printf("%s\n", inst.operand);
    } else if (inst.has_else) {
        printf("%s\n", inst.else_operand);
    }
```

---

## 💡 Exemplo Completo de Execução

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

Trace de execução:
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

Saída:
```
adulto
```

---

## ⚠️ Erros de Runtime

A VM captura e reporta erros:

| Erro | Causa |
|------|-------|
| `Variável indefinida 'x'` | Usando uma variável que não foi declarada |
| `Variável já declarada` | Usando `keep` em uma variável existente |
| `Não pode atribuir a variável não declarada` | Atribuição sem `keep` primeiro |
| `Divisão por zero` | Dividindo por zero em aritmética |

---

## 💡 Conceitos-Chave para Aprendizes

1. **Execução sem pilha** — JECH usa um modelo linear simples
2. **Tipagem dinâmica** — tipos são determinados em tempo de execução
3. **Armazenamento baseado em string** — tudo é string internamente
4. **Falha rápida** — erros param a execução imediatamente

---

## 🔬 Como a VM Conecta com Outras Etapas

```text
Tokens → Parser → AST → Bytecode → VM
                                    ↑
                               Você está aqui
```

A VM é o **destino final** — ela pega bytecode e produz a saída real do programa.

---
