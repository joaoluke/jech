## 🧠 Propósito do `vm.c`

> Interpretar instruções de bytecode sequencialmente e executar seus efeitos no ambiente de execução da linguagem JECH.

---

## 🔍 Análise Completa do Código

### 1. **Tabela de Variáveis**

```c
typedef struct {
	char name[MAX_STRING];
	char value[MAX_STRING];
} JechVariable;

static JechVariable variables[MAX_VARS];
static int var_count = 0;
```

* Armazena variáveis declaradas com `keep`.
* Usa uma lista fixa de até 64 variáveis (`MAX_VARS`).
* Cada variável tem `name` e `value`, ambos como strings (mesmo que seja um número ou booleano).

---

### 2. **Função `set_variable(...)`**

```c
static void set_variable(const char *name, const char *value)
```

* Verifica se a variável já existe:

* Se sim, atualiza o valor.
* Se não, adiciona uma nova entrada na tabela.
* Garante que o nome da variável seja único na lista.

🧠 Exemplo:

```jc
keep x = "olá";
keep x = "mundo"; // sobrescreve "olá"
```

---

### 3. **Função `get_variable(...)`**

```c
static const char *get_variable(const char *name)
```

* Retorna o valor da variável, se encontrada.
* Se não encontrada, retorna `NULL`.

> ⚠️ Ainda não é usado em `say(x)`, mas será útil para isso no futuro.

---

### 4. **Função Principal: `_JechVM_Execute(...)`**

```c
void _JechVM_Execute(const Bytecode *bc)
```

Esta função:

* Itera linearmente pelo array de instruções (`bc->instructions[i]`).
* Para cada instrução, executa baseado no `inst.op`:

| Opcode    | Ação                                               |
| --------- | -------------------------------------------------- |
| `OP_SAY`  | Imprime `inst.operand` no terminal                 |
| `OP_KEEP` | Salva `inst.name = inst.operand` na tabela de vars |
| `OP_END`  | Termina a execução                                 |
| `default` | Erro: opcode desconhecido                          |

---

### 💡 Exemplo de Execução

Dado este código JECH:

```jc
keep nome = "JECH";
say("Bem-vindo!");
```

Após passar por todas as etapas:

1. **Bytecode gerado:**

```text
[0] OP_KEEP → nome = "JECH"
[1] OP_SAY  → "Bem-vindo!"
[2] OP_END
```

2. **Executando a VM:**

```bash
> Bem-vindo!
```

---
