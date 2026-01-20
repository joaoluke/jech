#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
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
	printf("  numbers.map(* 2);         - Transform array\n");
	printf("\n");
}

static bool is_command(const char *input, const char *cmd)
{
	size_t len = strlen(cmd);
	return strncmp(input, cmd, len) == 0 && 
	       (input[len] == '\0' || input[len] == '\n');
}


void run_repl()
{
	print_welcome();
	
	// Initialize readline history
	using_history();

	while (true)
	{
		// readline handles the prompt and returns allocated string
		char *input = readline(">>> ");
		
		// EOF or error (Ctrl+D)
		if (!input)
		{
			printf("\n");
			break;
		}

		// Skip empty lines
		if (strlen(input) == 0)
		{
			free(input);
			continue;
		}

		// Add non-empty input to history
		add_history(input);

		if (is_command(input, "exit") || is_command(input, "quit"))
		{
			printf("Goodbye!\n");
			free(input);
			break;
		}

		if (is_command(input, "help"))
		{
			print_help();
			free(input);
			continue;
		}

		if (is_command(input, "clear"))
		{
			_JechVM_ClearState();
			printf("All variables and arrays cleared.\n");
			free(input);
			continue;
		}

		JechTokenList tokens = _JechTokenizer_Lex(input);
		
		if (tokens.count == 0 || (tokens.count == 1 && tokens.tokens[0].type == TOKEN_EOF))
		{
			free(input);
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

		// Free the input allocated by readline
		free(input);
	}
}
