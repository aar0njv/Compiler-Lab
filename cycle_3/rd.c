#include <stdio.h>
#include <string.h>

char input[100];
int i = 0;

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
    if (input[i] == '+') {
        i++;
        T();
        EP();
    }
}

void T() {
    F();
    TP();
}

void TP() {
    if (input[i] == '*') {
        i++;
        F();
        TP();
    }
}

void F() {
    if (input[i] == 'i') {
        i++;
    }
    else if (input[i] == '(') {
        i++;
        E();

        if (input[i] == ')')
            i++;
    }
}

int main() {
    printf("Grammar:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | epsilon\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | epsilon\n");
    printf("F  -> ( E ) | i\n\n");

    printf("Enter input: ");
    scanf("%s", input);

    E();

    if (i == strlen(input))
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}