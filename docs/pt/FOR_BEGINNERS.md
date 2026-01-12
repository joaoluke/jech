# 🎓 JECH para Desenvolvedores de Alto Nível

**Bem-vindo!** Se você é um desenvolvedor Python, JavaScript ou PHP curioso sobre como linguagens de programação realmente funcionam, você está no lugar certo.

## 🤔 "Nunca toquei em C ou compiladores. Ainda posso entender isso?"

**Com certeza!** Este guia foi escrito especificamente para você. Usaremos analogias de linguagens que você já conhece.

---

## 🌟 O Panorama Geral: Como o Código Realmente Executa?

### Em Python/JavaScript/PHP (O que você conhece)

```python
# Python
print("Olá")
```

Você escreve isso, aperta executar, e funciona. **Mas o que acontece nos bastidores?**

### A Mágica Revelada

Seu código passa por uma **pipeline** (como uma linha de montagem de fábrica):

```
Seu Código → Tokenizer → Parser → Compilador → Execução
   📝          🔤          🧱        🔧           ⚡
```

**Pense nisso como cozinhar:**
1. **Receita (Seu Código)**: "say('Olá')"
2. **Lendo ingredientes (Tokenizer)**: Identificar "say", "(", "Olá", ")", ";"
3. **Entendendo passos (Parser)**: "Ah, isso é um comando de impressão com uma string"
4. **Preparando (Compilador)**: Converter para instruções amigáveis à máquina
5. **Cozinhando (Execução)**: Realmente executar!

---

## 📚 Capítulo 1: O Tokenizer (Quebrando Código em Pedaços)

### O que é?

**Em termos Python:** Lembra como o Python sabe que `print("olá")` tem um nome de função, parênteses e uma string? O tokenizer faz isso!

**Analogia do mundo real:** Como ler uma frase e identificar: verbo, substantivo, pontuação.

### Exemplo

**Seu código:**
```jc
say("Olá, Mundo!");
```

**O que o tokenizer vê:**
```
1. "say"     → PALAVRA-CHAVE (como 'print' no Python)
2. "("       → PARÊNTESE DE ABERTURA
3. "Olá, Mundo!" → STRING (texto entre aspas)
4. ")"       → PARÊNTESE DE FECHAMENTO  
5. ";"       → PONTO E VÍRGULA (fim da instrução)
```

### Por que isso é necessário?

Computadores não entendem texto. O tokenizer converte seu código em **pedaços rotulados** que o próximo estágio pode processar.

**Equivalente JavaScript:**
```javascript
// Quando você escreve isso:
console.log("Oi");

// JavaScript internamente quebra em:
// - Identificador: "console"
// - Ponto: "."
// - Identificador: "log"
// - Parêntese: "("
// - String: "Oi"
// - Parêntese: ")"
// - Ponto e vírgula: ";"
```

---

## 📚 Capítulo 2: O Parser (Entendendo Significado)

### O que é?

**Em termos Python:** O parser é como o Python verificando se sua indentação está correta e se instruções `if` têm dois pontos.

**Analogia do mundo real:** Um verificador gramatical que garante que sua frase faz sentido.

### Exemplo

**Tokens do passo anterior:**
```
say ( "Olá" ) ;
```

**O que o parser faz:**
```
✓ Verifica: "say" é seguido por "("
✓ Verifica: Dentro dos parênteses há um valor válido
✓ Verifica: Instrução termina com ";"
✓ Cria: Um nó de "instrução SAY"
```

### Por que isso é necessário?

Só porque você tem palavras válidas não significa que elas formam uma frase válida!

**Exemplos inválidos:**
```jc
say "Olá";     // ✗ Faltando parênteses
say("Olá"      // ✗ Faltando ) de fechamento
say()Olá";     // ✗ Ordem sem sentido
```

O parser captura esses erros e te diz **exatamente** o que está errado.

---

## 📚 Capítulo 3: A AST (Árvore de Sintaxe Abstrata)

### O que é?

**Em termos Python:** Quando o Python lê `if x > 5: print(x)`, ele cria um modelo mental: "SE condição ENTÃO ação". Isso é uma AST!

**Analogia do mundo real:** Uma árvore genealógica, mas para seu código.

### Exemplo

**Seu código:**
```jc
keep x = 10;
when (x > 5) {
    say(x);
}
```

**A AST (estrutura em árvore):**
```
Programa
├── KEEP
│   ├── nome: "x"
│   └── valor: 10
└── WHEN
    ├── condição: (x > 5)
    └── corpo: SAY(x)
```

### Por que isso é necessário?

Árvores facilitam:
- **Entender relacionamentos**: "Este `say` está DENTRO do bloco `when`"
- **Transformar código**: Otimizar, compilar, analisar
- **Executar em ordem**: Caminhar pela árvore de cima para baixo

**Equivalente JavaScript:**
```javascript
// Quando você escreve:
if (x > 5) {
    console.log(x);
}

// JavaScript cria uma árvore similar internamente:
// IfStatement
//   ├── test: BinaryExpression (x > 5)
//   └── consequent: CallExpression (console.log)
```

---

## 📚 Capítulo 4: O Bytecode (Instruções Simplificadas)

### O que é?

**Em termos Python:** Python compila seu código para arquivos `.pyc` (bytecode). JECH faz o mesmo!

**Analogia do mundo real:** Como traduzir uma receita do português para uma lista numerada de passos.

### Exemplo

**Seu código:**
```jc
keep x = 10;
say(x);
```

**Bytecode (instruções simplificadas):**
```
[0] OP_KEEP    nome="x"  valor=10
[1] OP_SAY     operando="x"
[2] OP_END
```

### Por que isso é necessário?

Bytecode é:
- **Mais rápido de executar** do que analisar texto toda vez
- **Portável** (pode ser salvo e executado depois)
- **Otimizável** (pode ser melhorado antes de executar)

**Comparação com Python:**
```python
# Seu código Python
x = 10
print(x)

# É compilado para bytecode (você pode ver com dis.dis()):
# LOAD_CONST    10
# STORE_NAME    x
# LOAD_NAME     x
# PRINT_ITEM
```

---

## 📚 Capítulo 5: A Máquina Virtual (Realmente Executando Código)

### O que é?

**Em termos Python:** A VM do Python (CPython) lê bytecode e o executa. JECH tem sua própria mini-VM!

**Analogia do mundo real:** Um chef seguindo os passos numerados da receita.

### Exemplo

**Bytecode:**
```
[0] OP_KEEP    nome="x"  valor=10
[1] OP_SAY     operando="x"
```

**O que a VM faz:**
```
Passo 0: OP_KEEP
  → Criar variável "x"
  → Armazenar valor 10
  → Tabela de variáveis: { x: 10 }

Passo 1: OP_SAY
  → Procurar "x" na tabela de variáveis
  → Encontrado: 10
  → Imprimir na tela: "10"
```

### Por que isso é necessário?

A VM é o **executor real**. Tudo antes disso foi preparação!

---

## 🎯 Juntando Tudo

### A Jornada Completa

```jc
say("Olá!");
```

**Passo a passo:**

1. **Tokenizer** quebra em pedaços:
   ```
   [say] [(] ["Olá!"] [)] [;]
   ```

2. **Parser** entende o padrão:
   ```
   "Isso é um comando SAY com um argumento string"
   ```

3. **AST** cria um nó de árvore:
   ```
   SAY_NODE { valor: "Olá!" }
   ```

4. **Bytecode** gera instruções:
   ```
   OP_SAY operando="Olá!"
   ```

5. **VM** executa:
   ```
   Imprimir "Olá!" na tela
   ```

**Saída:** `Olá!`

---

## 💡 Conceitos-Chave Explicados Simplesmente

### Compilação vs Interpretação

**Compilado (como C):**
```
Código → Compilador → Código de Máquina → Executar
(Acontece uma vez)    (Rápido!)
```

**Interpretado (como Python):**
```
Código → Interpretador → Executar
(Acontece toda vez) (Flexível!)
```

**JECH (híbrido, como Python):**
```
Código → Tokenizer → Parser → Bytecode → VM
       (Compilar uma vez)         (Executar rápido!)
```

### Por que C?

**P:** "Por que JECH é escrito em C se eu não sei C?"

**R:** C é como a "linguagem assembly das linguagens de alto nível":
- Python (CPython) é escrito em C
- JavaScript (V8) é escrito em C++
- PHP é escrito em C

Aprender como JECH funciona te ensina como **suas linguagens favoritas** funcionam internamente!

### Tipagem Estática vs Dinâmica

**Python (dinâmica):**
```python
x = 10      # x é um número
x = "oi"    # agora x é uma string - sem problema!
```

**JECH (atualmente simples):**
```jc
keep x = 10;
x = "oi";    // Isso também funciona! (por enquanto)
```

JECH foi projetado para ser **simples primeiro**, depois podemos adicionar complexidade.

---

## 🚀 Próximos Passos

Agora que você entende os conceitos, mergulhe nos docs detalhados:

1. **[Mergulho Profundo no Tokenizer](architecture/tokenizer.md)** - Veja código C real com explicações
2. **[Mergulho Profundo no Parser](architecture/parser.md)** - Aprenda correspondência de padrões
3. **[Mergulho Profundo na VM](architecture/vm.md)** - Entenda execução

### Experimente Você Mesmo!

```bash
# Instalar JECH
git clone <repo>
cd jech
make

# Executar o REPL (como o modo interativo do Python)
./build/jech

# Experimente algum código!
>>> keep x = 10;
>>> say(x);
10
>>> keep arr = [1, 2, 3];
>>> say(arr[0]);
1
```

---

## 🤝 Perguntas Comuns

### "Preciso aprender C para entender JECH?"

**Não!** Os conceitos são agnósticos de linguagem. Explicamos tudo em termos que você já conhece.

### "É assim que Python/JavaScript realmente funcionam?"

**Sim!** Os princípios são idênticos. Python usa:
- Tokenizer (lexer)
- Parser (gera AST)
- Compilador (gera bytecode)
- VM (CPython executa bytecode)

### "Posso contribuir sem saber C?"

**Com certeza!** Você pode:
- Escrever programas de exemplo
- Melhorar documentação
- Reportar bugs
- Sugerir recursos
- Escrever testes

### "E se eu quiser aprender C?"

Ótimo! JECH é um **excelente** projeto de aprendizado de C porque:
- Base de código pequena (fácil de ler)
- Bem documentado
- Aplicação prática
- Estrutura modular

---

## 📖 Glossário para Desenvolvedores de Alto Nível

| Termo | Equivalente Python | Explicação Simples |
|------|-------------------|-------------------|
| **Token** | Unidade léxica | Um pedaço rotulado de código (palavra-chave, número, string) |
| **AST** | Resultado de `ast.parse()` | Representação em árvore do seu código |
| **Bytecode** | Conteúdo de arquivo `.pyc` | Instruções simplificadas para a VM |
| **VM** | Interpretador CPython | A coisa que realmente executa seu código |
| **Lexer** | Tokenizer | Quebra código em pedaços |
| **Parser** | Verificador de sintaxe | Valida estrutura do código |
| **Compilador** | `compile()` | Converte código para bytecode |
| **Interpretador** | comando `python` | Executa código diretamente |

---

## 🎓 Caminho de Aprendizado

**Nível 1: Entender os conceitos** (Você está aqui!)
- Ler este guia
- Experimentar o REPL
- Executar exemplos

**Nível 2: Ver em ação**
- Ler [Visão Geral da Arquitetura](architecture/architecture.md)
- Seguir exemplos de código
- Rastrear execução

**Nível 3: Entender implementação**
- Ler docs de componentes (tokenizer, parser, VM)
- Olhar código C real
- Entender estruturas de dados

**Nível 4: Contribuir**
- Escrever testes
- Adicionar recursos
- Melhorar docs
- Ajudar outros

---

**Lembre-se:** Todo especialista já foi iniciante. O criador do Python não sabia tudo quando começou. Nem os criadores do JavaScript ou PHP. Você está aprendendo os mesmos fundamentos que eles usaram!

**Bem-vindo ao mundo do design de linguagens!** 🚀
