#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int is_valid_integer(const char *str, int *value) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    char *endptr;
    errno = 0;
    long result = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || result < INT_MIN || result > INT_MAX) {
        return 0;
    }
    
    if (*endptr != '\0') {
        return 0;
    }
    
    if (endptr == str) {
        return 0;
    }
    
    const char *p = str;
    if (*p == '+' || *p == '-') {
        p++;
    }
    
    if (*p == '\0') {
        return 0;
    }
    
    while (*p) {
        if (*p < '0' || *p > '9') {
            return 0;
        }
        p++;
    }
    
    *value = (int)result;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    int n = argc - 1;
    int *input = (int*)malloc(n * sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));
    
    if (input == NULL || output == NULL) {
        exit(2);
    }
    
    for (int i = 0; i < n; i++) {
        if (!is_valid_integer(argv[i + 1], &input[i])) {
            printf("Error: invalid integer argument.\n");
            free(input);
            free(output);
            return 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        output[i] = 1;
    }
    
    int prefix = 1;
    for (int i = 0; i < n; i++) {
        output[i] = prefix;
        prefix *= input[i];
    }
    
    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        output[i] *= suffix;
        suffix *= input[i];
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d", output[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(input);
    free(output);
    return 0;
}