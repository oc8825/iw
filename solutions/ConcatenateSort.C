#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t buffer_len = 0;
    
    for (int i = 1; i < argc; i++) {
        size_t word_len = strlen(argv[i]);
        size_t needed = buffer_len + word_len + (i > 1 ? 1 : 0) + 1;
        
        if (needed > buffer_size) {
            size_t new_size = buffer_size == 0 ? 64 : buffer_size * 2;
            while (new_size < needed) {
                new_size *= 2;
            }
            char *new_buffer = (char *)realloc(buffer, new_size);
            if (!new_buffer) {
                free(buffer);
                exit(2);
            }
            buffer = new_buffer;
            buffer_size = new_size;
        }
        
        if (i > 1) {
            buffer[buffer_len] = ' ';
            buffer_len++;
        }
        
        memcpy(buffer + buffer_len, argv[i], word_len);
        buffer_len += word_len;
        buffer[buffer_len] = '\0';
    }
    
    if (!buffer) {
        exit(2);
    }
    
    int word_count = 0;
    for (size_t i = 0; i < buffer_len; i++) {
        if (buffer[i] == ' ') {
            word_count++;
        }
    }
    word_count++;
    
    char **words = (char **)malloc(word_count * sizeof(char *));
    if (!words) {
        free(buffer);
        exit(2);
    }
    
    int word_index = 0;
    char *start = buffer;
    
    for (size_t i = 0; i <= buffer_len; i++) {
        if (i == buffer_len || buffer[i] == ' ') {
            size_t word_len = buffer + i - start;
            words[word_index] = (char *)malloc(word_len + 1);
            if (!words[word_index]) {
                for (int j = 0; j < word_index; j++) {
                    free(words[j]);
                }
                free(words);
                free(buffer);
                exit(2);
            }
            memcpy(words[word_index], start, word_len);
            words[word_index][word_len] = '\0';
            word_index++;
            start = buffer + i + 1;
        }
    }
    
    qsort(words, word_count, sizeof(char *), compare_strings);
    
    for (int i = 0; i < word_count; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%s", words[i]);
    }
    printf("\n");
    
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    free(buffer);
    
    return 0;
}