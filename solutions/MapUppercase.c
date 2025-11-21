#include <stdio.h>
#include <stdlib.h>

int string_length(char *str) {
    char *ptr = str;
    int len = 0;
    while (*ptr != '\0') {
        len++;
        ptr++;
    }
    return len;
}

char *deep_copy_string(char *src) {
    int len = string_length(src);
    char *dest = malloc((len + 1) * sizeof(char));
    if (dest == NULL) {
        return NULL;
    }
    
    char *src_ptr = src;
    char *dest_ptr = dest;
    
    while (*src_ptr != '\0') {
        *dest_ptr = *src_ptr;
        src_ptr++;
        dest_ptr++;
    }
    *dest_ptr = '\0';
    
    return dest;
}

int count_uppercase(char *str) {
    char *ptr = str;
    int count = 0;
    
    while (*ptr != '\0') {
        if (*ptr >= 'A' && *ptr <= 'Z') {
            count++;
        }
        ptr++;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    int num_words = argc - 1;
    
    char **keys = malloc(num_words * sizeof(char *));
    if (keys == NULL) {
        exit(2);
    }
    
    int *counts = malloc(num_words * sizeof(int));
    if (counts == NULL) {
        free(keys);
        exit(2);
    }
    
    for (int i = 0; i < num_words; i++) {
        keys[i] = deep_copy_string(argv[i + 1]);
        if (keys[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            free(counts);
            exit(2);
        }
        
        counts[i] = count_uppercase(keys[i]);
    }
    
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", keys[i], counts[i]);
    }
    
    for (int i = 0; i < num_words; i++) {
        free(keys[i]);
    }
    free(keys);
    free(counts);
    
    return 0;
}