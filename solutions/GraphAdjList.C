#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *label;
    char **neighbors;
    size_t ndegs;
    size_t cap;
};

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int compare_nodes(const void *a, const void *b) {
    const struct Node *na = (const struct Node *)a;
    const struct Node *nb = (const struct Node *)b;
    return strcmp(na->label, nb->label);
}

struct Node *find_or_create_node(struct Node **nodes, size_t *num_nodes, size_t *nodes_cap, const char *label) {
    for (size_t i = 0; i < *num_nodes; i++) {
        if (strcmp((*nodes)[i].label, label) == 0) {
            return &(*nodes)[i];
        }
    }
    
    if (*num_nodes >= *nodes_cap) {
        *nodes_cap = (*nodes_cap == 0) ? 1 : *nodes_cap * 2;
        *nodes = (struct Node *)realloc(*nodes, *nodes_cap * sizeof(struct Node));
        if (!*nodes) exit(2);
    }
    
    struct Node *new_node = &(*nodes)[*num_nodes];
    new_node->label = (char *)malloc(strlen(label) + 1);
    if (!new_node->label) exit(2);
    strcpy(new_node->label, label);
    new_node->neighbors = NULL;
    new_node->ndegs = 0;
    new_node->cap = 0;
    (*num_nodes)++;
    
    return new_node;
}

void add_edge(struct Node *from_node, const char *to_label) {
    for (size_t i = 0; i < from_node->ndegs; i++) {
        if (strcmp(from_node->neighbors[i], to_label) == 0) {
            return;
        }
    }
    
    if (from_node->ndegs >= from_node->cap) {
        from_node->cap = (from_node->cap == 0) ? 1 : from_node->cap * 2;
        from_node->neighbors = (char **)realloc(from_node->neighbors, from_node->cap * sizeof(char *));
        if (!from_node->neighbors) exit(2);
    }
    
    from_node->neighbors[from_node->ndegs] = (char *)malloc(strlen(to_label) + 1);
    if (!from_node->neighbors[from_node->ndegs]) exit(2);
    strcpy(from_node->neighbors[from_node->ndegs], to_label);
    from_node->ndegs++;
}

int parse_edge(const char *arg, char **from, char **to) {
    const char *arrow = strstr(arg, "->");
    if (!arrow) return 0;
    
    size_t from_len = arrow - arg;
    if (from_len == 0) return 0;
    
    const char *to_start = arrow + 2;
    if (strlen(to_start) == 0) return 0;
    
    *from = (char *)malloc(from_len + 1);
    if (!*from) exit(2);
    strncpy(*from, arg, from_len);
    (*from)[from_len] = '\0';
    
    *to = (char *)malloc(strlen(to_start) + 1);
    if (!*to) {
        free(*from);
        exit(2);
    }
    strcpy(*to, to_start);
    
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    struct Node *nodes = NULL;
    size_t num_nodes = 0;
    size_t nodes_cap = 0;
    
    for (int i = 1; i < argc; i++) {
        char *from, *to;
        if (!parse_edge(argv[i], &from, &to)) {
            fprintf(stderr, "Error: invalid edge\n");
            return 1;
        }
        
        struct Node *from_node = find_or_create_node(&nodes, &num_nodes, &nodes_cap, from);
        find_or_create_node(&nodes, &num_nodes, &nodes_cap, to);
        add_edge(from_node, to);
        
        free(from);
        free(to);
    }
    
    qsort(nodes, num_nodes, sizeof(struct Node), compare_nodes);
    
    for (size_t i = 0; i < num_nodes; i++) {
        qsort(nodes[i].neighbors, nodes[i].ndegs, sizeof(char *), compare_strings);
    }
    
    for (size_t i = 0; i < num_nodes; i++) {
        printf("%s:", nodes[i].label);
        for (size_t j = 0; j < nodes[i].ndegs; j++) {
            printf(" %s", nodes[i].neighbors[j]);
        }
        printf("\n");
    }
    
    for (size_t i = 0; i < num_nodes; i++) {
        free(nodes[i].label);
        for (size_t j = 0; j < nodes[i].ndegs; j++) {
            free(nodes[i].neighbors[j]);
        }
        free(nodes[i].neighbors);
    }
    free(nodes);
    
    return 0;
}