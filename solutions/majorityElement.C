#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int is_valid_integer(const char *str) {
    if (!str || *str == '\0') return 0;
    
    int i = 0;
    if (str[0] == '-') {
        if (str[1] == '\0') return 0;
        i = 1;
    }
    
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') return 0;
        i++;
    }
    
    return 1;
}

long parse_integer(const char *str) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || *endptr != '\0') {
        return LONG_MIN;
    }
    
    return val;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("-1\n");
        return 0;
    }
    
    int count = argc - 1;
    long *numbers = (long*)malloc(count * sizeof(long));
    if (!numbers) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        if (!is_valid_integer(argv[i])) {
            fprintf(stderr, "Error: invalid number\n");
            free(numbers);
            exit(1);
        }
        
        long val = parse_integer(argv[i]);
        if (val == LONG_MIN && errno == ERANGE) {
            fprintf(stderr, "Error: invalid number\n");
            free(numbers);
            exit(1);
        }
        
        numbers[i - 1] = val;
    }
    
    long majority = -1;
    int majority_count = 0;
    
    for (int i = 0; i < count; i++) {
        int current_count = 0;
        for (int j = 0; j < count; j++) {
            if (numbers[j] == numbers[i]) {
                current_count++;
            }
        }
        
        if (current_count > count / 2 && current_count > majority_count) {
            majority = numbers[i];
            majority_count = current_count;
        }
    }
    
    if (majority_count > count / 2) {
        printf("%ld\n", majority);
    } else {
        printf("-1\n");
    }
    
    free(numbers);
    return 0;
}