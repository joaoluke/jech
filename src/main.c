#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "core/pipeline.h"
#include "core/repl.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		run_repl();
		return 0;
	}

	const char *filename = argv[1];

	if (!is_valid_extension(filename))
	{
		printf("Error: file must have .jc extension.\n");
		return 1;
	}

	char *source = load_source_file(filename);

	run_pipeline(source);

	free(source);
	return 0;
}
