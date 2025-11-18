#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: requires two command line arguments\n");
        return 1;
    }
    
    if (strlen(argv[1]) != 1) {
        fprintf(stderr, "Error: target must be one character\n");
        return 1;
    }
    
    char target = argv[1][0];
    char *text = argv[2];
    int count = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == target) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}