#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    int *lengths = (int*)malloc((argc - 1) * sizeof(int));
    if (!lengths) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        lengths[i - 1] = strlen(argv[i]);
    }
    
    qsort(lengths, argc - 1, sizeof(int), compare_ints);
    
    for (int i = 0; i < argc - 1; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", lengths[i]);
    }
    printf("\n");
    
    free(lengths);
    return 0;
}