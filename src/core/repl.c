#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "core/repl.h"
#include "core/pipeline.h"
#include "core/tokenizer.h"
#include "core/parser/parser.h"
#include "core/bytecode.h"
#include "core/vm.h"
#include "core/ast.h"

#define MAX_INPUT 1024
#define JECH_VERSION "0.1.0"

static void print_welcome()
{
	printf("Jech Interactive Shell v%s\n", JECH_VERSION);
	printf("Type 'exit' or 'quit' to leave, 'help' for help, 'clear' to clear variables\n");
	printf(">>> ");
	fflush(stdout);
}

static void print_help()
{
	printf("\nJech REPL Commands:\n");
	printf("  exit, quit  - Exit the REPL\n");
	printf("  help        - Show this help message\n");
	printf("  clear       - Clear all variables and arrays\n");
	printf("\nJech Syntax:\n");
	printf("  keep x = 10;              - Declare variable\n");
	printf("  x = 20;                   - Assign to variable\n");
	printf("  say(x);                   - Print value\n");
	printf("  keep arr = [1, 2, 3];     - Declare array\n");
	printf("  say(arr[0]);              - Print array element\n");
	printf("  when (x > 5) { say(x); }  - Conditional\n");
	printf("\n>>> ");
	fflush(stdout);
}

static bool is_command(const char *input, const char *cmd)
{
	size_t len = strlen(cmd);
	return strncmp(input, cmd, len) == 0 && 
	       (input[len] == '\0' || input[len] == '\n');
}

static void trim_newline(char *str)
{
	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}

void run_repl()
{
	char input[MAX_INPUT];
	print_welcome();

	while (true)
	{
		if (!fgets(input, MAX_INPUT, stdin))
		{
			printf("\n");
			break;
		}

		trim_newline(input);

		if (strlen(input) == 0)
		{
			printf(">>> ");
			fflush(stdout);
			continue;
		}

		if (is_command(input, "exit") || is_command(input, "quit"))
		{
			printf("Goodbye!\n");
			break;
		}

		if (is_command(input, "help"))
		{
			print_help();
			continue;
		}

		if (is_command(input, "clear"))
		{
			_JechVM_ClearState();
			printf("All variables and arrays cleared.\n>>> ");
			fflush(stdout);
			continue;
		}

		JechTokenList tokens = _JechTokenizer_Lex(input);
		
		if (tokens.count == 0 || (tokens.count == 1 && tokens.tokens[0].type == TOKEN_EOF))
		{
			printf(">>> ");
			fflush(stdout);
			continue;
		}

		int ast_count = 0;
		JechASTNode **roots = _JechParser_ParseAll(&tokens, &ast_count);

		if (ast_count > 0)
		{
			Bytecode bytecode = _JechBytecode_CompileAll(roots, ast_count);
			_JechVM_Execute(&bytecode);

			for (int i = 0; i < ast_count; i++)
			{
				_JechAST_Free(roots[i]);
			}
		}

		printf(">>> ");
		fflush(stdout);
	}
}
