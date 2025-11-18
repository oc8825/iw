#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverse_word(const char* word) {
    int len = strlen(word);
    char* reversed = (char*)malloc(len + 1);
    if (!reversed) {
        return NULL;
    }
    
    for (int i = 0; i < len; i++) {
        reversed[i] = word[len - 1 - i];
    }
    reversed[len] = '\0';
    
    return reversed;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    char** reversed_words = (char**)malloc((argc - 1) * sizeof(char*));
    if (!reversed_words) {
        exit(2);
    }
    
    int total_length = 0;
    
    for (int i = 1; i < argc; i++) {
        reversed_words[i - 1] = reverse_word(argv[i]);
        if (!reversed_words[i - 1]) {
            for (int j = 0; j < i - 1; j++) {
                free(reversed_words[j]);
            }
            free(reversed_words);
            exit(2);
        }
        total_length += strlen(reversed_words[i - 1]);
        if (i > 1) {
            total_length += 1;
        }
    }
    
    char* result = (char*)malloc(total_length + 1);
    if (!result) {
        for (int i = 0; i < argc - 1; i++) {
            free(reversed_words[i]);
        }
        free(reversed_words);
        exit(2);
    }
    
    result[0] = '\0';
    
    for (int i = 0; i < argc - 1; i++) {
        if (i > 0) {
            strcat(result, ",");
        }
        strcat(result, reversed_words[i]);
    }
    
    printf("%s\n", result);
    
    for (int i = 0; i < argc - 1; i++) {
        free(reversed_words[i]);
    }
    free(reversed_words);
    free(result);
    
    return 0;
}