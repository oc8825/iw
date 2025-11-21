#include <stdio.h>
#include <stdlib.h>

char* deep_copy_string(char* src) {
    if (!src) return NULL;
    
    char* len_ptr = src;
    int length = 0;
    while (*len_ptr) {
        length++;
        len_ptr++;
    }
    
    char* dest = malloc(length + 1);
    if (!dest) return NULL;
    
    char* src_ptr = src;
    char* dest_ptr = dest;
    while (*src_ptr) {
        *dest_ptr = *src_ptr;
        src_ptr++;
        dest_ptr++;
    }
    *dest_ptr = '\0';
    
    return dest;
}

void sort_string(char* str) {
    if (!str) return;
    
    char* end_ptr = str;
    int length = 0;
    while (*end_ptr) {
        length++;
        end_ptr++;
    }
    
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            char* ptr1 = str;
            char* ptr2 = str;
            
            for (int k = 0; k < j; k++) {
                ptr1++;
            }
            for (int k = 0; k < j + 1; k++) {
                ptr2++;
            }
            
            if (*ptr1 > *ptr2) {
                char temp = *ptr1;
                *ptr1 = *ptr2;
                *ptr2 = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    char** keys = malloc((argc - 1) * sizeof(char*));
    char** values = malloc((argc - 1) * sizeof(char*));
    
    if (!keys || !values) {
        if (keys) free(keys);
        if (values) free(values);
        return 2;
    }
    
    for (int i = 1; i < argc; i++) {
        keys[i - 1] = deep_copy_string(argv[i]);
        values[i - 1] = deep_copy_string(argv[i]);
        
        if (!keys[i - 1] || !values[i - 1]) {
            for (int j = 0; j < i; j++) {
                if (keys[j]) free(keys[j]);
                if (values[j]) free(values[j]);
            }
            free(keys);
            free(values);
            return 2;
        }
        
        sort_string(values[i - 1]);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%s %s\n", keys[i], values[i]);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        free(keys[i]);
        free(values[i]);
    }
    free(keys);
    free(values);
    
    return 0;
}