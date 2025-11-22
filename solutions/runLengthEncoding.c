#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encode_word(const char* word) {
    if (!word) return NULL;
    
    const char* ptr = word;
    if (*ptr == '\0') {
        char* result = malloc(1);
        if (!result) return NULL;
        *result = '\0';
        return result;
    }
    
    char* encoded = NULL;
    size_t encoded_size = 0;
    size_t encoded_capacity = 0;
    
    while (*ptr) {
        char current_char = *ptr;
        int count = 1;
        
        ptr++;
        while (*ptr && *ptr == current_char) {
            count++;
            ptr++;
        }
        
        char count_str[32];
        sprintf(count_str, "%d", count);
        size_t count_len = strlen(count_str);
        
        size_t needed = encoded_size + 1 + count_len;
        if (needed > encoded_capacity) {
            encoded_capacity = needed * 2;
            char* new_encoded = realloc(encoded, encoded_capacity);
            if (!new_encoded) {
                free(encoded);
                return NULL;
            }
            encoded = new_encoded;
        }
        
        encoded[encoded_size] = current_char;
        encoded_size++;
        
        const char* count_ptr = count_str;
        while (*count_ptr) {
            encoded[encoded_size] = *count_ptr;
            encoded_size++;
            count_ptr++;
        }
    }
    
    if (encoded_size >= encoded_capacity) {
        char* new_encoded = realloc(encoded, encoded_size + 1);
        if (!new_encoded) {
            free(encoded);
            return NULL;
        }
        encoded = new_encoded;
    }
    encoded[encoded_size] = '\0';
    
    return encoded;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    char** encoded_words = malloc((argc - 1) * sizeof(char*));
    if (!encoded_words) {
        exit(2);
    }
    
    int i;
    for (i = 1; i < argc; i++) {
        encoded_words[i - 1] = encode_word(argv[i]);
        if (!encoded_words[i - 1]) {
            int j;
            for (j = 0; j < i - 1; j++) {
                free(encoded_words[j]);
            }
            free(encoded_words);
            exit(2);
        }
    }
    
    for (i = 0; i < argc - 1; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%s", encoded_words[i]);
    }
    printf("\n");
    
    for (i = 0; i < argc - 1; i++) {
        free(encoded_words[i]);
    }
    free(encoded_words);
    
    return 0;
}