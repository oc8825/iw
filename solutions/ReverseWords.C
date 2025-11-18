#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    int i;
    char temp;
    
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main(int argc, char *argv[]) {
    int i;
    char *reversed;
    int len;
    
    if (argc == 1) {
        return 0;
    }
    
    for (i = 1; i < argc; i++) {
        len = strlen(argv[i]);
        reversed = (char*)malloc(len + 1);
        if (reversed == NULL) {
            exit(2);
        }
        
        strcpy(reversed, argv[i]);
        reverse_string(reversed);
        
        printf("%s", reversed);
        if (i < argc - 1) {
            printf(" ");
        }
        
        free(reversed);
    }
    
    printf("\n");
    return 0;
}