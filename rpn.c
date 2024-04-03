#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

// Structure to represent a stack
typedef struct {
    int top;
    char *items[STACK_SIZE];
} Stack;

// Function to initialize the stack
void initialize(Stack *s) {
    s->top = -1;
}

// Function to push an item onto the stack
void push(Stack *s, char *item) {
    if (s->top == STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = strdup(item);
}

// Function to pop an item from the stack
char *pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

// Function to check if a character is an operator
int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

// Function to convert RPN expression to infix expression
char *rpn_to_infix(const char *expression) {
    Stack s;
    initialize(&s);

    const char *delimiter = " ";
    char *token_ptr = strtok((char *)expression, delimiter);

    while (token_ptr != NULL) {
        if (!is_operator(*token_ptr)) {
            push(&s, token_ptr);
        } else {
            // Pop two operands from the stack
            char *operand2 = pop(&s);
            char *operand1 = pop(&s);

            // Check if there are enough operands
            if (!operand1 || !operand2) {
                printf("Error: Not enough operands for operator\n");
                exit(EXIT_FAILURE);
            }

            // Allocate memory for the infix expression
            char *infix_expression = malloc(strlen(operand1) + strlen(operand2) + 5); // 5 for parentheses, operator, and null terminator
            if (!infix_expression) {
                printf("Error: Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            // Format infix expression
            snprintf(infix_expression, strlen(operand1) + strlen(operand2) + 5, "(%s %c %s)", operand1, *token_ptr, operand2);

            // Free memory for operands
            free(operand1);
            free(operand2);

            // Push the infix expression onto the stack
            push(&s, infix_expression);
        }
        token_ptr = strtok(NULL, delimiter);
    }

    // Return the final infix expression
    return pop(&s);
}


int main() {
    char expression[STACK_SIZE];
    printf("Enter the RPN expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strlen(expression) - 1] = '\0'; // Removing newline character

    char *infix_expression = rpn_to_infix(expression);
    printf("Infix expression: %s\n", infix_expression);

    // Free memory allocated for the infix expression
    free(infix_expression);

    return 0;
}
