#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    int *numbers = (int*)malloc((argc - 1) * sizeof(int));
    if (numbers == NULL) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i], &endptr, 10);
        
        if (errno != 0 || *endptr != '\0' || endptr == argv[i] || val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Error: command line argument not an integer\n");
            free(numbers);
            exit(1);
        }
        
        numbers[i - 1] = (int)val;
    }
    
    qsort(numbers, argc - 1, sizeof(int), compare);
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%d", numbers[i]);
        if (i < argc - 2) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(numbers);
    return 0;
}