#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Entry {
    char *name;
    char *phone;
};

int compare_entries(const void *a, const void *b) {
    const struct Entry *entry_a = (const struct Entry *)a;
    const struct Entry *entry_b = (const struct Entry *)b;
    return strcmp(entry_a->name, entry_b->name);
}

char *duplicate_string(const char *str) {
    size_t len = strlen(str);
    char *copy = (char *)malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, str);
    return copy;
}

void free_entries(struct Entry *entries, int count) {
    for (int i = 0; i < count; i++) {
        free(entries[i].name);
        free(entries[i].phone);
    }
    free(entries);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    if ((argc - 1) % 2 != 0) {
        fprintf(stderr, "Error: requires pairs of name and number\n");
        return 1;
    }
    
    int num_pairs = (argc - 1) / 2;
    struct Entry *entries = (struct Entry *)malloc(num_pairs * sizeof(struct Entry));
    if (!entries) {
        return 2;
    }
    
    for (int i = 0; i < num_pairs; i++) {
        entries[i].name = duplicate_string(argv[1 + i * 2]);
        entries[i].phone = duplicate_string(argv[1 + i * 2 + 1]);
        
        if (!entries[i].name || !entries[i].phone) {
            for (int j = 0; j <= i; j++) {
                free(entries[j].name);
                free(entries[j].phone);
            }
            free(entries);
            return 2;
        }
    }
    
    qsort(entries, num_pairs, sizeof(struct Entry), compare_entries);
    
    for (int i = 0; i < num_pairs; i++) {
        printf("%s: %s\n", entries[i].name, entries[i].phone);
    }
    
    free_entries(entries, num_pairs);
    return 0;
}