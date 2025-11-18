#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_chars(char *start, char *end) {
    char temp = *start;
    *start = *end;
    *end = temp;
}

void reverse_word(char *word) {
    char *start = word;
    char *end = word;
    
    while (*end != '\0') {
        end++;
    }
    end--;
    
    while (start < end) {
        swap_chars(start, end);
        start++;
        end--;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        reverse_word(argv[i]);
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}