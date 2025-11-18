#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    char first_char = argv[1][0];
    char **words = NULL;
    size_t count = 0;
    size_t capacity = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == first_char) {
            if (count == capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                void *new_words = realloc(words, capacity * sizeof(char *));
                if (new_words == NULL) {
                    free(words);
                    return 2;
                }
                words = (char **)new_words;
            }
            words[count++] = argv[i];
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

    free(words);
    return 0;
}