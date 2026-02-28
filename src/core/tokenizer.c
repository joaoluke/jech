#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "core/tokenizer.h"
#include "errors/error.h"

static int push_token(JechTokenList *list, JechToken token)
{
	if (list->count >= JECH_MAX_TOKENS - 1)
	{
		report_error(SYNTAX_ERROR, "Too many tokens", token.line, token.column);
		return 0;
	}

	list->tokens[list->count++] = token;
	return 1;
}

/**
 * JECH Language Keyword Mapping
 */
typedef struct
{
	const char *keyword;
	JechTokenType type;
} KeywordMap;

KeywordMap keywords[] = {
	{"say", TOKEN_SAY},
	{"keep", TOKEN_KEEP},
	{"when", TOKEN_WHEN},
	{"else", TOKEN_ELSE},
	{"map", TOKEN_MAP},
	{"do", TOKEN_DO},
	{"return", TOKEN_RETURN},
	{NULL, TOKEN_UNKNOWN}};

/**
 * Checks if a word matches a language keyword
 */
JechTokenType match_keyword(const char *word)
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

/**
 * Creates a token with defined type and value
 */
JechToken create_token(JechTokenType type, const char *value, int line, int column)
{
	JechToken token;
	token.type = type;
	strncpy(token.value, value, sizeof(token.value) - 1);
	token.value[sizeof(token.value) - 1] = '\0';
	token.line = line;
	token.column = column;
	return token;
}

/**
 * Skip whitespace and comments
 */
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

/**
 * Reads words or booleans (true/false) and returns a token
 */
static JechToken read_word(const char **p, int *line, int *col, int token_col)
{
	char word[64];
	int i = 0;
	while (isalnum(**p) && i < 63)
	{
		word[i++] = *(*p)++;
		(*col)++;
	}
	word[i] = '\0';

	if (strcmp(word, "true") == 0 || strcmp(word, "false") == 0)
	{
		return create_token(TOKEN_BOOL, word, *line, token_col);
	}

	JechTokenType type = match_keyword(word);
	return create_token(type, word, *line, token_col);
}

/**
 * Reads numbers (integers or floats)
 */
static JechToken read_number(const char **p, int *line, int *col, int start_col)
{
	char number[64];
	int i = 0;
	while ((isdigit(**p) || **p == '.') && i < 63)
	{
		number[i++] = *(*p)++;
		(*col)++;
	}
	number[i] = '\0';
	return create_token(TOKEN_NUMBER, number, *line, start_col);
}

/**
 * Reads quoted strings
 */
static JechToken read_string(const char **p, int *line, int *col, int start_col)
{
	(*p)++; // Skip opening quote
	(*col)++;
	char buffer[256];
	int i = 0;

	while (**p && **p != '"' && i < 255)
	{
		if (**p == '\n')
		{
			(*line)++;
			*col = 1;
		}
		else
		{
			(*col)++;
		}
		buffer[i++] = *(*p)++;
	}
	buffer[i] = '\0';

	if (**p == '"')
	{
		(*p)++;
		(*col)++;
		return create_token(TOKEN_STRING, buffer, *line, start_col);
	}
	else
	{
		report_error(SYNTAX_ERROR, "Unterminated string literal", *line, start_col);
		exit(1);
	}
}

/**
 * Parses the source code and returns the list of tokens
 */
JechTokenList _JechTokenizer_Lex(const char *source)
{
	JechTokenList list;
	list.count = 0;

	const char *p = source;
	int line = 1;
	int col = 1;

	while (*p)
	{
		skip_whitespace_and_comments(&p);
		int token_col = col;

		if (isalpha(*p))
		{
			if (!push_token(&list, read_word(&p, &line, &col, token_col)))
				break;
		}
		else if (isdigit(*p))
		{
			if (!push_token(&list, read_number(&p, &line, &col, token_col)))
				break;
		}
		else if (*p == '+')
		{
			if (!push_token(&list, create_token(TOKEN_PLUS, "+", line, col)))
				break;
			p++;
		}
		else if (*p == '-')
		{
			if (!push_token(&list, create_token(TOKEN_MINUS, "-", line, col)))
				break;
			p++;
		}
		else if (*p == '*')
		{
			if (!push_token(&list, create_token(TOKEN_STAR, "*", line, col)))
				break;
			p++;
		}
		else if (*p == '/')
		{
			if (*(p + 1) == '/')
			{
				while (*p && *p != '\n')
				{
					p++;
				}
			}
			else
			{
				if (!push_token(&list, create_token(TOKEN_SLASH, "/", line, col)))
					break;
				p++;
			}
		}
		else if (*p == '=' && *(p + 1) == '=')
		{
			if (!push_token(&list, create_token(TOKEN_EQEQ, "==", line, col)))
				break;
			p += 2;
		}
		else if (*p == '=')
		{
			if (!push_token(&list, create_token(TOKEN_EQUAL, "=", line, col)))
				break;
			p++;
		}
		else if (*p == '>')
		{
			if (!push_token(&list, create_token(TOKEN_GT, ">", line, col)))
				break;
			p++;
		}
		else if (*p == '<')
		{
			if (!push_token(&list, create_token(TOKEN_LT, "<", line, col)))
				break;
			p++;
		}
		else if (*p == '(')
		{
			if (!push_token(&list, create_token(TOKEN_LPAREN, "(", line, col)))
				break;
			p++;
		}
		else if (*p == ')')
		{
			if (!push_token(&list, create_token(TOKEN_RPAREN, ")", line, col)))
				break;
			p++;
		}
		else if (*p == '[')
		{
			if (!push_token(&list, create_token(TOKEN_LBRACKET, "[", line, col)))
				break;
			p++;
		}
		else if (*p == ']')
		{
			if (!push_token(&list, create_token(TOKEN_RBRACKET, "]", line, col)))
				break;
			p++;
		}
		else if (*p == ',')
		{
			if (!push_token(&list, create_token(TOKEN_COMMA, ",", line, col)))
				break;
			p++;
		}
		else if (*p == '.')
		{
			if (!push_token(&list, create_token(TOKEN_DOT, ".", line, col)))
				break;
			p++;
		}
		else if (*p == ';')
		{
			if (!push_token(&list, create_token(TOKEN_SEMICOLON, ";", line, col)))
				break;
			p++;
		}
		else if (*p == '"')
		{
			if (!push_token(&list, read_string(&p, &line, &col, token_col)))
				break;
		}
		else if (*p == '{')
		{
			if (!push_token(&list, create_token(TOKEN_LBRACE, "{", line, col)))
				break;
			p++;
		}
		else if (*p == '}')
		{
			if (!push_token(&list, create_token(TOKEN_RBRACE, "}", line, col)))
				break;
			p++;
		}

		else if (*p != '\0')
		{
			char unknown[2] = {*p, '\0'};
			if (!push_token(&list, create_token(TOKEN_UNKNOWN, unknown, line, col)))
				break;

			char msg[64];
			snprintf(msg, sizeof(msg), "Unknown character '%c'", *p);
			report_syntax_error(msg, line, col);

			p++;
		}
	}

	push_token(&list, create_token(TOKEN_EOF, "", line, col));
	return list;
}
