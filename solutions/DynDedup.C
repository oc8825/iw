#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }

    char **words = NULL;
    size_t capacity = 0;
    size_t count = 0;

    for (int i = 1; i < argc; i++) {
        int found = 0;
        for (size_t j = 0; j < count; j++) {
            if (strcmp(argv[i], words[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (count == capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                words = realloc(words, capacity * sizeof(char *));
                if (words == NULL) {
                    exit(2);
                }
            }
            words[count] = strdup(argv[i]);
            if (words[count] == NULL) {
                exit(2);
            }
            count++;
        }
    }

    qsort(words, count, sizeof(char *), compare);

    for (size_t i = 0; i < count; i++) {
        printf("%s", words[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}