### 🔍 Visão Geral

O **tokenizer** (ou **lexer**) é responsável por transformar o texto-fonte em **tokens** — blocos categorizados que representam palavras-chave, símbolos, números, strings, etc.

---

### 📄 Estrutura Geral do `tokenizer.c`

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "core/tokenizer.h"
```

Importação das bibliotecas padrão do C e do cabeçalho da linguagem JECH.

---

### 🔤 Tabela de Palavras-Chave

```c
typedef struct {
	const char *keyword;
	JechTokenType type;
} KeywordMap;

KeywordMap keywords[] = {
	{"say", TOKEN_SAY},
	{"keep", TOKEN_KEEP},
	{"when", TOKEN_WHEN},
	{NULL, TOKEN_UNKNOWN}
};
```

Aqui definimos o **mapeamento entre strings e seus tipos de token**. Isso permite que `say`, por exemplo, seja interpretado como um token do tipo `TOKEN_SAY`.

---

### 🧠 Funções Auxiliares

#### 🔍 `match_keyword`

```c
JechTokenType match_keyword(const char *word)
```

Verifica se a palavra lida é uma palavra-chave reconhecida. Se sim, retorna o tipo correspondente. Caso contrário, assume que é um identificador (`TOKEN_IDENTIFIER`).

---

#### 🧱 `create_token`

```c
JechToken create_token(JechTokenType type, const char *value)
```

Cria um novo token com tipo e valor. É usado em praticamente todas as funções de leitura (strings, números, símbolos...).

---

### 🔧 Lendo o Código-Fonte

#### Ignorando espaços e comentários

```c
static void skip_whitespace_and_comments(const char **p)
```

Avança o ponteiro `p` ignorando:

* espaços em branco
* comentários começando com `#` ou `//`

---

#### 🧾 `read_word`

```c
static JechToken read_word(const char **p)
```

Lê uma palavra que pode ser:

* uma palavra-chave (`say`, `keep`, etc.)
* um booleano (`true`, `false`)
* um identificador genérico

---

#### 🔢 `read_number`

```c
static JechToken read_number(const char **p)
```

Lê números inteiros ou de ponto flutuante, como `42` ou `3.14`.

---

#### 📝 `read_string`

```c
static JechToken read_string(const char **p)
```

Lê strings entre aspas (`"algo"`). Se não encontrar a aspa final, lança um erro.

---

### 🎯 Função Principal

```c
JechTokenList _JechTokenizer_Lex(const char *source)
```

Esta é a **função pública principal do lexer**. Ela:

1. Cria a lista de tokens.
2. Lê o código caractere por caractere.
3. Chama a função de leitura apropriada:
* `read_word`, `read_number`, `read_string`, etc.
4. Adiciona um `TOKEN_EOF` ao final.

---
