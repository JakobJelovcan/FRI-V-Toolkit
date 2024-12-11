#pragma once
#include <inttypes.h>

#define LEX_INVALID_TOKEN -1
#define LEX_OUT_OF_SPACE -2

typedef enum {
    TOK_NUM,  // Number
    TOK_ADD,  // +
    TOK_SUB,  // -
    TOK_MUL,  // *
    TOK_DIV,  // /
    TOK_REM,  // %
    TOK_LPR,  // (
    TOK_RPR,  // )
    TOK_EOF,  // End of file
    TOK_ERR   // Invalid token
} token_type_t;

typedef struct {
    token_type_t type;
    const char* ptr;
    uint16_t size;
} token_t;

int32_t scan(const char* str, token_t tokens[], uint16_t size);
