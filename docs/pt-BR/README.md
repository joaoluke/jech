<div align="center">

[![JECH Lang][repo_logo_img]][repo_url]

# Bem-vindo ao JECH Lang

[![Wiki][repo_wiki_img]][repo_wiki_url]
[![License][repo_license_img]][repo_license_url]

Uma linguagem de programação criada com amor, como uma homenagem à próxima geração — e um convite a qualquer um que queira aprender como as linguagens nascem, crescem e se tornam realidade.

</div>

## 📘 Introdução

> Aposto que você já sabe programar. Talvez já tenha construído coisas legais em Python, JavaScript ou até C. Mas... você já se perguntou como essas linguagens realmente funcionam por baixo dos panos?
>
> Como um comando como `print("Hello")` se transforma em instruções que sua máquina consegue entender?
>
> O JECH foi criado exatamente para essa curiosidade — e para você. Uma linguagem feita por um programador, para programadores. Uma jornada passo a passo, simples e acessível, do código bruto até a saída executada, mesmo que você nunca tenha tocado em compiladores, interpretadores ou programação de baixo nível.

O projeto JECH Lang foi criado para demonstrar, passo a passo, como uma linguagem de programação pode ser construída do zero — de forma simples, clara e didática. Ele foi desenvolvido para entusiastas de programação que desejam mergulhar no fascinante mundo do design de linguagens, usando C como base, assim como Python é construído em CPython.

## 🎯 Propósito

JECH é uma linguagem de programação criada com o objetivo de **ensinar, explorar e celebrar o processo de construção de uma linguagem do zero**.

Ela foi projetada para ser simples, legível e modular — permitindo que qualquer pessoa, mesmo com experiência mínima em programação de baixo nível, acompanhe seu desenvolvimento e entenda como um interpretador completo funciona, do analisador léxico à máquina virtual.

JECH não visa competir com as linguagens existentes. Em vez disso, serve como uma plataforma de aprendizado, uma jornada documentada e uma fonte de inspiração para desenvolvedores curiosos sobre compiladores, design de linguagens e o funcionamento interno dos interpretadores.

## 📖 História

O JECH nasceu de um desejo pessoal de aprender como uma linguagem de programação é construída — desde os conceitos mais fundamentais até um interpretador funcional.

Mas este projeto não é só para mim.

O JECH também foi criado para servir como um recurso de ensino — um **guia transparente, bem documentado e passo a passo** sobre como as linguagens de programação funcionam internamente. Eu queria compartilhar essa experiência de aprendizado com outros desenvolvedores que, como eu, têm curiosidade sobre o que acontece nos bastidores.

## 💡 Por que o nome "JECH"?

O nome "JECH" é uma homenagem aos meus dois filhos: **Jonathan Edwards** e **Charles Haddon**.
Combina as iniciais dos nomes deles como um gesto simbólico — representando não apenas a criação técnica de uma linguagem, mas também um legado de amor, curiosidade e inspiração.

## 🧠 Comandos e Funcionalidades

### ✅ `say(...)` — Saída

> Imprime um valor no terminal.

**Tipos suportados:**

- ✅ **String** → `say("Olá, JECH!");`
- ✅ **Boolean** → `say(true);`, `say(false);`
- ✅ **Inteiro** → `say(42);`
- ✅ **Float** → `say(3.14);`
- ✅ **Variáveis** → `keep x = "Oi!"; say(x);`

---

### ✅ `keep` — Declaração de Variável

> Declara uma nova variável que pode ser reutilizada ao longo do programa.

```jc
keep nome = "JECH";
keep idade = 25;
keep ativo = true;

say(nome);   // Saída: JECH
say(idade);  // Saída: 25
```

---

### ✅ Reatribuição de Variável

> Após declarar uma variável com `keep`, você pode reatribuir seu valor.

```jc
keep status = true;
status = false;
say(status);  // Saída: false
```

---

### ✅ `when` — Estruturas Condicionais

> Executa um bloco de código baseado em uma condição.

#### Condições Booleanas

```jc
keep mostrar = true;

when (mostrar) {
    say("Olá!");
}
```

#### Operadores de Comparação (`==`, `>`, `<`)

```jc
keep idade = 25;

when (idade > 18) {
    say("Você é adulto");
}
```

```jc
keep nome = "João";

when (nome == "João") {
    say("Bem-vindo, João!");
}
```

---

### ✅ `else` — Bloco Alternativo

> Executa um bloco quando a condição do `when` é `false`.

```jc
keep idade = 15;

when (idade > 18) {
    say("adulto");
}
else {
    say("menor");
}
// Saída: menor
```

```jc
keep logado = false;

when (logado) {
    say("Bem-vindo de volta!");
}
else {
    say("Por favor, faça login");
}
// Saída: Por favor, faça login
```

## 🚀 Início Rápido

### Compilando o JECH

```bash
# Clone o repositório
git clone https://github.com/joaoluke/jech.git
cd jech

# Compile
make

# Execute um programa JECH
./build/jech main.jc
```

### Seu Primeiro Programa

Crie um arquivo chamado `hello.jc`:

```jc
keep nome = "Mundo";
say("Olá, JECH!");
say(nome);
```

Execute:

```bash
./build/jech hello.jc
# Saída:
# Olá, JECH!
# Mundo
```

---

## ⚙️ Pipeline de Arquitetura

O JECH implementa um **pipeline de interpretador totalmente modular**, inspirado em como o CPython funciona:

```text
┌─────────────────┐
│  Código Fonte   │  →  keep x = 10; say(x);
└────────┬────────┘
         ▼
┌─────────────────┐
│   Tokenizador   │  →  Quebra código em tokens: KEEP, IDENTIFIER, EQUALS, NUMBER...
└────────┬────────┘
         ▼
┌─────────────────┐
│     Parser      │  →  Valida sintaxe e cria nós da AST
└────────┬────────┘
         ▼
┌─────────────────┐
│       AST       │  →  Estrutura em árvore representando o programa
└────────┬────────┘
         ▼
┌─────────────────┐
│    Bytecode     │  →  Converte AST em instruções: OP_KEEP, OP_SAY...
└────────┬────────┘
         ▼
┌─────────────────┐
│ Máquina Virtual │  →  Executa bytecode e produz saída
└─────────────────┘
```

### 🔬 Entendendo Cada Etapa

Cada etapa é **totalmente modular** — você pode inspecionar, modificar ou substituir qualquer componente independentemente. Isso torna o JECH perfeito para aprender como interpretadores funcionam.

| Etapa | Arquivo | Propósito |
|-------|---------|-----------|
| **Tokenizador** | `tokenizer.c` | Converte código fonte em tokens |
| **Parser** | `parser.c` | Valida sintaxe, cria AST |
| **AST** | `ast.c` | Estrutura em árvore para representação do programa |
| **Bytecode** | `bytecode.c` | Compila AST em instruções da VM |
| **VM** | `vm.c` | Executa instruções de bytecode |

### 📂 Documentação Detalhada

- [Visão Geral da Arquitetura](arquitetura.md) — Walkthrough completo do pipeline
- [Design do Tokenizador](tokenizador.md) — Como funciona a análise léxica
- [Parser](parser.md) — Validação de sintaxe e geração da AST
- [AST](ast.md) — Estrutura da Árvore Sintática Abstrata
- [Bytecode](bytecode.md) — Compilação de instruções
- [Máquina Virtual](vm.md) — Execução do bytecode

## 🌐 Idiomas Disponíveis

- [🇺🇸 English (en)](../../README.md)
- [🇧🇷 Português (pt-BR)](README.md)

## 🤝 Contribuidores

Agradecimentos a essas pessoas maravilhosas (🔥):

<table>
  <tr>
    <td align="center"><a href="https://github.com/joaoluke"><img src="https://avatars.githubusercontent.com/u/62743404?v=4?s=100" width="100px;" alt=""/><br /><sub><b>João Lucas</b></sub></a><br />Criador e Mantenedor</td>
  </tr>
</table>

## ⚠️ Licença

[`JECH Lang`][repo_url] é um software livre e de código aberto licenciado sob a [Licença Apache 2.0][repo_license_url].

<!-- Repository -->

[repo_url]: https://github.com/joaoluke/jech
[repo_logo_url]: https://github.com/joaoluke/jech/wiki/Logo
[repo_logo_img]: ../../images/jc_logo.png
[repo_license_url]: https://github.com/joaoluke/jech/blob/main/LICENSE
[repo_license_img]: https://img.shields.io/badge/license-Apache_2.0-red?style=for-the-badge&logo=none
[repo_wiki_url]: https://github.com/joaoluke/jech/wiki
[repo_wiki_img]: https://img.shields.io/badge/docs-wiki_page-blue?style=for-the-badge&logo=none

