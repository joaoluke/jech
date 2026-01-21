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

#define MAX_INPUT 4096
#define JECH_VERSION "0.1.0"

static void print_welcome()
{
	printf("Jech Interactive Shell v%s\n", JECH_VERSION);
	printf("Type 'exit' or 'quit' to leave, 'help' for help, 'clear' to clear variables\n");
	printf("Multi-line input: The REPL automatically detects incomplete statements (unclosed braces)\n");
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
	printf("\nMulti-line Support:\n");
	printf("  The REPL automatically continues to the next line when it detects\n");
	printf("  unclosed braces or parentheses. Example:\n");
	printf("  >>> do greet(name) {\n");
	printf("  ...   say(name);\n");
	printf("  ... }\n");
	printf("\n");
}

static bool is_command(const char *input, const char *cmd)
{
	size_t len = strlen(cmd);
	return strncmp(input, cmd, len) == 0 && 
	       (input[len] == '\0' || input[len] == '\n');
}

/**
 * Check if the input has unclosed braces, indicating an incomplete statement
 */
static bool has_unclosed_braces(const char *input)
{
	int brace_count = 0;
	int paren_count = 0;
	bool in_string = false;
	
	for (const char *p = input; *p; p++)
	{
		if (*p == '"' && (p == input || *(p-1) != '\\'))
		{
			in_string = !in_string;
		}
		else if (!in_string)
		{
			if (*p == '{') brace_count++;
			else if (*p == '}') brace_count--;
			else if (*p == '(') paren_count++;
			else if (*p == ')') paren_count--;
		}
	}
	
	return brace_count > 0 || paren_count > 0;
}


void run_repl()
{
	print_welcome();
	
	// Initialize readline history
	using_history();

	while (true)
	{
		// Buffer for multi-line input
		char buffer[MAX_INPUT] = {0};
		
		// Read first line
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

		// Copy first line to buffer
		strncpy(buffer, input, MAX_INPUT - 1);
		free(input);
		
		// Check if we need more lines (unclosed braces)
		while (has_unclosed_braces(buffer))
		{
			char *continuation = readline("... ");
			
			if (!continuation)
			{
				printf("\n");
				break;
			}
			
			// Append continuation line with newline
			size_t current_len = strlen(buffer);
			if (current_len + strlen(continuation) + 2 < MAX_INPUT)
			{
				strcat(buffer, "\n");
				strcat(buffer, continuation);
			}
			free(continuation);
		}
		
		// Add complete multi-line input to history
		if (strlen(buffer) > 0)
		{
			add_history(buffer);
		}

		if (is_command(buffer, "exit") || is_command(buffer, "quit"))
		{
			printf("Goodbye!\n");
			break;
		}

		if (is_command(buffer, "help"))
		{
			print_help();
			continue;
		}

		if (is_command(buffer, "clear"))
		{
			_JechVM_ClearState();
			printf("All variables and arrays cleared.\n");
			continue;
		}

		JechTokenList tokens = _JechTokenizer_Lex(buffer);
		
		if (tokens.count == 0 || (tokens.count == 1 && tokens.tokens[0].type == TOKEN_EOF))
		{
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
	}
}
