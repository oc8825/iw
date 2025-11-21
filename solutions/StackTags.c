#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    char *tag;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

void stack_init(Stack *s) {
    s->top = NULL;
}

int is_alpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char *str_dup(const char *src, const char *end) {
    const char *p = src;
    int len = 0;
    while (p < end) {
        len++;
        p++;
    }
    
    char *dst = malloc(len + 1);
    if (!dst) return NULL;
    
    const char *s = src;
    char *d = dst;
    while (s < end) {
        *d = *s;
        s++;
        d++;
    }
    *d = '\0';
    
    return dst;
}

int str_equal(const char *a, const char *b) {
    const char *pa = a;
    const char *pb = b;
    while (*pa && *pb) {
        if (*pa != *pb) return 0;
        pa++;
        pb++;
    }
    return *pa == *pb;
}

void stack_push(Stack *s, const char *tag, const char *end) {
    StackNode *node = malloc(sizeof(StackNode));
    if (!node) exit(2);
    
    node->tag = str_dup(tag, end);
    if (!node->tag) {
        free(node);
        exit(2);
    }
    
    node->next = s->top;
    s->top = node;
}

int stack_pop_and_check(Stack *s, const char *tag, const char *end) {
    if (!s->top) return 0;
    
    char *temp_tag = str_dup(tag, end);
    if (!temp_tag) exit(2);
    
    int match = str_equal(s->top->tag, temp_tag);
    free(temp_tag);
    
    StackNode *temp = s->top;
    s->top = s->top->next;
    free(temp->tag);
    free(temp);
    
    return match;
}

int stack_empty(Stack *s) {
    return s->top == NULL;
}

void stack_free(Stack *s) {
    while (s->top) {
        StackNode *temp = s->top;
        s->top = s->top->next;
        free(temp->tag);
        free(temp);
    }
}

int main(int argc, char *argv[]) {
    Stack stack;
    stack_init(&stack);
    
    for (int i = 1; i < argc; i++) {
        char *p = argv[i];
        
        while (*p) {
            if (*p == '<') {
                p++;
                
                int is_closing = 0;
                if (*p == '/') {
                    is_closing = 1;
                    p++;
                }
                
                char *tag_start = p;
                while (*p && *p != '>') {
                    if (!is_alpha(*p)) {
                        fprintf(stderr, "Error: invalid structure\n");
                        stack_free(&stack);
                        exit(1);
                    }
                    p++;
                }
                
                if (*p != '>') {
                    fprintf(stderr, "Error: invalid structure\n");
                    stack_free(&stack);
                    exit(1);
                }
                
                if (tag_start == p) {
                    fprintf(stderr, "Error: invalid structure\n");
                    stack_free(&stack);
                    exit(1);
                }
                
                if (is_closing) {
                    if (!stack_pop_and_check(&stack, tag_start, p)) {
                        fprintf(stderr, "Error: invalid structure\n");
                        stack_free(&stack);
                        exit(1);
                    }
                } else {
                    stack_push(&stack, tag_start, p);
                }
                
                p++;
            } else {
                p++;
            }
        }
    }
    
    if (!stack_empty(&stack)) {
        fprintf(stderr, "Error: invalid structure\n");
        stack_free(&stack);
        exit(1);
    }
    
    printf("valid\n");
    stack_free(&stack);
    return 0;
}