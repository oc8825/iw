#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int is_valid_integer(const char *str) {
    if (!str || *str == '\0') {
        return 0;
    }
    
    int i = 0;
    if (str[0] == '-') {
        if (str[1] == '\0') {
            return 0;
        }
        i = 1;
    }
    
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i++;
    }
    
    return 1;
}

long parse_integer(const char *str) {
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0') {
        return LONG_MIN;
    }
    return val;
}

long max(long a, long b) {
    return a > b ? a : b;
}

long rob_linear(long *houses, int n) {
    if (n == 0) return 0;
    if (n == 1) return houses[0];
    
    long prev2 = 0;
    long prev1 = houses[0];
    
    for (int i = 1; i < n; i++) {
        long current = max(prev1, prev2 + houses[i]);
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

long rob_circular(long *houses, int n) {
    if (n == 0) return 0;
    if (n == 1) return houses[0];
    if (n == 2) return max(houses[0], houses[1]);
    
    return max(rob_linear(houses, n - 1), rob_linear(houses + 1, n - 1));
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    long *houses = (long *)malloc((argc - 1) * sizeof(long));
    if (!houses) {
        return 2;
    }
    
    for (int i = 1; i < argc; i++) {
        if (!is_valid_integer(argv[i])) {
            fprintf(stderr, "Error: non-integer argument\n");
            free(houses);
            return 1;
        }
        
        long val = parse_integer(argv[i]);
        if (val == LONG_MIN) {
            fprintf(stderr, "Error: non-integer argument\n");
            free(houses);
            return 1;
        }
        
        if (val < 0) {
            fprintf(stderr, "Error: negative integer argument\n");
            free(houses);
            return 1;
        }
        
        houses[i - 1] = val;
    }
    
    long result = rob_circular(houses, argc - 1);
    printf("%ld\n", result);
    
    free(houses);
    return 0;
}