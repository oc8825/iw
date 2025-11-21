#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

Stack* stack_create() {
    Stack *s = malloc(sizeof(Stack));
    if (!s) return NULL;
    s->data = malloc(sizeof(int) * 2);
    if (!s->data) {
        free(s);
        return NULL;
    }
    s->size = 0;
    s->capacity = 2;
    return s;
}

void stack_free(Stack *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

int stack_push(Stack *s, int value) {
    if (s->size >= s->capacity) {
        int new_capacity = s->capacity * 2;
        int *new_data = realloc(s->data, sizeof(int) * new_capacity);
        if (!new_data) return 0;
        s->data = new_data;
        s->capacity = new_capacity;
    }
    s->data[s->size++] = value;
    return 1;
}

int stack_pop(Stack *s, int *value) {
    if (s->size <= 0) return 0;
    *value = s->data[--s->size];
    return 1;
}

int is_operator(const char *token) {
    return (strlen(token) == 1 && 
            (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'));
}

int is_integer(const char *token) {
    char *endptr;
    strtol(token, &endptr, 10);
    return (*endptr == '\0' && strlen(token) > 0);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    Stack *stack = stack_create();
    if (!stack) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        char *token = argv[i];
        
        if (is_integer(token)) {
            int value = atoi(token);
            if (!stack_push(stack, value)) {
                stack_free(stack);
                exit(2);
            }
        } else if (is_operator(token)) {
            if (stack->size < 2) {
                fprintf(stderr, "Error: invalid expression\n");
                stack_free(stack);
                exit(1);
            }
            
            int right, left;
            stack_pop(stack, &right);
            stack_pop(stack, &left);
            
            int result;
            switch (token[0]) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    result = left / right;
                    break;
            }
            
            if (!stack_push(stack, result)) {
                stack_free(stack);
                exit(2);
            }
        } else {
            fprintf(stderr, "Error: invalid expression\n");
            stack_free(stack);
            exit(1);
        }
    }
    
    if (stack->size != 1) {
        fprintf(stderr, "Error: invalid expression\n");
        stack_free(stack);
        exit(1);
    }
    
    printf("%d\n", stack->data[0]);
    stack_free(stack);
    return 0;
}