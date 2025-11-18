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
    
    char **unique_words = (char **)malloc((argc - 1) * sizeof(char *));
    if (!unique_words) {
        exit(2);
    }
    
    int unique_count = 0;
    
    for (int i = 1; i < argc; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(argv[i], unique_words[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        
        if (!is_duplicate) {
            unique_words[unique_count] = (char *)malloc(strlen(argv[i]) + 1);
            if (!unique_words[unique_count]) {
                for (int k = 0; k < unique_count; k++) {
                    free(unique_words[k]);
                }
                free(unique_words);
                exit(2);
            }
            strcpy(unique_words[unique_count], argv[i]);
            unique_count++;
        }
    }
    
    qsort(unique_words, unique_count, sizeof(char *), compare_strings);
    
    for (int i = 0; i < unique_count; i++) {
        printf("%s", unique_words[i]);
        if (i < unique_count - 1) {
            printf(" ");
        }
    }
    if (unique_count > 0) {
        printf("\n");
    }
    
    for (int i = 0; i < unique_count; i++) {
        free(unique_words[i]);
    }
    free(unique_words);
    
    return 0;
}