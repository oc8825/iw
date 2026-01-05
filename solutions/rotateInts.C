#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int is_non_negative_integer(const char *str) {
    if (str == NULL || str[0] == '\0') return 0;
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) return 0;
    return 1;
}

int is_integer(const char *str) {
    if (str == NULL || str[0] == '\0') return 0;
    int start = 0;
    if (str[0] == '-') start = 1;
    if (str[start] == '\0') return 0;
    for (int i = start; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 0;

    if (!is_non_negative_integer(argv[1])) {
        printf("Error: n must be a non-negative integer.\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int list_count = argc - 2;

    if (list_count == 0) return 0;

    for (int i = 2; i < argc; i++) {
        if (!is_integer(argv[i])) {
            printf("Error: all list elements must be valid integers.\n");
            return 1;
        }
    }

    int *list = (int *)malloc(list_count * sizeof(int));
    if (list == NULL) {
        return 2;
    }

    for (int i = 0; i < list_count; i++) {
        list[i] = atoi(argv[i + 2]);
    }

    n = n % list_count;

    for (int i = 0; i < list_count; i++) {
        int index = (list_count - n + i) % list_count;
        printf("%d", list[index]);
        if (i < list_count - 1) printf(" ");
    }
    printf("\n");

    free(list);
    return 0;
}