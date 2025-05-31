#include <stdio.h>
#include <string.h>
#include "say.h"

#define MAX_STRING 256

void remove_quotes(char *str)
{
    size_t len = strlen(str);
    if (str[0] == '"' && str[len - 1] == '"')
    {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

int count_char(const char *str, char target)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == target)
            count++;
    }
    return count;
}

void execute_say(const char *line)
{
    int aspas = count_char(line, '"');
    if (aspas != 2)
    {
        printf("Error: invalid string. Use only one pair of double quotes.\n");
        return;
    }

    char text[MAX_STRING];
    if (sscanf(line, "say(\"%255[^\"]\");", text) == 1)
    {
        if (strlen(text) >= MAX_STRING - 1)
        {
            printf("Error: string exceeds max length of %d characters\n", MAX_STRING - 1);
            return;
        }

        printf("%s\n", text);
    }
    else
    {
        if (strstr(line, "say("))
        {
            printf("Error: could not process say command. Possibly too long.\n");
        }
        else
        {
            printf("Syntax error in say command.\n");
        }
    }
}
