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
        *(words + i - 1) = *(argv + i);
    }

    if (argc > 2) {
        char *first = *words;
        char **temp = words;

        while (temp < words + argc - 2) {
            *temp = *(temp + 1);
            temp++;
        }
        *temp = first;
    }

    for (int i = 0; i < argc - 1; i++) {
        printf("%s", *(words + i));
        if (i < argc - 2) {
            printf(" ");
        }
    }
    printf("\n");

    free(words);
    return 0;
}