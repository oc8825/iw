#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("0\n");
        return 0;
    }

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long num = strtol(argv[i], &endptr, 10);

        if (errno != 0 || *endptr != '\0' || endptr == argv[i] || num < INT_MIN || num > INT_MAX) {
            fprintf(stderr, "Error: command line argument not an integer\n");
            return 1;
        }

        if ((num > 0 && sum > INT_MAX - num) || (num < 0 && sum < INT_MIN - num)) {
            return 2;
        }

        sum += (int)num;
    }

    printf("%d\n", sum);
    return 0;
}