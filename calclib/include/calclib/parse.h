#pragma once
#include <calclib/lex.h>

#define PARSER_OUT_OF_TOKENS -1
#define PARSER_UNEXPECTED_TOKEN -2

extern int parser_errno;

int32_t evaluate(token_t tokens[]);