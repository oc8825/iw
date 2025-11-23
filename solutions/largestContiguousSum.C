#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    long *sequence = (long*)malloc((argc - 1) * sizeof(long));
    if (!sequence) {
        return 2;
    }
    
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        
        if (strlen(argv[i]) == 0) {
            fprintf(stderr, "Error: All arguments must be valid integers.\n");
            free(sequence);
            return 1;
        }
        
        long val = strtol(argv[i], &endptr, 10);
        
        if (*endptr != '\0' || errno == ERANGE) {
            fprintf(stderr, "Error: All arguments must be valid integers.\n");
            free(sequence);
            return 1;
        }
        
        sequence[i - 1] = val;
    }
    
    long cur = sequence[0];
    long maxSoFar = sequence[0];
    
    for (int i = 1; i < argc - 1; i++) {
        cur = (sequence[i] > cur + sequence[i]) ? sequence[i] : cur + sequence[i];
        maxSoFar = (maxSoFar > cur) ? maxSoFar : cur;
    }
    
    printf("%ld\n", maxSoFar);
    free(sequence);
    return 0;
}