#include <emscripten.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define OUTPUT_BUFFER_SIZE 16384

static char output_buffer[OUTPUT_BUFFER_SIZE];
static int output_pos = 0;

/**
 * Custom printf that writes to our buffer instead of stdout
 * This will be used by overriding printf in the VM code
 */
int jech_wasm_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int remaining = OUTPUT_BUFFER_SIZE - output_pos - 1;
    if (remaining > 0) {
        int written = vsnprintf(output_buffer + output_pos, remaining, format, args);
        if (written > 0 && written < remaining) {
            output_pos += written;
        }
    }
    
    va_end(args);
    return 0;
}

// Override printf and fprintf for WASM
#define printf jech_wasm_printf
#define fprintf(stream, ...) jech_wasm_printf(__VA_ARGS__)

// Now include the Jech headers after defining the overrides
#include "core/pipeline.h"
#include "core/vm.h"
#include "core/tokenizer.h"
#include "core/parser/parser.h"
#include "core/bytecode.h"
#include "core/ast.h"

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
