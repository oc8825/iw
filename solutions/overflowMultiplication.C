#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_valid_integer(const char *str) {
    if (*str == '+' || *str == '-') str++;
    if (*str == '\0') return 0;
    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        str++;
    }
    return 1;
}

long long parse_integer(const char *str) {
    long long result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    while (*str) {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

int main(int argc, char *argv[]) {
    if (argc == 1) return 0;

    long long product = 1;
    for (int i = 1; i < argc; i++) {
        if (!is_valid_integer(argv[i])) {
            printf("invalid integer\n");
            return 2;
        }
        long long num = parse_integer(argv[i]);
        if (num > 0) {
            if (product > LLONG_MAX / num) {
                printf("overflow\n");
                return 1;
            }
        } else if (num < 0) {
            if (product < LLONG_MIN / num) {
                printf("overflow\n");
                return 1;
            }
        }
        product *= num;
    }

    printf("%lld\n", product);
    return 0;
}