#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// JECH Language Headers
#include "jech.h"
#include "core/lexer.h"
#include "core/parser.h"
#include "core/bytecode.h"
#include "core/vm.h"
#include "utils.h"
#include "errors.h"
#include "commands/say.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <file.jc>\n", argv[0]);
		return 1;
	}

	const char *filename = argv[1];
	int len = strlen(filename);
	if (len < 4 || strcmp(&filename[len - 3], ".jc") != 0)
	{
		printf("Error: file must have .jc extension.\n");
		return 1;
	}

	char *source = read_file_content(filename);
	if (!source)
	{
		printf("Could not read file: %s\n", filename);
		return 1;
	}

	TokenList tokens = lex(source);

	check_lexical_errors(&tokens, source);

	ASTList ast = parse_all(&tokens);
	if (ast.count == 0)
	{
		printf("Parser error: No valid instructions found\n");
	}
	else
	{
		Bytecode bc = compile_all(ast);
		execute(bc);
	}

	free(source);
	return 0;
}