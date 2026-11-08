
#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;
int error = 0;

void E();
void EP();
void T();
void TP();
void F();

void E() {
    T();
    EP();
}

void EP() {
    if (input[pos] == '+') {
        pos++;
        T();
        EP();
    }
}

void T() {
    F();
    TP();
}

void TP() {
    if (input[pos] == '*') {
        pos++;
        F();
        TP();
    }
}

void F() {
    if (input[pos] == 'i') {
        pos++;
    }
    else if (input[pos] == '(') {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            error = 1;
    }
    else {
        error = 1;
    }
}

int main() {
    printf("Grammar:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | epsilon\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | epsilon\n");
    printf("F  -> ( E ) | i\n");

    printf("\nEnter input: ");
    scanf("%99s", input);

    E();

    if (pos != strlen(input))
        error = 1;

    if (error == 0)
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}
