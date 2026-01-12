<div align="center">

[![JECH Logo][repo_logo_img]][repo_url]

# Linguagem de Programação JECH

[![Wiki][repo_wiki_img]][repo_wiki_url]
[![Licença][repo_license_img]][repo_license_url]

📖 **Leia em outros idiomas:** [English](README.md) | [Português (Brasil)](README_pt-BR.md)

**Já se perguntou como Python, JavaScript ou PHP realmente funcionam por baixo dos panos?**

JECH é uma linguagem de programação construída do zero para te ensinar exatamente isso — de forma clara, documentada e acessível.

</div>

---

## 🎯 Para Quem É Este Projeto?

**Você é um desenvolvedor que:**
- ✅ Conhece Python, JavaScript ou PHP
- ✅ Escreve código todos os dias
- ✅ Se pergunta "como o `print()` realmente funciona?"
- ❌ Nunca tocou em C ou compiladores
- ❌ Não sabe o que significa "bytecode"
- ❌ Acha "lexer" intimidante

**Perfeito!** JECH foi construído especificamente para você.

---

## 🤔 Que Problema o JECH Resolve?

### O Problema

Você sabe usar Python:
```python
print("Olá")
x = 10
if x > 5:
    print(x)
```

Mas você **não tem ideia** de como o Python realmente executa isso. É mágica! ✨

### A Solução

JECH mostra **exatamente** como funciona, passo a passo:

```
Seu Código → Tokenizer → Parser → AST → Bytecode → VM → Saída
   📝          🔤           🧱    🌳      🔧      ⚡     ✨
```

Cada estágio é:
- ✅ **Documentado** com exemplos
- ✅ **Explicado** em termos que você já conhece
- ✅ **Visível** - você pode ver acontecer
- ✅ **Modular** - cada peça é independente

---

## 🚀 Início Rápido (5 minutos)

### 1. Instalar

```bash
git clone https://github.com/seuusuario/jech
cd jech
make
```

### 2. Experimentar o REPL (Modo Interativo)

```bash
./build/jech
```

```jc
>>> keep x = 10;
>>> say(x);
10

>>> keep nome = "JECH";
>>> say(nome);
JECH

>>> keep numeros = [1, 2, 3];
>>> say(numeros[0]);
1
```

**É como o modo interativo do Python!**

### 3. Executar um Programa

```bash
./build/jech examples/17_arrays_basic.jc
```

---

## 📖 Aprenda Como Linguagens Funcionam

### Para Desenvolvedores Python

**Você conhece isso:**
```python
print("Olá")
```

**JECH mostra que isso acontece:**

```
1. Tokenizer quebra em: [print] [(] ["Olá"] [)] 
2. Parser entende: "Isso é um comando print"
3. Compilador gera: OP_PRINT "Olá"
4. VM executa: Imprime "Olá" na tela
```

**Mesmo processo que o Python usa!** (CPython faz exatamente isso)

### Para Desenvolvedores JavaScript

**Você conhece isso:**
```javascript
const x = 10;
console.log(x);
```

**JECH mostra:**
- Como o V8 tokeniza seu código
- Como o parser constrói uma AST
- Como o bytecode é gerado
- Como a VM executa

**Mesmos princípios, sintaxe diferente!**

### Para Desenvolvedores PHP

**Você conhece isso:**
```php
$x = 10;
echo $x;
```

**JECH revela:**
- Como o Zend Engine processa seu código
- Como os opcodes são gerados
- Como o executor os executa

**Mesma arquitetura!**

---

## 🎓 Caminho de Aprendizado

### Nível 1: Use (Comece Aqui!)

**Objetivo:** Ficar confortável com a sintaxe do JECH

```bash
# Experimente o REPL
./build/jech

# Execute exemplos
./build/jech examples/01_hello_world.jc
./build/jech examples/17_arrays_basic.jc
```

**Tempo:** 15 minutos  
**Docs:** [Recursos da Linguagem](#-recursos-da-linguagem)

---

### Nível 2: Entenda os Conceitos

**Objetivo:** Aprenda como linguagens funcionam (sem C necessário!)

**Leia:** [Guia Para Iniciantes](docs/pt/FOR_BEGINNERS.md)

Este guia explica:
- O que é um tokenizer? (com analogias Python)
- O que é um parser? (com exemplos JavaScript)
- O que é bytecode? (como arquivos `.pyc` do Python)
- O que é uma VM? (como CPython)

**Tempo:** 30 minutos  
**Pré-requisitos:** Nenhum! Apenas curiosidade

---

### Nível 3: Veja em Ação

**Objetivo:** Observe o código se transformar através de cada estágio

**Leia:** [Visão Geral da Arquitetura](docs/en/architecture.md)

Siga uma única linha de código:
```jc
say("Olá");
```

Através de todos os 5 estágios:
1. Tokenizer → `[say] [(] ["Olá"] [)] [;]`
2. Parser → `SAY_STATEMENT`
3. AST → `SAY_NODE { value: "Olá" }`
4. Bytecode → `OP_SAY "Olá"`
5. VM → `print("Olá")`

**Tempo:** 45 minutos  
**Pré-requisitos:** Nível 2

---

### Nível 4: Mergulho Profundo nos Componentes

**Objetivo:** Entenda cada componente em detalhes

**Leia:**
- [Tokenizer](docs/pt/architecture/tokenizer.md) - Como código vira tokens
- [Parser](docs/pt/architecture/parser.md) - Como tokens viram estrutura
- [AST](docs/pt/architecture/ast.md) - Como estrutura vira árvores
- [Bytecode](docs/pt/architecture/bytecode.md) - Como árvores viram instruções
- [VM](docs/pt/architecture/vm.md) - Como instruções viram execução

**Tempo:** 2-3 horas  
**Pré-requisitos:** Nível 3

---

### Nível 5: Contribua

**Objetivo:** Adicione recursos, corrija bugs, melhore docs

**Leia:** [Guia de Contribuição](CONTRIBUTING.md)

Você pode contribuir mesmo sem conhecer C:
- Escrever programas de exemplo
- Melhorar documentação
- Reportar bugs
- Sugerir recursos
- Escrever testes

**Tempo:** Contínuo  
**Pré-requisitos:** Entusiasmo!

---

## 🧠 Recursos da Linguagem

### Variáveis

```jc
keep x = 10;
keep nome = "João";
keep ativo = true;

say(x);        // 10
say(nome);     // João
say(ativo);    // true
```

**Como:** `x = 10` do Python, `const x = 10` do JavaScript, `$x = 10` do PHP

---

### Arrays

```jc
keep numeros = [1, 2, 3, 4, 5];
keep nomes = ["Alice", "Bob", "Charlie"];
keep misturado = [42, "texto", true];

say(numeros[0]);  // 1
say(nomes[1]);    // Bob
say(misturado[2]); // true
```

**Como:** Listas do Python, arrays do JavaScript, arrays do PHP

---

### Condicionais

```jc
keep idade = 20;

when (idade > 18) {
    say("Adulto");
}
else {
    say("Menor");
}
```

**Como:** `if` do Python, `if` do JavaScript, `if` do PHP

---

### Saída

```jc
say("Olá, Mundo!");
say(42);
say(true);
say(minhaVariavel);
say(meuArray[0]);
```

**Como:** `print()` do Python, `console.log()` do JavaScript, `echo` do PHP

---

## 🏗️ Arquitetura (A Mágica Revelada)

### A Pipeline

Cada linha de código passa por 5 estágios:

```
┌─────────────┐
│ Código Fonte│  say("Olá");
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Tokenizer  │  [say] [(] ["Olá"] [)] [;]
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Parser    │  SAY_STATEMENT { value: "Olá" }
└──────┬──────┘
       │
       ▼
┌─────────────┐
│     AST     │  SAY_NODE → "Olá"
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Bytecode   │  [OP_SAY "Olá"]
└──────┬──────┘
       │
       ▼
┌─────────────┐
│     VM      │  Executa: print "Olá"
└──────┬──────┘
       │
       ▼
    Saída: Olá
```

### Comparação com o Mundo Real

**Isso é exatamente como o Python funciona:**

| Estágio JECH | Equivalente Python | O Que Faz |
|--------------|-------------------|-----------|
| Tokenizer | módulo `tokenize` | Quebra código em pedaços |
| Parser | `ast.parse()` | Valida sintaxe |
| AST | `ast.AST` | Cria estrutura em árvore |
| Bytecode | arquivos `.pyc` | Compila para instruções |
| VM | CPython | Executa instruções |

**Mente explodida?** 🤯 Agora você sabe como o Python funciona!

---

## 🧪 Testes & Qualidade

JECH tem **70 testes automatizados** cobrindo:
- ✅ Tokenizer (32 asserções)
- ✅ Parser (25 asserções)
- ✅ VM (6 asserções)
- ✅ Integração (7 asserções)

### Executar Testes

```bash
./run_tests.sh
```

### Hooks de Pre-Commit

Execute testes automaticamente antes de cada commit:

```bash
./install_hooks.sh
```

**Como:** `pytest` do Python, `jest` do JavaScript, `PHPUnit` do PHP

---

## 📚 Documentação

### Para Iniciantes (Comece Aqui!)

- **[Guia Para Iniciantes](docs/en/FOR_BEGINNERS.md)** ⭐
  - Sem conhecimento de C necessário
  - Usa analogias Python/JavaScript
  - Explica cada conceito de forma simples

### Arquitetura

- **[Visão Geral da Arquitetura](docs/en/architecture.md)**
  - Explicação completa da pipeline
  - Diagramas visuais
  - Exemplos passo a passo

### Componentes (Mergulho Profundo)

- **[Tokenizer](docs/en/tokenizer.md)** - Análise léxica
- **[Parser](docs/en/parser.md)** - Análise sintática
- **[AST](docs/en/ast.md)** - Estruturas em árvore
- **[Bytecode](docs/en/bytecode.md)** - Compilação
- **[VM](docs/en/vm.md)** - Execução

### Contribuindo

- **[Guia de Contribuição](CONTRIBUTING.md)**
- **[Guia de Configuração](SETUP.md)**
- **[Documentação de Testes](tests/README.md)**

---

## 💡 Por Que JECH?

### Educacional

**Aprenda como suas linguagens favoritas funcionam:**
- Python (CPython)
- JavaScript (V8, SpiderMonkey)
- PHP (Zend Engine)
- Ruby (YARV)

Todas usam os mesmos princípios que o JECH demonstra!

### Transparente

**Cada estágio é visível:**
```bash
# Ver tokens
./build/jech --debug-tokens meuarquivo.jc

# Ver AST
./build/jech --debug-ast meuarquivo.jc

# Ver bytecode
./build/jech --debug-bytecode meuarquivo.jc
```

### Prático

**Recursos reais:**
- ✅ Variáveis
- ✅ Arrays
- ✅ Condicionais
- ✅ REPL
- ✅ Mensagens de erro
- ✅ Sistema de tipos (em breve)

### Simples

**Base de código pequena:**
- ~3.000 linhas de C
- Bem documentado
- Design modular
- Fácil de entender

---

## 🎯 Objetivos do Projeto

### Objetivo Primário: Educação

JECH existe para ensinar como linguagens de programação funcionam. Cada decisão de design prioriza **clareza** sobre **performance**.

### Objetivo Secundário: Inspiração

Mostrar que construir uma linguagem é **alcançável**. Você não precisa de PhD ou 10 anos de experiência em C.

### Não-Objetivo: Uso em Produção

JECH **não** pretende substituir Python, JavaScript ou PHP. É uma ferramenta de aprendizado.

---

## 💖 A História Por Trás do JECH

JECH foi criado como:
1. **Uma jornada de aprendizado** - Entendendo como linguagens funcionam
2. **Uma ferramenta de ensino** - Compartilhando esse conhecimento com outros
3. **Uma homenagem** - Aos meus filhos Jonathan Edwards e Charles Haddon (J-E-C-H)

Foi construído com amor, para aprendizes, por um aprendiz.

---

## 🤝 Contribuindo

Aceitamos contribuições de desenvolvedores de **todos os níveis de experiência**!

### Você Pode Ajudar:

- 📝 Escrevendo programas de exemplo
- 📖 Melhorando documentação
- 🐛 Reportando bugs
- 💡 Sugerindo recursos
- 🧪 Escrevendo testes
- 🌍 Traduzindo docs

**Sem experiência em C necessária!**

Veja [CONTRIBUTING.md](CONTRIBUTING.md) para detalhes.

---

## 📊 Estatísticas do Projeto

- **Linguagem:** C
- **Linhas de Código:** ~3.000
- **Testes:** 70 (100% passando)
- **Documentação:** 6 guias detalhados
- **Exemplos:** 22 programas
- **Contribuidores:** Crescendo!

---

## 🗺️ Roadmap

### ✅ Completo

- [x] Tokenizer
- [x] Parser
- [x] AST
- [x] Compilador de bytecode
- [x] Máquina Virtual
- [x] Variáveis
- [x] Arrays
- [x] Condicionais
- [x] REPL
- [x] Testes abrangentes
- [x] Documentação

### 🚧 Em Progresso

- [ ] Funções
- [ ] Loops
- [ ] Sistema de tipos
- [ ] Biblioteca padrão

### 🔮 Futuro

- [ ] Coleta de lixo
- [ ] Passes de otimização
- [ ] Compilação JIT
- [ ] Gerenciador de pacotes

Veja [roadmap.md](roadmap.md) para detalhes.

---

## 📖 Saiba Mais

### Ordem de Leitura Recomendada

1. **[Para Iniciantes](docs/en/FOR_BEGINNERS.md)** - Comece aqui!
2. **[Arquitetura](docs/en/architecture.md)** - Veja o panorama geral
3. **[Tokenizer](docs/en/tokenizer.md)** - Primeiro estágio
4. **[Parser](docs/en/parser.md)** - Segundo estágio
5. **[VM](docs/en/vm.md)** - Estágio final

### Recursos Externos

- [Crafting Interpreters](https://craftinginterpreters.com/) - Livro excelente
- [CPython Internals](https://realpython.com/cpython-source-code-guide/) - Como Python funciona
- [V8 Blog](https://v8.dev/blog) - Como JavaScript funciona

---

## ⚖️ Licença

JECH é software livre e de código aberto licenciado sob a [Licença Apache 2.0][repo_license_url].

---

## 🙏 Agradecimentos

- **Python** - Por inspiração e padrões de design
- **Crafting Interpreters** - Pela abordagem educacional
- **A comunidade** - Por feedback e contribuições

---

<div align="center">

**Pronto para aprender como linguagens funcionam?**

[Começar](docs/en/FOR_BEGINNERS.md) | [Documentação](docs/en/architecture.md) | [Contribuir](CONTRIBUTING.md)

Feito com ❤️ para desenvolvedores curiosos

</div>

<!-- Links -->
[repo_url]: https://github.com/seuusuario/jech
[repo_logo_img]: images/jc_logo.png
[repo_license_url]: https://github.com/seuusuario/jech/blob/main/LICENSE
[repo_license_img]: https://img.shields.io/badge/license-Apache_2.0-red?style=for-the-badge&logo=none
[repo_wiki_url]: https://github.com/seuusuario/jech/wiki
[repo_wiki_img]: https://img.shields.io/badge/docs-wiki_page-blue?style=for-the-badge&logo=none
