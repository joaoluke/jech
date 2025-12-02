# 🔍 Tokenizador (Análise Léxica)

## O que é um Tokenizador?

O **tokenizador** (também chamado de **lexer**) é a primeira etapa de qualquer compilador ou interpretador. Seu trabalho é ler o código fonte bruto e quebrá-lo em pedaços significativos chamados **tokens**.

Pense nisso como ler uma frase: antes de entender a gramática, você precisa identificar palavras individuais e sinais de pontuação.

### Exemplo

```jc
keep idade = 25;
```

O tokenizador converte isso em:

```text
TOKEN_KEEP       → "keep"
TOKEN_IDENTIFIER → "idade"
TOKEN_EQUALS     → "="
TOKEN_NUMBER     → "25"
TOKEN_SEMICOLON  → ";"
```

Cada token tem um **tipo** (que tipo de elemento é) e um **valor** (o texto real).

---

## 📄 Implementação no JECH

### Estrutura do Arquivo

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "core/tokenizer.h"
```

Bibliotecas padrão do C para manipulação de strings, classificação de caracteres e alocação de memória.

---

## 🔤 Tipos de Token

O JECH reconhece estes tipos de token:

### Palavras-chave
| Token | Palavra-chave | Descrição |
|-------|---------------|-----------|
| `TOKEN_SAY` | `say` | Comando de saída |
| `TOKEN_KEEP` | `keep` | Declaração de variável |
| `TOKEN_WHEN` | `when` | Declaração condicional |
| `TOKEN_ELSE` | `else` | Bloco alternativo |

### Literais
| Token | Exemplo | Descrição |
|-------|---------|-----------|
| `TOKEN_STRING` | `"olá"` | Texto entre aspas |
| `TOKEN_NUMBER` | `42`, `3.14` | Inteiro ou float |
| `TOKEN_BOOL` | `true`, `false` | Valores booleanos |
| `TOKEN_IDENTIFIER` | `minhaVar` | Nomes de variáveis |

### Operadores e Símbolos
| Token | Símbolo | Descrição |
|-------|---------|-----------|
| `TOKEN_EQUALS` | `=` | Atribuição |
| `TOKEN_EQEQ` | `==` | Comparação de igualdade |
| `TOKEN_GT` | `>` | Maior que |
| `TOKEN_LT` | `<` | Menor que |
| `TOKEN_LPAREN` | `(` | Parêntese esquerdo |
| `TOKEN_RPAREN` | `)` | Parêntese direito |
| `TOKEN_LBRACE` | `{` | Chave esquerda |
| `TOKEN_RBRACE` | `}` | Chave direita |
| `TOKEN_SEMICOLON` | `;` | Terminador de declaração |

---

## 🔧 Mapeamento de Palavras-chave

```c
typedef struct {
    const char *keyword;
    JechTokenType type;
} KeywordMap;

KeywordMap keywords[] = {
    {"say", TOKEN_SAY},
    {"keep", TOKEN_KEEP},
    {"when", TOKEN_WHEN},
    {"else", TOKEN_ELSE},
    {NULL, TOKEN_UNKNOWN}
};
```

Esta tabela mapeia strings de palavras-chave para seus tipos de token. Quando o tokenizador lê uma palavra, ele verifica esta tabela para determinar se é uma palavra-chave ou um identificador regular.

---

## 🧠 Funções Principais

### `match_keyword`

```c
JechTokenType match_keyword(const char *word)
```

Verifica se uma palavra é uma palavra-chave reconhecida. Retorna o tipo de token correspondente, ou `TOKEN_IDENTIFIER` se não for uma palavra-chave.

**Como funciona:**
```c
// Itera pela tabela de palavras-chave
for (int i = 0; keywords[i].keyword != NULL; i++) {
    if (strcmp(word, keywords[i].keyword) == 0) {
        return keywords[i].type;  // Encontrou uma palavra-chave!
    }
}
return TOKEN_IDENTIFIER;  // Não é palavra-chave, deve ser nome de variável
```

---

### `create_token`

```c
JechToken create_token(JechTokenType type, const char *value)
```

Função fábrica que cria um novo token com o tipo e valor fornecidos. Também rastreia números de linha e coluna para relatório de erros.

---

## 🔧 Funções de Leitura

### Ignorando Espaços em Branco e Comentários

```c
static void skip_whitespace_and_comments(const char **p)
```

Avança o ponteiro do fonte além de:
- Espaços, tabs, quebras de linha
- Comentários de linha única (`//` ou `#`)

Isso garante que o tokenizador processe apenas caracteres significativos.

---

### `read_word`

```c
static JechToken read_word(const char **p)
```

Lê sequências alfabéticas que podem ser:
- **Palavras-chave**: `say`, `keep`, `when`, `else`
- **Booleanos**: `true`, `false`
- **Identificadores**: nomes de variáveis como `minhaVar`, `idade`

---

### `read_number`

```c
static JechToken read_number(const char **p)
```

Lê literais numéricos:
- **Inteiros**: `42`, `100`
- **Floats**: `3.14`, `0.5`

---

### `read_string`

```c
static JechToken read_string(const char **p)
```

Lê literais de string entre aspas duplas: `"Olá, Mundo!"`

Se a aspa de fechamento estiver faltando, reporta um erro "String não terminada".

---

## 🎯 Ponto de Entrada Principal

```c
JechTokenList _JechTokenizer_Lex(const char *source)
```

Esta é a **API pública** do tokenizador. Ela orquestra toda a análise léxica:

1. **Inicializa** uma lista de tokens vazia
2. **Itera** pelo código fonte caractere por caractere
3. **Despacha** para o leitor apropriado baseado no caractere atual:
   - Letra → `read_word()`
   - Dígito → `read_number()`
   - Aspas → `read_string()`
   - Símbolo → cria token de símbolo diretamente
4. **Adiciona** `TOKEN_EOF` para marcar o fim
5. **Retorna** a lista completa de tokens

### Exemplo de Walkthrough

Entrada:
```jc
when (idade > 18) { say("adulto"); }
```

Tokens de saída:
```text
[0] TOKEN_WHEN       "when"
[1] TOKEN_LPAREN     "("
[2] TOKEN_IDENTIFIER "idade"
[3] TOKEN_GT         ">"
[4] TOKEN_NUMBER     "18"
[5] TOKEN_RPAREN     ")"
[6] TOKEN_LBRACE     "{"
[7] TOKEN_SAY        "say"
[8] TOKEN_LPAREN     "("
[9] TOKEN_STRING     "adulto"
[10] TOKEN_RPAREN    ")"
[11] TOKEN_SEMICOLON ";"
[12] TOKEN_RBRACE    "}"
[13] TOKEN_EOF
```

---

## 💡 Conceitos-Chave para Aprendizes

1. **Tokens são os átomos da sua linguagem** — tudo começa aqui
2. **Ordem importa** — verifique `==` antes de `=` para evitar confusões
3. **Rastreie posição** — info de linha/coluna é crucial para mensagens de erro úteis
4. **Falhe cedo** — reporte erros assim que detectá-los

---
