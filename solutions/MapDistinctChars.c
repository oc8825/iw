#include <stdio.h>
#include <stdlib.h>

char* deep_copy_word(char* word) {
    char* p = word;
    size_t len = 0;
    while (*p) {
        len++;
        p++;
    }
    
    char* copy = malloc(len + 1);
    if (!copy) exit(2);
    
    char* src = word;
    char* dst = copy;
    while (*src) {
        *dst = *src;
        src++;
        dst++;
    }
    *dst = '\0';
    
    return copy;
}

size_t count_distinct_chars(char* word) {
    char* seen = malloc(1);
    if (!seen) exit(2);
    
    char* seen_end = seen;
    
    char* p = word;
    while (*p) {
        char current = *p;
        
        char* check = seen;
        int found = 0;
        while (check < seen_end) {
            if (*check == current) {
                found = 1;
                break;
            }
            check++;
        }
        
        if (!found) {
            size_t current_size = seen_end - seen;
            char* new_seen = realloc(seen, current_size + 2);
            if (!new_seen) {
                free(seen);
                exit(2);
            }
            seen = new_seen;
            seen_end = seen + current_size;
            *seen_end = current;
            seen_end++;
        }
        
        p++;
    }
    
    size_t count = seen_end - seen;
    free(seen);
    return count;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        return 0;
    }
    
    char** keys = malloc((argc - 1) * sizeof(char*));
    if (!keys) exit(2);
    
    size_t* distinct_counts = malloc((argc - 1) * sizeof(size_t));
    if (!distinct_counts) {
        free(keys);
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        char* word_copy = deep_copy_word(*(argv + i));
        *(keys + i - 1) = word_copy;
        *(distinct_counts + i - 1) = count_distinct_chars(word_copy);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%s %zu\n", *(keys + i), *(distinct_counts + i));
    }
    
    for (int i = 0; i < argc - 1; i++) {
        free(*(keys + i));
    }
    free(keys);
    free(distinct_counts);
    
    return 0;
}