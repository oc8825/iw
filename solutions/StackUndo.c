#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return p - s;
}

char *my_strcpy(const char *src) {
    int len = my_strlen(src);
    char *dst = malloc(len + 1);
    if (!dst) return NULL;
    
    const char *s = src;
    char *d = dst;
    while (*s) {
        *d = *s;
        s++;
        d++;
    }
    *d = '\0';
    return dst;
}

int my_strcmp(const char *s1, const char *s2) {
    const char *p1 = s1;
    const char *p2 = s2;
    while (*p1 && *p2 && *p1 == *p2) {
        p1++;
        p2++;
    }
    return *p1 - *p2;
}

int main(int argc, char *argv[]) {
    char **stack = NULL;
    int capacity = 0;
    int size = 0;
    
    for (int i = 1; i < argc; i++) {
        if (my_strcmp(*(argv + i), "undo") == 0) {
            if (size == 0) {
                fprintf(stderr, "Error: nothing to undo\n");
                for (int j = 0; j < size; j++) {
                    free(*(stack + j));
                }
                free(stack);
                exit(1);
            }
            size--;
            free(*(stack + size));
        } else {
            if (size >= capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                char **new_stack = realloc(stack, capacity * sizeof(char *));
                if (!new_stack) {
                    for (int j = 0; j < size; j++) {
                        free(*(stack + j));
                    }
                    free(stack);
                    exit(2);
                }
                stack = new_stack;
            }
            
            char *action = my_strcpy(*(argv + i));
            if (!action) {
                for (int j = 0; j < size; j++) {
                    free(*(stack + j));
                }
                free(stack);
                exit(2);
            }
            *(stack + size) = action;
            size++;
        }
    }
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", *(stack + i));
        free(*(stack + i));
    }
    
    free(stack);
    return 0;
}