#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

static char arena[65536];
static size_t arena_offset = 0;

int is_valid_size(const char *str, int32_t *result) {
    if (!str || *str == '\0') {
        return 0;
    }
    
    const char *p = str;
    while (*p) {
        if (*p < '0' || *p > '9') {
            return 0;
        }
        p++;
    }
    
    long long value = 0;
    p = str;
    while (*p) {
        long long new_value = value * 10 + (*p - '0');
        if (new_value > 2147483647) {
            return 0;
        }
        value = new_value;
        p++;
    }
    
    *result = (int32_t)value;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        int32_t size;
        if (!is_valid_size(argv[i], &size)) {
            printf("ERROR: invalid size\n");
            return 1;
        }
        
        size_t aligned = ((arena_offset + 7) / 8) * 8;
        
        if (aligned > 65536 || size > 65536 - aligned) {
            printf("ERROR: out of memory\n");
            return 1;
        }
        
        printf("%zu\n", aligned);
        arena_offset = aligned + size;
    }
    
    return 0;
}