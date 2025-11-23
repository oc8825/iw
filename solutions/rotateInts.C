#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int parse_non_negative_int(const char* str) {
    if (str == NULL || *str == '\0') return -1;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return -1;
    }
    
    errno = 0;
    char* endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || val < 0 || val > INT_MAX) return -1;
    
    return (int)val;
}

int parse_int(const char* str) {
    if (str == NULL || *str == '\0') return 0;
    
    int start = 0;
    if (str[0] == '-') start = 1;
    
    if (str[start] == '\0') return 0;
    
    for (int i = start; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    
    errno = 0;
    char* endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) return 0;
    
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    if (argc == 2) {
        return 0;
    }
    
    int n = parse_non_negative_int(argv[1]);
    if (n == -1) {
        printf("Error: n must be a non-negative integer.\n");
        return 1;
    }
    
    int list_size = argc - 2;
    int* list = (int*)malloc(list_size * sizeof(int));
    if (list == NULL) {
        return 2;
    }
    
    for (int i = 0; i < list_size; i++) {
        if (!parse_int(argv[i + 2])) {
            printf("Error: all list elements must be valid integers.\n");
            free(list);
            return 1;
        }
        list[i] = atoi(argv[i + 2]);
    }
    
    if (list_size == 0) {
        free(list);
        return 0;
    }
    
    int effective_rotation = n % list_size;
    
    for (int i = 0; i < list_size; i++) {
        int original_index = (i - effective_rotation + list_size) % list_size;
        printf("%d", list[original_index]);
        if (i < list_size - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(list);
    return 0;
}