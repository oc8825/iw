#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }

    int *array = NULL;
    int capacity = 1;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        char *end;
        long num = strtol(argv[i], &end, 10);
        if (end == argv[i] || *end != '\0' || num < INT_MIN || num > INT_MAX) {
            fprintf(stderr, "Invalid integer input.\n");
            free(array);
            return 2;
        }

        if (count == capacity) {
            int *new_array = (int*)realloc(array, 2 * capacity * sizeof(int));
            if (new_array == NULL) {
                fprintf(stderr, "Memory allocation failure.\n");
                free(array);
                return 2;
            }
            array = new_array;
            capacity *= 2;
        }

        array[count++] = (int)num;
    }

    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}