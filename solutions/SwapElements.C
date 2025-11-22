#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int parse_integer(const char *str, int *result) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || endptr == str) {
        return 0;
    }
    
    if (val < INT_MIN || val > INT_MAX) {
        return 0;
    }
    
    *result = (int)val;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Error: At least three arguments are required.\n");
        return 1;
    }
    
    int i;
    if (!parse_integer(argv[1], &i) || i < 0) {
        fprintf(stderr, "Error: Indices must be non-negative.\n");
        return 1;
    }
    
    int j;
    if (!parse_integer(argv[2], &j) || j < 0) {
        fprintf(stderr, "Error: Indices must be non-negative.\n");
        return 1;
    }
    
    int array_length = argc - 3;
    
    if (i >= array_length || j >= array_length) {
        fprintf(stderr, "Error: Indices must be less than the array length.\n");
        return 1;
    }
    
    int *array = (int*)malloc(array_length * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }
    
    for (int k = 0; k < array_length; k++) {
        if (!parse_integer(argv[k + 3], &array[k])) {
            fprintf(stderr, "Error: Invalid integer in array.\n");
            free(array);
            return 1;
        }
    }
    
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    
    for (int k = 0; k < array_length; k++) {
        printf("%d", array[k]);
        if (k < array_length - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(array);
    return 0;
}