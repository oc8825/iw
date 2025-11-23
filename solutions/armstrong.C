#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int is_valid_natural(const char *str) {
    if (!str || *str == '\0') return 0;
    if (*str == '+' || *str == '-') return 0;
    
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int count_digits(unsigned long long n) {
    if (n == 0) return 1;
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

unsigned long long power(int base, int exp) {
    unsigned long long result = 1;
    for (int i = 0; i < exp; i++) {
        if (result > ULLONG_MAX / base) return ULLONG_MAX;
        result *= base;
    }
    return result;
}

int is_armstrong(unsigned long long n) {
    int digits = count_digits(n);
    unsigned long long sum = 0;
    unsigned long long temp = n;
    
    while (temp > 0) {
        int digit = temp % 10;
        unsigned long long digit_power = power(digit, digits);
        if (digit_power == ULLONG_MAX) return -1;
        if (sum > ULLONG_MAX - digit_power) return -1;
        sum += digit_power;
        temp /= 10;
    }
    
    return (sum == n) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    if (argc > 2) {
        fprintf(stderr, "Error: expected one argument\n");
        return 1;
    }
    
    if (!is_valid_natural(argv[1])) {
        fprintf(stderr, "Error: invalid number\n");
        return 1;
    }
    
    char *endptr;
    unsigned long long n = strtoull(argv[1], &endptr, 10);
    
    if (*endptr != '\0') {
        fprintf(stderr, "Error: invalid number\n");
        return 1;
    }
    
    int result = is_armstrong(n);
    if (result == -1) {
        return 2;
    }
    
    printf("%s\n", result ? "true" : "false");
    return 0;
}