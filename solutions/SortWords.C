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
    
    char **words = (char **)malloc((argc - 1) * sizeof(char *));
    if (words == NULL) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        words[i - 1] = argv[i];
    }
    
    qsort(words, argc - 1, sizeof(char *), compare_strings);
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%s", words[i]);
        if (i < argc - 2) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(words);
    return 0;
}