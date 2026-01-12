## ⚙️ Papel do `bytecode.c`

Este arquivo é responsável por:

> 🚧 **Converter a AST (árvore de comandos) em bytecode linear**
> que será posteriormente executado pela máquina virtual.

---

## 🔍 Análise do Código

### 1. **Função auxiliar: `compile_say`**

```c
static void compile_say(Bytecode *bc, const JechASTNode *node)
```

* Cria uma instrução do tipo `OP_SAY`.
* Copia o valor (`node->value`) para o campo `operand`.
* Armazena o tipo de token original (ex: `TOKEN_STRING`, `TOKEN_NUMBER`).
* Incrementa o contador de instruções.

📦 Isso transforma o comando `say("olá")` em:

```text
{ op: OP_SAY, operand: "olá", token_type: TOKEN_STRING }
```

---

### 2. **Função auxiliar: `compile_keep`**

```c
static void compile_keep(Bytecode *bc, const JechASTNode *node)
```

* Cria uma instrução `OP_KEEP`.
* Define `name` como o identificador da variável.
* Define `operand` como o valor atribuído.
* Também armazena o tipo do valor.

🧠 Exemplo:

```jc
keep x = 42;
```

torna-se:

```text
{ op: OP_KEEP, name: "x", operand: "42", token_type: TOKEN_NUMBER }
```

---

### 3. **Função principal: `_JechBytecode_CompileAll`**

```c
Bytecode _JechBytecode_CompileAll(JechASTNode **roots, int count)
```

#### 🚀 Esta é a função que varre toda a AST e compila cada nó em uma instrução:

* Inicializa uma nova estrutura `Bytecode` com contador 0.
* Itera sobre todos os nós na AST (`roots[i]`).
* Para cada nó, verifica seu tipo (`JECH_AST_SAY`, `JECH_AST_KEEP`...).

* Chama a função de compilação correspondente.
* Adiciona manualmente a instrução final `OP_END` ao fim do programa (marcando o fim da execução para a VM).

🧱 Exemplo de uma sequência de instruções:

```text
[0] OP_KEEP ("x" = "42")
[1] OP_SAY ("x")
[2] OP_END
```

---
