#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char value[256];
} Variable;

#define MAX_VARIABLES 100
Variable variables[MAX_VARIABLES];
int var_count = 0;

void set_variable(const char* name, const char* value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            strncpy(variables[i].value, value, sizeof(variables[i].value));
            return;
        }
    }
    strncpy(variables[var_count].name, name, sizeof(variables[var_count].name));
    strncpy(variables[var_count].value, value, sizeof(variables[var_count].value));
    var_count++;
}

const char* get_variable(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    return NULL;
}

void remove_quotes(char* str) {
    size_t len = strlen(str);
    if (str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

void interpret_line(char* line) {
    if (strncmp(line, "keep", 4) == 0) {
        char name[50], value[256];
        if (sscanf(line, "keep %49[^=]= %255[^;];", name, value) == 2) {
            char* trimmed_name = strtok(name, " \t");
            remove_quotes(value);
            set_variable(trimmed_name, value);
        }
    } else if (strncmp(line, "say", 3) == 0) {
        char arg[256];
        if (sscanf(line, "say(%255[^)]);", arg) == 1) {
            remove_quotes(arg);
            const char* value = get_variable(arg);
            if (value) {
                printf("%s\n", value);
            } else {
                printf("%s\n", arg);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file.jc>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        interpret_line(line);
    }

    fclose(file);
    return 0;
}
