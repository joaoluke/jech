#ifndef LEXER_H
#define LEXER_H

typedef enum {
    // Keywords
    TOKEN_SAY,
    TOKEN_KEEP,
    TOKEN_WHEN,

    // Symbols
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_STRING,
    TOKEN_SEMICOLON,

    // Others
    TOKEN_IDENTIFIER, // for names that are not reserved commands
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[256];
} Token;

typedef struct {
    Token tokens[128];
    int count;
} TokenList;

TokenList lex(const char *source);

#endif
