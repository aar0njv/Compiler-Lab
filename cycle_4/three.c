
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0, temp = 1;

// Function declarations

void expression(char result[]);
void term(char result[]);
void factor(char result[]);


// Generate intermediate code
void generate(char left[], char op, char right[], char result[]) {
    char t[10];
    sprintf(t, "t%d", temp++);
    printf("%s = %s %c %s\n", t, left, op, right);
    strcpy(result, t);
}


// Handle operands and brackets

void factor(char result[]) {
    int i = 0;
    if (input[pos] == '(') {
        pos++;
        expression(result);
        if (input[pos] == ')')
            pos++;
    }
    else {
        while (isalnum(input[pos]) || input[pos] == '_') {
            result[i++] = input[pos++];
        }
        result[i] = '\0';
    }
}


// Handle multiplication and division

void term(char result[]) {
    char left[20], right[20];
    char op;

    factor(left);

    while (input[pos] == '*' || input[pos] == '/') {
        op = input[pos++];
        factor(right);
        generate(left, op, right, left);
    }
    strcpy(result, left);
}


// Handle addition and subtraction

void expression(char result[]) {
    char left[20], right[20];
    char op;
    term(left);

    while (input[pos] == '+' || input[pos] == '-') {
        op = input[pos++];
        term(right);
        generate(left, op, right, left);
    }
    strcpy(result, left);
}


int main() {

    char result[20];
    char lhs[20] = "";
    int i = 0;

    // Input
    printf("Enter an expression: ");
    scanf("%99s", input);

    // Check assignment
    if (strchr(input, '=') != NULL) {

        while (isalnum(input[pos]) || input[pos] == '_') {
            lhs[i++] = input[pos++];
        }
        lhs[i] = '\0';
        if (input[pos] != '=') {
            printf("Invalid Expression\n");
            return 0;
        }
        pos++;
    }

    // Generate Three Address Code
    expression(result);

    // Check for invalid remaining characters
    if (input[pos] != '\0') {
        printf("Invalid Expression\n");
        return 0;
    }

    // Display final assignment
    if (lhs[0] != '\0') {
        printf("%s = %s\n", lhs, result);
    }
    else {
        printf("Result = %s\n", result);
    }

    return 0;
}
