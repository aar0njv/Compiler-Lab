#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];
int n;

/* Add symbol to a set if it is not already present */
void add(char set[], char ch) {
    if (strchr(set, ch) == NULL) {
        int len = strlen(set);
        set[len] = ch;
        set[len + 1] = '\0';
    }
}

/* Find FIRST of a symbol */
void findFirst(char first[], char symbol) {
    if (!isupper(symbol)) {
        add(first, symbol);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] != symbol)
            continue;
        
        if (prod[i][2] == 'e') {
            add(first, 'e');
            continue;
        }

        for (int j = 2; prod[i][j] != '\0'; j++) {
            char temp[20] = "";
            findFirst(temp, prod[i][j]);
            for (int k = 0; temp[k] != '\0'; k++) {
                if (temp[k] != 'e')
                    add(first, temp[k]);
            }

            if (strchr(temp, 'e') == NULL)
                break;

            if (prod[i][j + 1] == '\0')
                add(first, 'e');
        }
    }
}

void findFollow(char follow[], char symbol) {
    if (prod[0][0] == symbol)
        add(follow, '$');

    for (int i = 0; i < n; i++) {

        for (int j = 2; prod[i][j] != '\0'; j++) {

            if (prod[i][j] != symbol)
                continue;

            int next = j + 1;
            while (prod[i][next] != '\0') {

                char temp[20] = "";
                findFirst(temp, prod[i][next]);

                for (int k = 0; temp[k] != '\0'; k++) {
                    if (temp[k] != 'e')
                        add(follow, temp[k]);
                }
                if (strchr(temp, 'e') == NULL)
                    break;
                next++;
            }

            if (prod[i][next] == '\0' && prod[i][0] != symbol) {

                char temp[20] = "";
                findFollow(temp, prod[i][0]);

                for (int k = 0; temp[k] != '\0'; k++)
                    add(follow, temp[k]);
            }
        }
    }
}

int main() {

    char nonTerminals[20];
    int nonTerminalCount = 0;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (A=aB or A=e):\n");

    for (int i = 0; i < n; i++) {

        scanf("%s", prod[i]);

        char symbol = prod[i][0];

        if (strchr(nonTerminals, symbol) == NULL) {
            nonTerminals[nonTerminalCount++] = symbol;
        }
    }

    printf("\n--- FIRST and FOLLOW ---\n\n");

    for (int i = 0; i < nonTerminalCount; i++) {

        char first[20] = "";
        char follow[20] = "";

        findFirst(first, nonTerminals[i]);
        findFollow(follow, nonTerminals[i]);

        printf("FIRST(%c)  = { ", nonTerminals[i]);

        for (int j = 0; first[j] != '\0'; j++)
            printf("%c ", first[j]);

        printf("}\n");

        printf("FOLLOW(%c) = { ", nonTerminals[i]);

        for (int j = 0; follow[j] != '\0'; j++)
            printf("%c ", follow[j]);

        printf("}\n\n");
    }

    return 0;
}
