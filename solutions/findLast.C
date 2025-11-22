#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int parse_integer(const char *str, int *result) {
    char *endptr;
    long val;
    
    errno = 0;
    val = strtol(str, &endptr, 10);
    
    if (errno != 0) {
        return 0;
    }
    
    if (endptr == str) {
        return 0;
    }
    
    if (*endptr != '\0') {
        return 0;
    }
    
    if (val < INT_MIN || val > INT_MAX) {
        return 0;
    }
    
    *result = (int)val;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No command line arguments provided\n");
        return 1;
    }
    
    int elem;
    int arr_size = argc - 2;
    
    if (!parse_integer(argv[1], &elem)) {
        fprintf(stderr, "Invalid integer\n");
        return 1;
    }
    
    int last_index = -1;
    
    for (int i = 0; i < arr_size; i++) {
        int value;
        if (!parse_integer(argv[i + 2], &value)) {
            fprintf(stderr, "Invalid integer\n");
            return 1;
        }
        if (value == elem) {
            last_index = i;
        }
    }
    
    printf("%d\n", last_index);
    
    return 0;
}