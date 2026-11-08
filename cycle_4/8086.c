
#include <stdio.h>

int main() {
    char a, b, c, op;

    printf("Enter Three Address Code: ");
    scanf("%c=%c%c%c", &c, &a, &op, &b);

    printf("\n8086 Assembly Code:\n");

    printf("MOV AX, %c\n", a);

    if (op == '+')
        printf("ADD AX, %c\n", b);

    else if (op == '-')
        printf("SUB AX, %c\n", b);

    else if (op == '*') {
        printf("MOV BX, %c\n", b);
        printf("MUL BX\n");
    }

    else if (op == '/') {
        printf("MOV BX, %c\n", b);
        printf("MOV DX, 0\n");
        printf("DIV BX\n");
    }

    printf("MOV %c, AX\n", c);

    return 0;
}
