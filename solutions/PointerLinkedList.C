#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node *create_node(const char *word) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    
    node->word = (char *)malloc(strlen(word) + 1);
    if (!node->word) {
        free(node);
        return NULL;
    }
    
    strcpy(node->word, word);
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    Node *head = NULL;
    
    for (int i = 1; i < argc; i++) {
        Node *new_node = create_node(argv[i]);
        if (!new_node) {
            free_list(head);
            return 2;
        }
        
        new_node->next = head;
        head = new_node;
    }
    
    Node *current = head;
    while (current) {
        printf("%s", current->word);
        if (current->next) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
    
    free_list(head);
    return 0;
}