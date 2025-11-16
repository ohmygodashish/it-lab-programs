/*
Write a program to generate three-address (intermediate) code for the given source code.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[100], stack[100], postfix[100];
int top = -1;

// Stack operations
void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }

// Operator precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Convert infix to postfix
void infixToPostfix() {
    int i, j = 0;
    for (i = 0; i < strlen(expr); i++) {
        char c = expr[i];
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();
            pop();
        } else {
            while (top != -1 && precedence(peek()) >= precedence(c))
                postfix[j++] = pop();
            push(c);
        }
    }
    while (top != -1)
        postfix[j++] = pop();
    postfix[j] = '\0';
}

// Generate three-address code
void generateTAC() {
    char temp = '1';
    char op1, op2, op;
    char stack2[100];
    int top2 = -1;
    
    for (int i = 0; i < strlen(postfix); i++) {
        if (isalnum(postfix[i])) {
            stack2[++top2] = postfix[i];
        } else {
            op2 = stack2[top2--];
            op1 = stack2[top2--];
            printf("t%c = %c %c %c\n", temp, op1, postfix[i], op2);
            stack2[++top2] = 't';
            stack2[++top2] = temp++;
        }
    }
    printf("Result = t%c\n", temp - 1);
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", expr);

    infixToPostfix();
    printf("\nPostfix: %s\n", postfix);
    printf("\nThree Address Code:\n");
    generateTAC();
    return 0;
}