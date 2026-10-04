#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = 0, i = 0;

void check() {
    int reduced = 1;

    while (reduced) {
        reduced = 0;

        if (top >= 2 && stack[top - 1] == 'i') {
            stack[top - 1] = 'E';
            printf("%-15s %-15s Reduce E -> i\n", stack, input + i);
            reduced = 1;
        }

        else if (top >= 4 && stack[top - 3] == 'E' &&
                 stack[top - 2] == '*' && stack[top - 1] == 'E') {
            stack[top - 3] = 'E';
            top -= 2;
            stack[top] = '\0';
            printf("%-15s %-15s Reduce E -> E*E\n", stack, input + i);
            reduced = 1;
        }

        else if (top >= 4 && stack[top - 3] == 'E' &&
                 stack[top - 2] == '+' && stack[top - 1] == 'E') {
            if (input[i] == '*')
                break;

            stack[top - 3] = 'E';
            top -= 2;
            stack[top] = '\0';
            printf("%-15s %-15s Reduce E -> E+E\n", stack, input + i);
            reduced = 1;
        }
    }
}

int main() {
    printf("Grammar:\n");
    printf("E -> E+E\n");
    printf("E -> E*E\n");
    printf("E -> i\n\n");

    printf("Enter input string (e.g., i+i*i): ");
    scanf("%s", input);

    strcat(input, "$");

    printf("\n%-15s %-15s %s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------\n");

    stack[0] = '$';
    stack[1] = '\0';
    top = 1;

    while (i < strlen(input) - 1) {
        stack[top] = input[i];
        stack[top + 1] = '\0';
        top++;

        printf("%-15s %-15s Shift\n", stack, input + i + 1);
        i++;

        check();
    }

    if (stack[1] == 'E' && stack[2] == '\0' && input[i] == '$') {
        printf("\n%-15s %-15s Accepted\n", stack, "$");
    } else {
        printf("\n%-15s %-15s Rejected: Syntax Error\n",
               stack, input + i);
    }

    return 0;
}