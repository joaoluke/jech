#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

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

Token create_token(TokenType type, const char *value)
{
	Token token;
	token.type = type;
	strncpy(token.value, value, sizeof(token.value) - 1);
	token.value[sizeof(token.value) - 1] = '\0';
	return token;
}

TokenList lex(const char *source)
{
	TokenList list;
	list.count = 0;

	const char *p = source;
	while (*p)
	{
		if (isspace(*p))
		{
			p++;
			continue;
		}

		if (isalpha(*p))
		{
			char word[64];
			int i = 0;
			while (isalnum(*p) && i < 63)
			{
				word[i++] = *p++;
			}
			word[i] = '\0';

			if (strcmp(word, "true") == 0 || strcmp(word, "false") == 0)
			{
				list.tokens[list.count++] = create_token(TOKEN_BOOL, word);
				continue;
			}

			TokenType type = match_keyword(word);
			list.tokens[list.count++] = create_token(type, word);
		}
		else if (isdigit(*p))
		{
			char number[64];
			int i = 0;
			while ((isdigit(*p) || *p == '.') && i < 63) 
			{
				number[i++] = *p++;
			}
			number[i] = '\0';
			list.tokens[list.count++] = create_token(TOKEN_NUMBER, number);
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
			p++;
			char buffer[256];
			int i = 0;
			while (*p && *p != '"' && i < 255)
			{
				buffer[i++] = *p++;
			}
			buffer[i] = '\0';

			if (*p == '"')
			{
				p++;
				list.tokens[list.count++] = create_token(TOKEN_STRING, buffer);
			}
			else
			{
				list.tokens[list.count++] = create_token(TOKEN_UNKNOWN, buffer);
			}
		}
		else
		{
			char unknown[2] = {*p, '\0'};
			list.tokens[list.count++] = create_token(TOKEN_UNKNOWN, unknown);
			p++;
		}
	}

	list.tokens[list.count++] = create_token(TOKEN_EOF, "");
	return list;
}
