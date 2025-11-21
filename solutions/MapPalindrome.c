#include <stdio.h>
#include <stdlib.h>

char* deep_copy(char* src) {
    char* p = src;
    int len = 0;
    while (*p) {
        len++;
        p++;
    }
    
    char* copy = malloc(len + 1);
    if (!copy) return NULL;
    
    char* dest = copy;
    char* source = src;
    while (*source) {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = '\0';
    
    return copy;
}

int is_palindrome(char* word) {
    char* start = word;
    char* end = word;
    
    while (*end) {
        end++;
    }
    end--;
    
    while (start < end) {
        if (*start != *end) {
            return 0;
        }
        start++;
        end--;
    }
    
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    char** keys = malloc((argc - 1) * sizeof(char*));
    if (!keys) {
        exit(2);
    }
    
    int* values = malloc((argc - 1) * sizeof(int));
    if (!values) {
        free(keys);
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        keys[i - 1] = deep_copy(argv[i]);
        if (!keys[i - 1]) {
            for (int j = 0; j < i - 1; j++) {
                free(keys[j]);
            }
            free(keys);
            free(values);
            exit(2);
        }
        values[i - 1] = is_palindrome(keys[i - 1]);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%s %d\n", keys[i], values[i]);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        free(keys[i]);
    }
    free(keys);
    free(values);
    
    return 0;
}