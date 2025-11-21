#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;
} HashMap;

typedef struct {
    char **keys;
    int count;
    int capacity;
} InsertionOrder;

unsigned int hash(const char *str, int table_size) {
    unsigned int hash_value = 0;
    const char *p = str;
    while (*p) {
        hash_value = hash_value * 31 + *p;
        p++;
    }
    return hash_value % table_size;
}

int string_length(const char *str) {
    int len = 0;
    const char *p = str;
    while (*p) {
        len++;
        p++;
    }
    return len;
}

char *string_duplicate(const char *str) {
    int len = string_length(str);
    char *dup = malloc(len + 1);
    if (!dup) return NULL;
    
    const char *src = str;
    char *dst = dup;
    while (*src) {
        *dst = *src;
        src++;
        dst++;
    }
    *dst = '\0';
    return dup;
}

int strings_equal(const char *str1, const char *str2) {
    const char *p1 = str1;
    const char *p2 = str2;
    while (*p1 && *p2) {
        if (*p1 != *p2) return 0;
        p1++;
        p2++;
    }
    return *p1 == *p2;
}

HashMap *create_hashmap(int size) {
    HashMap *map = malloc(sizeof(HashMap));
    if (!map) return NULL;
    
    map->buckets = malloc(size * sizeof(Node*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        map->buckets[i] = NULL;
    }
    map->size = size;
    return map;
}

InsertionOrder *create_insertion_order() {
    InsertionOrder *order = malloc(sizeof(InsertionOrder));
    if (!order) return NULL;
    
    order->keys = malloc(10 * sizeof(char*));
    if (!order->keys) {
        free(order);
        return NULL;
    }
    order->count = 0;
    order->capacity = 10;
    return order;
}

int add_to_insertion_order(InsertionOrder *order, const char *key) {
    if (order->count >= order->capacity) {
        int new_capacity = order->capacity * 2;
        char **new_keys = malloc(new_capacity * sizeof(char*));
        if (!new_keys) return 0;
        
        for (int i = 0; i < order->count; i++) {
            new_keys[i] = order->keys[i];
        }
        free(order->keys);
        order->keys = new_keys;
        order->capacity = new_capacity;
    }
    
    order->keys[order->count] = (char*)key;
    order->count++;
    return 1;
}

int hashmap_insert(HashMap *map, const char *key, int value, InsertionOrder *order) {
    unsigned int index = hash(key, map->size);
    Node *current = map->buckets[index];
    
    while (current) {
        if (strings_equal(current->key, key)) {
            current->value += value;
            return 1;
        }
        current = current->next;
    }
    
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return 0;
    
    new_node->key = string_duplicate(key);
    if (!new_node->key) {
        free(new_node);
        return 0;
    }
    
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
    
    if (!add_to_insertion_order(order, new_node->key)) {
        return 0;
    }
    
    return 1;
}

int hashmap_get(HashMap *map, const char *key) {
    unsigned int index = hash(key, map->size);
    Node *current = map->buckets[index];
    
    while (current) {
        if (strings_equal(current->key, key)) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

void free_hashmap(HashMap *map) {
    if (!map) return;
    
    for (int i = 0; i < map->size; i++) {
        Node *current = map->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

void free_insertion_order(InsertionOrder *order) {
    if (!order) return;
    free(order->keys);
    free(order);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    HashMap *map = create_hashmap(101);
    if (!map) {
        exit(2);
    }
    
    InsertionOrder *order = create_insertion_order();
    if (!order) {
        free_hashmap(map);
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        int len = string_length(argv[i]);
        if (!hashmap_insert(map, argv[i], len, order)) {
            free_hashmap(map);
            free_insertion_order(order);
            exit(2);
        }
    }
    
    for (int i = 0; i < order->count; i++) {
        int value = hashmap_get(map, order->keys[i]);
        printf("%s %d\n", order->keys[i], value);
    }
    
    free_hashmap(map);
    free_insertion_order(order);
    return 0;
}