#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "core/lexer.h"

// JECH Language Keyword Mapping
typedef struct
{
	const char *keyword;
	TokenType type;
} KeywordMap;

KeywordMap keywords[] = {
	{"say", TOKEN_SAY},
	{"keep", TOKEN_KEEP},
	{"when", TOKEN_WHEN},
	{NULL, TOKEN_UNKNOWN}};

// Checks if a word matches a language keyword
TokenType match_keyword(const char *word)
{
	for (int i = 0; keywords[i].keyword != NULL; i++)
	{
		if (strcmp(word, keywords[i].keyword) == 0)
		{
			return keywords[i].type;
		}
	}
	return TOKEN_IDENTIFIER;
}

// Creates a token with defined type and value
Token create_token(TokenType type, const char *value)
{
	Token token;
	token.type = type;
	strncpy(token.value, value, sizeof(token.value) - 1);
	token.value[sizeof(token.value) - 1] = '\0';
	return token;
}

// Skip whitespace and comments
static void skip_whitespace_and_comments(const char **p)
{
	while (**p)
	{
		if (isspace(**p))
		{
			(*p)++;
		}
		else if (**p == '#' || (**p == '/' && *(*p + 1) == '/'))
		{
			while (**p && **p != '\n')
				(*p)++;
		}
		else
		{
			break;
		}
	}
}

// Reads words or booleans (true/false) and returns a token
static Token read_word(const char **p)
{
	char word[64];
	int i = 0;
	while (isalnum(**p) && i < 63)
	{
		word[i++] = *(*p)++;
	}
	word[i] = '\0';

	if (strcmp(word, "true") == 0 || strcmp(word, "false") == 0)
	{
		return create_token(TOKEN_BOOL, word);
	}

	TokenType type = match_keyword(word);
	return create_token(type, word);
}

// Reads numbers (integers or floats)
static Token read_number(const char **p)
{
	char number[64];
	int i = 0;
	while ((isdigit(**p) || **p == '.') && i < 63)
	{
		number[i++] = *(*p)++;
	}
	number[i] = '\0';
	return create_token(TOKEN_NUMBER, number);
}

// Reads quoted strings
static Token read_string(const char **p)
{
	(*p)++; // Skip the first quote
	char buffer[256];
	int i = 0;
	while (**p && **p != '"' && i < 255)
	{
		buffer[i++] = *(*p)++;
	}
	buffer[i] = '\0';

	if (**p == '"')
	{
		(*p)++;
		return create_token(TOKEN_STRING, buffer);
	}
	else
	{
		fprintf(stderr, "Lexer error: Unterminated string literal → \"%s\"\n", buffer);
		exit(1);
	}
}

// Parses the source code and returns the list of tokens
TokenList lex(const char *source)
{
	TokenList list;
	list.count = 0;

	const char *p = source;

	while (*p)
	{
		skip_whitespace_and_comments(&p);

		if (isalpha(*p))
		{
			list.tokens[list.count++] = read_word(&p);
		}
		else if (isdigit(*p))
		{
			list.tokens[list.count++] = read_number(&p);
		}
		else if (*p == '=')
		{
			list.tokens[list.count++] = create_token(TOKEN_EQUAL, "=");
			p++;
		}
		else if (*p == '(')
		{
			list.tokens[list.count++] = create_token(TOKEN_LPAREN, "(");
			p++;
		}
		else if (*p == ')')
		{
			list.tokens[list.count++] = create_token(TOKEN_RPAREN, ")");
			p++;
		}
		else if (*p == ';')
		{
			list.tokens[list.count++] = create_token(TOKEN_SEMICOLON, ";");
			p++;
		}
		else if (*p == '"')
		{
			list.tokens[list.count++] = read_string(&p);
		}
		else if (*p != '\0')
		{
			char unknown[2] = {*p, '\0'};
			list.tokens[list.count++] = create_token(TOKEN_UNKNOWN, unknown);
			fprintf(stderr, "Lexer error: unknown character '%c'\n", *p);
			p++;
		}
	}

	list.tokens[list.count++] = create_token(TOKEN_EOF, "");
	return list;
}
