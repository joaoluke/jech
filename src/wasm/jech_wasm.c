#include <emscripten.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "core/pipeline.h"
#include "core/vm.h"
#include "core/tokenizer.h"
#include "core/parser/parser.h"
#include "core/bytecode.h"
#include "core/ast.h"

#define OUTPUT_BUFFER_SIZE 16384

static char output_buffer[OUTPUT_BUFFER_SIZE];
static int output_pos = 0;

/**
 * Função para adicionar texto ao buffer de saída
 * Esta será chamada pelo JavaScript via EM_JS
 */
EMSCRIPTEN_KEEPALIVE
void append_output(const char* text) {
    int len = strlen(text);
    int remaining = OUTPUT_BUFFER_SIZE - output_pos - 1;
    int to_copy = (len < remaining) ? len : remaining;
    
    if (to_copy > 0) {
        memcpy(output_buffer + output_pos, text, to_copy);
        output_pos += to_copy;
        output_buffer[output_pos] = '\0';
    }
}

/**
 * Obter o buffer de saída atual
 */
EMSCRIPTEN_KEEPALIVE
const char* get_output() {
    return output_buffer;
}

/**
 * Execute Jech code and return the output
 * This is the main entry point called from JavaScript
 */
EMSCRIPTEN_KEEPALIVE
const char* jech_execute(const char *source) {
    // Clear output buffer
    output_pos = 0;
    memset(output_buffer, 0, OUTPUT_BUFFER_SIZE);
    
    if (!source || strlen(source) == 0) {
        strcpy(output_buffer, "Error: Empty source code");
        return output_buffer;
    }
    
    // Tokenize
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    if (tokens.count == 0 || (tokens.count == 1 && tokens.tokens[0].type == TOKEN_EOF)) {
        strcpy(output_buffer, "");
        return output_buffer;
    }
    
    // Parse
    int ast_count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &ast_count);
    
    if (ast_count == 0) {
        strcpy(output_buffer, "Error: Failed to parse code");
        return output_buffer;
    }
    
    // Compile to bytecode
    Bytecode bytecode = _JechBytecode_CompileAll(roots, ast_count);
    
    // Execute
    _JechVM_Execute(&bytecode);
    
    // Cleanup
    for (int i = 0; i < ast_count; i++) {
        _JechAST_Free(roots[i]);
    }
    
    return output_buffer;
}

/**
 * Clear all VM state (variables, arrays, functions)
 */
EMSCRIPTEN_KEEPALIVE
void jech_clear() {
    _JechVM_ClearState();
    output_pos = 0;
    memset(output_buffer, 0, OUTPUT_BUFFER_SIZE);
}

/**
 * Get the current Jech version
 */
EMSCRIPTEN_KEEPALIVE
const char* jech_version() {
    return "0.1.0";
}
