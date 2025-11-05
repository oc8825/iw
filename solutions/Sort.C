#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    
    int *numbers = (int*)malloc((argc - 1) * sizeof(int));
    
    for (int i = 1; i < argc; i++) {
        numbers[i - 1] = atoi(argv[i]);
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