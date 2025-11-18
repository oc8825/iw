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

char *duplicate_string(char *src) {
    int len = string_length(src);
    char *dst = (char *)malloc((len + 1) * sizeof(char));
    if (dst == NULL) {
        return NULL;
    }
    
    char *src_ptr = src;
    char *dst_ptr = dst;
    
    while (*src_ptr != '\0') {
        *dst_ptr = *src_ptr;
        src_ptr++;
        dst_ptr++;
    }
    *dst_ptr = '\0';
    
    return dst;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    int num_words = argc - 1;
    char **copied_words = (char **)malloc(num_words * sizeof(char *));
    if (copied_words == NULL) {
        exit(2);
    }
    
    for (int i = 0; i < num_words; i++) {
        copied_words[i] = duplicate_string(argv[i + 1]);
        if (copied_words[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(copied_words[j]);
            }
            free(copied_words);
            exit(2);
        }
    }
    
    for (int i = num_words - 1; i >= 0; i--) {
        printf("%s", copied_words[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
    
    for (int i = 0; i < num_words; i++) {
        free(copied_words[i]);
    }
    free(copied_words);
    
    return 0;
}