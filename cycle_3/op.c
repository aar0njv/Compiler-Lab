// E -> E+E / E*E / id

#include <stdio.h>
#include <string.h>

char table[4][4] = {
    //   +    *    i    $
    {'>', '<', '<', '>'},  // +
    {'>', '>', '<', '>'},  // *
    {'>', '>', 'e', '>'},  // i
    {'<', '<', '<', 'A'}   // $
};

int get_index(char ch) {
    if (ch == '+')
        return 0;
    if (ch == '*')
        return 1;
    if (ch == 'i')
        return 2;
    if (ch == '$')
        return 3;

    return -1;
}

int main() {
    char input[30], stack[30];
    int i = 0, top = 0;

    printf("Enter input (use i for id and $ at end): ");
    scanf("%s", input);

    stack[0] = '$';
    stack[1] = '\0';

    printf("\n%-15s %-15s %s\n", "Stack", "Input", "Action");
    printf("--------------------------------------------\n");

    while (1) {
        int k = top;

        // Find topmost terminal
        while (k >= 0 && stack[k] == 'E')
            k--;

        char a = stack[k];
        char b = input[i];

        int row = get_index(a);
        int col = get_index(b);

        if (row == -1 || col == -1) {
            printf("Invalid symbol\n");
            break;
        }

        char rel = table[row][col];

        printf("%-15s %-15s ", stack, &input[i]);

        // Shift
        if (rel == '<' || rel == '=') {
            printf("Shift\n");

            stack[++top] = b;
            stack[top + 1] = '\0';

            i++;
        }

        // Reduce
        else if (rel == '>') {
            printf("Reduce\n");

            if (stack[top] == 'i') {
                stack[top] = 'E';
            }
            else if (top >= 2 &&
                     stack[top - 2] == 'E' &&
                     (stack[top - 1] == '+' || stack[top - 1] == '*') &&
                     stack[top] == 'E') {

                top -= 2;
                stack[top] = 'E';
                stack[top + 1] = '\0';
            }
            else {
                printf("Syntax Error\n");
                break;
            }
        }

        // Accept
        else if (rel == 'A') {
            printf("Accepted\n");
            break;
        }

        // Error
        else {
            printf("Syntax Error\n");
            break;
        }
    }

    return 0;
}