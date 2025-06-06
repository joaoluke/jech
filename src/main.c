#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils/main_helpers.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <file.jc>\n", argv[0]);
		return 1;
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
