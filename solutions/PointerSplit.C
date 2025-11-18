#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: requires two command line arguments\n");
        return 1;
    }
    
    if (strlen(argv[2]) != 1) {
        fprintf(stderr, "Error: delim must be one character\n");
        return 1;
    }
    
    char *s = argv[1];
    char delim = argv[2][0];
    
    char *ptr = s;
    int count = 0;
    
    while (*ptr) {
        if (*ptr == delim) {
            count++;
        }
        ptr++;
    }
    count++;
    
    char **substrings = (char**)malloc(count * sizeof(char*));
    if (!substrings) {
        return 2;
    }
    
    ptr = s;
    int index = 0;
    
    while (*ptr) {
        char *start = ptr;
        int length = 0;
        
        while (*ptr && *ptr != delim) {
            length++;
            ptr++;
        }
        
        substrings[index] = (char*)malloc((length + 1) * sizeof(char));
        if (!substrings[index]) {
            for (int i = 0; i < index; i++) {
                free(substrings[i]);
            }
            free(substrings);
            return 2;
        }
        
        char *dest = substrings[index];
        char *src = start;
        for (int i = 0; i < length; i++) {
            *dest = *src;
            dest++;
            src++;
        }
        *dest = '\0';
        
        index++;
        
        if (*ptr == delim) {
            ptr++;
        }
    }
    
    for (int i = 0; i < count; i++) {
        printf("%s", substrings[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    for (int i = 0; i < count; i++) {
        free(substrings[i]);
    }
    free(substrings);
    
    return 0;
}