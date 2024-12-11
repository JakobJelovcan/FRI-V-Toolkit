#include <calclib/lex.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum { LEX_WHITE, LEX_NUM, LEX_OP } lexer_state_t;

static bool is_operator(char chr) {
    switch (chr) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}

static bool is_number(char chr) {
    return chr >= 48 && chr <= 57;
}

static bool is_whitespace(char chr) {
    switch (chr) {
        case ' ':
        case '\n':
        case '\t':
            return true;
        default:
            return false;
    }
}

token_type_t get_operator_token_type(char chr) {
    switch (chr) {
        case '+':
            return TOK_ADD;
        case '-':
            return TOK_SUB;
        case '*':
            return TOK_MUL;
        case '/':
            return TOK_DIV;
        case '%':
            return TOK_REM;
        case '(':
            return TOK_LPR;
        case ')':
            return TOK_RPR;
        default:
            return TOK_ERR;
    }
}

int32_t scan(const char* str, token_t tokens[], uint16_t max_tokens) {
    lexer_state_t state = LEX_WHITE;
    const char* token_ptr = str;
    uint16_t token_index = 0;
    uint16_t token_size = 0;

    do {
        if (token_index == max_tokens - 1)
            return LEX_OUT_OF_SPACE;

        switch (state) {
            case LEX_WHITE: {
                token_ptr = str;
                token_size = 0;

                if (is_number(*str))
                    state = LEX_NUM;
                else if (is_operator(*str))
                    state = LEX_OP;
                else if (is_whitespace(*str))
                    ++str;
                else
                    return LEX_INVALID_TOKEN;

                break;
            }
            case LEX_NUM: {
                if (!is_number(*str)) {
                    // clang-format off
                    const token_t token = {
                        .type = TOK_NUM,
                        .ptr  = token_ptr,
                        .size = token_size
                    };
                    // clang-format on
                    tokens[token_index++] = token;
                    state = LEX_WHITE;
                } else {
                    ++token_size;
                    ++str;
                }

                break;
            }
            case LEX_OP: {
                // clang-format off
                const token_t token = {
                    .type = get_operator_token_type(*token_ptr),
                    .ptr  = token_ptr,
                    .size = 1
                };
                // clang-format on
                tokens[token_index++] = token;
                state = LEX_WHITE;

                ++token_size;
                ++str;

                break;
            }
        }
    } while (*str || state != LEX_WHITE);

    // clang-format off
    const token_t token = {
        .type = TOK_EOF,
        .ptr = NULL,
        .size = 0
    };
    // clang-format on
    tokens[token_index] = token;

    return token_index;
}
