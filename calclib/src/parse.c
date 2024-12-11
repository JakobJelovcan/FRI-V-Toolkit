#include <calclib/parse.h>

int parser_errno = 0;

static int32_t parse_additive_expression(token_t* tokens[]);
static int32_t parse_additive_expression_2(token_t* tokens[], int32_t left_side);
static int32_t parse_multiplicative_expression(token_t* tokens[]);
static int32_t parse_multiplicative_expression_2(token_t* tokens[], int32_t left_side);
static int32_t parse_prefix_expression(token_t* tokens[]);
static int32_t parse_atomic_expression(token_t* tokens[]);
static int32_t parse_constant_expression(token_t* tokens[]);

static int32_t parse_constant_expression(token_t* tokens[]) {
    const token_t* token = (*tokens)++;
    int32_t result = 0;
    for (int i = 0; i < token->size; ++i)
        result = result * 10 + (token->ptr[i] - 48);

    return result;
}

static int32_t parse_atomic_expression(token_t* tokens[]) {
    const token_t* token = *tokens;

    switch (token->type) {
        case TOK_NUM: {
            const int32_t result = parse_constant_expression(tokens);
            return result;
        }
        case TOK_LPR: {
            (*tokens)++;
            const int32_t result = parse_additive_expression(tokens);
            token = (*tokens)++;
            if (token->type != TOK_RPR)
                parser_errno = PARSER_UNEXPECTED_TOKEN;
            return result;
        }
        default: {
            parser_errno = PARSER_OUT_OF_TOKENS;
            return 1;
        }
    }
}

static int32_t parse_prefix_expression(token_t* tokens[]) {
    const token_t* token = *tokens;

    switch (token->type) {
        case TOK_ADD:
            (*tokens)++;
            return parse_atomic_expression(tokens);
        case TOK_SUB: {
            (*tokens)++;
            return -parse_atomic_expression(tokens);
        }
        case TOK_LPR:
        case TOK_NUM: {
            return parse_atomic_expression(tokens);
        }
        default: {
            parser_errno = PARSER_UNEXPECTED_TOKEN;
            return 1;
        }
    }
}

static int32_t parse_multiplicative_expression(token_t* tokens[]) {
    const token_t* token = *tokens;

    switch (token->type) {
        case TOK_ADD:
        case TOK_SUB:
        case TOK_NUM: {
            const int32_t result = parse_prefix_expression(tokens);
            return parse_multiplicative_expression_2(tokens, result);
        }
        case TOK_LPR: {
            return parse_atomic_expression(tokens);
        }
        default: {
            parser_errno = PARSER_UNEXPECTED_TOKEN;
            return 1;
        }
    }
}

static int32_t parse_multiplicative_expression_2(token_t* tokens[], int32_t left_side) {
    const token_t* token = *tokens;

    switch (token->type) {
        case TOK_MUL: {
            (*tokens)++;
            const int32_t result = left_side * parse_prefix_expression(tokens);
            return parse_multiplicative_expression_2(tokens, result);
        }
        case TOK_DIV: {
            (*tokens)++;
            const int32_t result = left_side / parse_prefix_expression(tokens);
            return parse_multiplicative_expression_2(tokens, result);
        }
        case TOK_REM: {
            (*tokens)++;
            const int32_t result = left_side % parse_prefix_expression(tokens);
            return parse_multiplicative_expression_2(tokens, result);
        }
        default:
            return left_side;
    }
}

static int32_t parse_additive_expression(token_t* tokens[]) {
    token_t* token = *tokens;

    switch (token->type) {
        case TOK_ADD:
        case TOK_SUB:
        case TOK_NUM:
        case TOK_LPR: {
            const int32_t result = parse_multiplicative_expression(tokens);
            return parse_additive_expression_2(tokens, result);
        }
        default: {
            parser_errno = PARSER_UNEXPECTED_TOKEN;
            return 1;
        }
    }
}

static int32_t parse_additive_expression_2(token_t* tokens[], int32_t left_side) {
    const token_t* token = *tokens;

    switch (token->type) {
        case TOK_ADD: {
            (*tokens)++;
            const int32_t result = left_side + parse_multiplicative_expression(tokens);
            return parse_additive_expression_2(tokens, result);
        }
        case TOK_SUB: {
            (*tokens)++;
            const int32_t result = left_side - parse_multiplicative_expression(tokens);
            return parse_additive_expression_2(tokens, result);
        }
        default:
            return left_side;
    }
}

int32_t evaluate(token_t tokens[]) {
    parser_errno = 0;
    return parse_additive_expression(&tokens);
}
