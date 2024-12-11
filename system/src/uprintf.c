#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <system/uprintf.h>

#ifdef __linux__
#include <stdio.h>
#define uart_transmit putchar
#else
#include <system/uart.h>
#endif

#define LEFT_JUSTIFY (1 << 0)
#define FORCE_SIGN (1 << 1)
#define FORCE_SPACE (1 << 2)
#define ZERO_PAD (1 << 3)
#define ALTERNATE_FORM (1 << 4)

#define ENABLE_LONG
#define ENABLE_SHORT

typedef enum {
    INT,      // Integer
    UINT,     // Unsigned integer
    HEX,      // Hexadecimal integer
    OCT,      // Octal integer
    BIN,      // Binary integer
    CHR,      // Char
    STR,      // String
    ADDR,     // Address
    PERCENT,  // Percent symbol
    FLT,      // Floating point number
    UNDEFINED
} specifier_t;

typedef enum {
    SHORT,
    NORMAL,
    LONG,
} length_t;

const static char upper_hex[] = "0123456789ABCDEF";

static int sutos(short unsigned int value, char* str, unsigned int base);
static int utos(unsigned int value, char* str, unsigned int base);
static int lutos(long unsigned int value, char* str, unsigned int base);

static specifier_t _get_specifier(const char** fmt);
static length_t _get_length(const char** fmt);
static int _get_percision(const char** fmt);
static int _get_width(const char** fmt);
static int _get_flags(const char** fmt);
static int _uprintf(const char* fmt, va_list args);
static int _uprint_arg(const char** fmt, va_list args);

static int _uprint_char(char c);
static int _uprint_str(const char* str);
static int _uprint_num(const char* num, int count, int prefix_size, int flags, int width);
static int _uprint_int(int i, int flags, int width, unsigned int base);
static int _uprint_uint(unsigned int u, int flags, int width, unsigned int base);

static int _uprint_short_int(short int i, int flags, int width, unsigned int base);
static int _uprint_short_uint(short unsigned int i, int flags, int width, unsigned int base);

static int _uprint_long_int(long int i, int flags, int width, unsigned int base);
static int _uprint_long_uint(long unsigned int u, int flags, int width, unsigned int base);

static int _uprint_double(double f, int flags, int width, int percision);

int uprintf(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    const int count = _uprintf(fmt, args);
    va_end(args);

    return count;
}

int _uprintf(const char* fmt, va_list args) {
    int count = 0;
    while (*fmt) {
        if (*fmt == '%') {
            ++fmt;
            count += _uprint_arg(&fmt, args);
        } else {
            uart_transmit(*(fmt++));
            ++count;
        }
    }
    return count;
}

int _uprint_arg(const char** fmt, va_list args) {
    const int flags = _get_flags(fmt);
    const int width = _get_width(fmt);
    const int percision = _get_percision(fmt);
    const length_t length = _get_length(fmt);
    const specifier_t specifier = _get_specifier(fmt);

    switch (specifier) {
        case INT: {
            switch (length) {
                case SHORT:
                    return _uprint_short_int(va_arg(args, int), flags, width, 10);
                case NORMAL:
                    return _uprint_int(va_arg(args, int), flags, width, 10);
                case LONG:
                    return _uprint_long_int(va_arg(args, long int), flags, width, 10);
            }
        }
        case UINT: {
            switch (length) {
                case SHORT:
                    return _uprint_short_uint(va_arg(args, unsigned int), flags, width, 10);
                case NORMAL:
                    return _uprint_uint(va_arg(args, unsigned int), flags, width, 10);
                case LONG:
                    return _uprint_long_uint(va_arg(args, long unsigned int), flags, width, 10);
            }
        }
        case HEX: {
            switch (length) {
                case SHORT:
                    return _uprint_short_uint(va_arg(args, unsigned int), flags, width, 16);
                case NORMAL:
                    return _uprint_uint(va_arg(args, unsigned int), flags, width, 16);
                case LONG:
                    return _uprint_long_uint(va_arg(args, long unsigned int), flags, width, 16);
            }
        }
        case OCT: {
            switch (length) {
                case SHORT:
                    return _uprint_short_uint(va_arg(args, unsigned int), flags, width, 8);
                case NORMAL:
                    return _uprint_uint(va_arg(args, unsigned int), flags, width, 8);
                case LONG:
                    return _uprint_long_uint(va_arg(args, long unsigned int), flags, width, 8);
            }
        }
        case BIN: {
            switch (length) {
                case SHORT:
                    return _uprint_short_uint(va_arg(args, unsigned int), flags, width, 2);
                case NORMAL:
                    return _uprint_uint(va_arg(args, unsigned int), flags, width, 2);
                case LONG:
                    return _uprint_long_uint(va_arg(args, long unsigned int), flags, width, 2);
            }
        }
        case CHR:
            return _uprint_char(va_arg(args, int));
        case STR:
            return _uprint_str(va_arg(args, char*));
        case ADDR:
            return _uprint_long_uint((long unsigned int) va_arg(args, void*), flags | ALTERNATE_FORM, width, 16);
        case PERCENT:
            return _uprint_char('%');
        case FLT:
            return _uprint_double(va_arg(args, double), flags, width, percision);
        case UNDEFINED:
            return 0;
    }
}

int _get_flags(const char** fmt) {
    int flags = 0;
    while (**fmt) {
        switch (**fmt) {
            case '-':
                flags |= LEFT_JUSTIFY;
                ++(*fmt);
                break;
            case '+':
                flags |= FORCE_SIGN;
                ++(*fmt);
                break;
            case '#':
                flags |= ALTERNATE_FORM;
                ++(*fmt);
                break;
            case '0':
                flags |= ZERO_PAD;
                ++(*fmt);
                break;
            case ' ':
                flags |= FORCE_SPACE;
                ++(*fmt);
                break;
            default:
                return flags;
        }
    }
    return flags;
}

int _get_width(const char** fmt) {
    int width = 0;
    while (**fmt) {
        if (isdigit(**fmt)) {
            width = width * 10 + (**fmt - '0');
            ++(*fmt);
        } else {
            break;
        }
    }
    return width;
}

int _get_percision(const char** fmt) {
    int percision = 0;

    if (**fmt == '.') {
        ++(*fmt);
    } else {
        return 0;
    }

    while (**fmt) {
        if (isdigit(**fmt)) {
            percision = percision * 10 + (**fmt - '0');
            ++(*fmt);
        } else {
            break;
        }
    }
    return percision;
}

length_t _get_length(const char** fmt) {
    length_t length = NORMAL;
    while (**fmt) {
        switch (**fmt) {
            case 'l':
                length = LONG;
                ++(*fmt);
                break;
            case 'h':
                length = SHORT;
                ++(*fmt);
                break;
            default:
                return length;
        }
    }
    return length;
}

specifier_t _get_specifier(const char** fmt) {
    switch (*((*fmt)++)) {
        case 'u':
            return UINT;
        case 'x':
            return HEX;
        case 'o':
            return OCT;
        case 'b':
            return BIN;
        case 'p':
            return ADDR;
        case 's':
            return STR;
        case '%':
            return PERCENT;
        case 'd':
            return INT;
        case 'c':
            return CHR;
        case 'f':
            return FLT;
        default:
            return UNDEFINED;
    }
}

int _uprint_char(char c) {
    uart_transmit((uint8_t) c);
    return 1;
}

int _uprint_str(const char* str) {
    const char* ptr = str;
    while (*ptr) {
        uart_transmit((uint8_t) * (ptr++));
    }
    return (ptr - str);
}

static int _uprint_num(const char* num, int count, int prefix_size, int flags, int width) {
    const char padding_char = (flags & ZERO_PAD) ? '0' : ' ';
    const int padding_size = (width > count) ? width - count : 0;
    const int left_padding = (flags & LEFT_JUSTIFY) ? 0 : padding_size;
    const int right_padding = (flags & LEFT_JUSTIFY) ? padding_size : 0;

    int printed = 0;

    for (int i = 0; i < prefix_size && (flags & ZERO_PAD); ++i) {
        uart_transmit(num[printed++]);
    }

    for (int i = 0; i < left_padding; ++i) {
        uart_transmit(padding_char);
    }

    for (int i = printed; i < prefix_size; ++i) {
        uart_transmit(num[printed++]);
    }

    for (int i = count - 1; i >= printed; --i) {
        uart_transmit(num[i]);
    }

    for (int i = 0; i < right_padding; ++i) {
        uart_transmit(' ');
    }

    return count + padding_size;
}

int _uprint_int(int i, int flags, int width, unsigned int base) {
    const int size = sizeof(int) * 8 + 4;
    char buffer[size];

    int count = 0;
    if (i < 0) {
        buffer[count++] = '-';
    } else if (flags & FORCE_SIGN) {
        buffer[count++] = '+';
    } else if (flags & FORCE_SPACE) {
        buffer[count++] = ' ';
    }

    const int prefix_size = count;

    count += utos(abs(i), &buffer[count], base);

    return _uprint_num(buffer, count, prefix_size, flags, width);
}

int _uprint_short_int(short int i, int flags, int width, unsigned int base) {
#ifdef ENABLE_SHORT
    const int size = sizeof(short int) * 8 + 4;
    char buffer[size];

    int count = 0;
    if (i < 0) {
        buffer[count++] = '-';
    } else if (flags & FORCE_SIGN) {
        buffer[count++] = '+';
    } else if (flags & FORCE_SPACE) {
        buffer[count++] = ' ';
    }

    const int prefix_size = count;

    count += sutos(labs(i), &buffer[count], base);

    return _uprint_num(buffer, count, prefix_size, flags, width);
#else
    return 0;
#endif
}

int _uprint_long_int(long int i, int flags, int width, unsigned int base) {
#ifdef ENABLE_LONG
    const int size = sizeof(long int) * 8 + 4;
    char buffer[size];

    int count = 0;
    if (i < 0) {
        buffer[count++] = '-';
    } else if (flags & FORCE_SIGN) {
        buffer[count++] = '+';
    } else if (flags & FORCE_SPACE) {
        buffer[count++] = ' ';
    }

    const int prefix_size = count;

    count += lutos(labs(i), &buffer[count], base);

    return _uprint_num(buffer, count, prefix_size, flags, width);
#else
    return 0;
#endif
}

int _uprint_uint(unsigned int u, int flags, int width, unsigned int base) {
    const int size = sizeof(unsigned int) * 8 + 4;
    char buffer[size];

    int count = 0;
    if (flags & FORCE_SIGN) {
        buffer[count++] = '+';
    } else if ((flags & ALTERNATE_FORM) && base == 16) {
        buffer[count++] = '0';
        buffer[count++] = 'x';
    } else if ((flags & ALTERNATE_FORM) && base == 8) {
        buffer[count++] = '0';
    }

    const int prefix_size = count;

    count += utos(u, &buffer[count], base);

    return _uprint_num(buffer, count, prefix_size, flags, width);
}

int _uprint_short_uint(short unsigned int u, int flags, int width, unsigned int base) {
#ifdef ENABLE_SHORT
    const int size = sizeof(short unsigned int) * 8 + 4;
    char buffer[size];

    int count = 0;
    if (flags & FORCE_SIGN) {
        buffer[count++] = '+';
    } else if ((flags & ALTERNATE_FORM) && base == 16) {
        buffer[count++] = '0';
        buffer[count++] = 'x';
    } else if ((flags & ALTERNATE_FORM) && base == 8) {
        buffer[count++] = '0';
    }

    const int prefix_size = count;

    count += sutos(u, &buffer[count], base);

    return _uprint_num(buffer, count, prefix_size, flags, width);
#else
    return 0;
#endif
}

int _uprint_long_uint(long unsigned int u, int flags, int width, unsigned int base) {
#ifdef ENABLE_LONG
    const int size = sizeof(long unsigned int) * 8 + 4;
    char buffer[size];

    int count = 0;
    if (flags & FORCE_SIGN) {
        buffer[count++] = '+';
    } else if ((flags & ALTERNATE_FORM) && base == 16) {
        buffer[count++] = '0';
        buffer[count++] = 'x';
    } else if ((flags & ALTERNATE_FORM) && base == 8) {
        buffer[count++] = '0';
    }

    const int prefix_size = count;

    count += lutos(u, &buffer[count], base);

    return _uprint_num(buffer, count, prefix_size, flags, width);
#else
    return 0;
#endif
}

int _uprint_double(double d, int flags, int width, int percision) {
#ifdef ENABLE_FLOAT
#error FLOAT IS NOT YET SUPPORTED
    return 0;
#else
    return 0;
#endif
}

int utos(unsigned int value, char* str, unsigned int base) {
    char* ptr = str;

    do {
        *(ptr++) = upper_hex[value % base];
        value /= base;
    } while (value > 0);
    *ptr = '\0';

    return (ptr - str);
}

int sutos(short unsigned int value, char* str, unsigned int base) {
    char* ptr = str;

    do {
        *(ptr++) = upper_hex[value % base];
        value /= base;
    } while (value > 0);
    *ptr = '\0';

    return (ptr - str);
}

int lutos(long unsigned int value, char* str, unsigned int base) {
    char* ptr = str;

    do {
        *(ptr++) = upper_hex[value % base];
        value /= base;
    } while (value > 0);
    *ptr = '\0';

    return (ptr - str);
}
