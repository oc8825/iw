#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }

    char **words = (char **)malloc((argc - 1) * sizeof(char *));
    if (words == NULL) {
        return 2;
    }

    for (int i = 1; i < argc; i++) {
        words[i - 1] = argv[i];
    }

    if (argc > 2) {
        char **first = words;
        char **last = words + argc - 2;
        char *temp = *first;

        while (first < last) {
            *first = *(first + 1);
            first++;
        }
        *last = temp;
    }

    for (int i = 0; i < argc - 1; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%s", words[i]);
    }
    printf("\n");

    free(words);
    return 0;
}