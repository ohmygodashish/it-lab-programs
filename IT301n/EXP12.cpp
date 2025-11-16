/*
Write a program to implement a shift-reduce parser/LR parser.
*/

#include <stdio.h>
#include <string.h>

char input[100];
int i = 0, j = 0, k = 0, z = 0;
int f = 0;
char stack[100], temp[2], act[20];

// Function to print the current action and stack
void printAction() {
    printf("%s\t%s$\t%s$\n", stack, input + i, act);
}

// Function to perform reductions
void check() {
    for (z = 0; z < strlen(stack); z++) {
        if (stack[z] == 'i' && stack[z + 1] == 'd') {
            stack[z] = 'F';
            stack[z + 1] = '\0';
            printf("REDUCE F -> id\n");
            printAction();
            i++;
        }
    }

    for (z = 0; z < strlen(stack); z++) {
        if (stack[z] == '(' && stack[z + 1] == 'E' && stack[z + 2] == ')') {
            stack[z] = 'F';
            stack[z + 1] = stack[z + 2] = '\0';
            printf("REDUCE F -> (E)\n");
            printAction();
        }
    }

    for (z = 0; z < strlen(stack); z++) {
        if (stack[z] == 'T' && stack[z + 1] == '*' && stack[z + 2] == 'F') {
            stack[z] = 'T';
            stack[z + 1] = stack[z + 2] = '\0';
            printf("REDUCE T -> T*F\n");
            printAction();
        }
    }

    for (z = 0; z < strlen(stack); z++) {
        if (stack[z] == 'F') {
            stack[z] = 'T';
            stack[z + 1] = '\0';
            printf("REDUCE T -> F\n");
            printAction();
        }
    }

    for (z = 0; z < strlen(stack); z++) {
        if (stack[z] == 'E' && stack[z + 1] == '+' && stack[z + 2] == 'T') {
            stack[z] = 'E';
            stack[z + 1] = stack[z + 2] = '\0';
            printf("REDUCE E -> E+T\n");
            printAction();
        }
    }

    for (z = 0; z < strlen(stack); z++) {
        if (stack[z] == 'T') {
            stack[z] = 'E';
            stack[z + 1] = '\0';
            printf("REDUCE E -> T\n");
            printAction();
        }
    }
}

int main() {
    printf("GRAMMAR:\nE -> E+T | T\nT -> T*F | F\nF -> (E) | id\n");
    printf("\nEnter the input string (end with $): ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");
    printf("----------------------------\n");

    strcpy(act, "SHIFT");

    while (i < strlen(input)) {
        temp[0] = input[i];
        temp[1] = '\0';
        strcat(stack, temp);
        input[i] = ' ';
        printf("%s\t%s$\t%s\n", stack, input + i + 1, act);
        i++;
        check();
    }

    if (strcmp(stack, "E") == 0)
        printf("\nACCEPTED: Input string is successfully parsed.\n");
    else
        printf("\nREJECTED: Invalid string.\n");

    return 0;
}