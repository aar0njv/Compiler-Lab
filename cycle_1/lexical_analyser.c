#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };

    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }

    return 0;
}

int main() {
    int ch, i, j = 0;
    char buffer[30];
    char operators[] = "+-*/%=";

    printf("Enter C code:\n");

    printf("%-20s%-20s\n", "Token", "Type");
    printf("----------------------------------------\n");

    while ((ch = getchar()) != EOF) {

        // Ignore spaces, tabs and newlines
        if (isspace(ch))
            continue;

        // Check for operators
        for (i = 0; i < 6; i++) {
            if (ch == operators[i]) {
                printf("%-20c%-20s\n", ch, "Operator");
                break;
            }
        }

        // Check for special characters
        if (ch == ';' || ch == ',' || ch == '{' ||
            ch == '}' || ch == '(' || ch == ')') {
            printf("%-20c%-20s\n", ch, "Special Character");
        }

        // Check for keywords and identifiers
        if (isalpha(ch)) {
            buffer[j++] = ch;
            ch = getchar();

            while (isalnum(ch)) {
                buffer[j++] = ch;
                ch = getchar();
            }

            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer))
                printf("%-20s%-20s\n", buffer, "Keyword");
            else
                printf("%-20s%-20s\n", buffer, "Identifier");

            ungetc(ch, stdin);
        }

        // Check for constants
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            ch = getchar();

            while (isdigit(ch)) {
                buffer[j++] = ch;
                ch = getchar();
            }

            buffer[j] = '\0';
            j = 0;

            printf("%-20s%-20s\n", buffer, "Constant");

            ungetc(ch, stdin);
        }
    }

    return 0;
}
