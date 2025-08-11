// #include "nostdlib/stdint.h"
#include "stdlib/stdio.h"
#include "nostdlib/stdbool.h"
#include "vga/vga.h"

void putc(char c) {
    print_char(c);
}

void puts(const char* str) {
    print_str(str);
}

void printf(const char* format, ...) {
    int* argp = (int*) &format;
    int state = PRINTF_STATE_START;
    int length = PRINTF_LENGTH_START;
    int radix = 10;
    bool sign = false;

    argp++; // Skip the format string pointer

    while (*format) {
        switch (state) {
            case PRINTF_STATE_START:
                if (*format == '%') {
                    state = PRINTF_STATE_LENGTH;
                } else {
                    putc(*format);
                }
                // format++;
                break;

            case PRINTF_STATE_LENGTH:
                if (*format == 'h') {
                    length = PRINTF_LENGTH_SHORT;
                    state = PRINTF_STATE_SHORT;
                } else if (*format == 'l') {
                    length = PRINTF_LENGTH_LONG;
                    state = PRINTF_STATE_LONG;
                } else {
                    goto PRINTF_STATE_SPEC_;
                }
                // format++;
                break;

            // hd
            case PRINTF_STATE_SHORT:
                if (*format == 'h') {
                    length = PRINTF_LENGTH_SHORT_SHORT;
                    state = PRINTF_STATE_SPEC;
                } else {
                    goto PRINTF_STATE_SPEC_;
                }
                // format++;
                break;

            case PRINTF_STATE_LONG:
                if (*format == 'l') {
                    length = PRINTF_LENGTH_LONG_LONG;
                    state = PRINTF_STATE_SPEC;
                } else {
                    goto PRINTF_STATE_SPEC_;
                }
                // format++;
                break;

            case PRINTF_STATE_SPEC:
                PRINTF_STATE_SPEC_:
                switch (*format) {
                    case 'c':
                        putc((char)*argp);
                        argp++;
                        break;
                    case 's':
                        if (length == PRINTF_LENGTH_LONG || 
                            length == PRINTF_LENGTH_LONG_LONG) 
                        {
                                puts(*(const char **)argp);
                                argp += 2; // Skip the pointer
                        } else {
                            puts(*(const char **)argp);
                            argp++;
                        }
                        break;
                    case '%':
                        putc('%');
                        break;
                    case 'd':
                    case 'i':
                        radix = 10;
                        sign = true;
                        argp = printf_number(argp, length, sign, radix);
                        break;
                    case 'u':
                        radix = 10;
                        sign = false;
                        argp = printf_number(argp, length, sign, radix);
                        break;
                    case 'X':
                    case 'x':
                    case 'p':
                        radix = 16;
                        sign = false;
                        argp = printf_number(argp, length, sign, radix);
                        break;
                    case 'b':
                        radix = 2;
                        sign = false;
                        argp = printf_number(argp, length, sign, radix);
                        break;
                    case 'o':
                        radix = 8;
                        sign = false;
                        argp = printf_number(argp, length, sign, radix);
                        break;
                    default:
                        break;
                }
            state = PRINTF_STATE_START;
            length = PRINTF_LENGTH_START;
            radix = 10;
            sign = false;
            break;
        }
        format++;
    }
}

const char possibleCharacters[] = "0123456789abcdef";

int * printf_number(int *argp, int length, bool sign, int radix) {
    char buffer[32] = "";
    uint32_t number;
    int number_sign = 1;
    int pos = 0;

    switch (length) {
        case PRINTF_LENGTH_SHORT_SHORT:
        case PRINTF_LENGTH_SHORT:
        case PRINTF_LENGTH_START:
            if (sign) {
                int n = *argp;
                if (n < 0) {
                    n = -n;
                    number_sign = -1;
                }
                number = (uint32_t) n;
            } else {
                number = *(uint32_t*) argp;
            }
            argp++;
            break;
        case PRINTF_LENGTH_LONG:
            if (sign) {
                long int n = *(long int*)argp;
                if (n < 0) {
                    n = -n;
                    number_sign = -1;
                }
                number = (uint32_t) n;
            } else {
                number = *(uint32_t*) argp;
            }
            argp += 2;
            break;
        case PRINTF_LENGTH_LONG_LONG:
            if (sign) {
                long long int n = *(long long int*) argp;
                if (n < 0) {
                    n = -n;
                    number_sign = -1;
                }
                number = (uint32_t) n;
            } else {
                number = *(uint32_t*) argp;
            }
            argp += 4;
            break;
    }

    do {
        uint32_t rem = number % radix;
        number = number / radix;

        buffer[pos++] = possibleCharacters[rem];
    } while (number > 0);

    if (sign && number_sign < 0) {
        buffer[pos++] = '-';
    }

    while (--pos >= 0) {
        putc(buffer[pos]);
    }

    return argp;
}