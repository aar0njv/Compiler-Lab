#include <stdio.h>
#include <string.h>
#include <ctype.h>

char grammar[20][20];
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
void findFirst(char result[], char symbol) {
    if (!isupper(symbol)) {
        add(result, symbol);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (grammar[i][0] != symbol)
            continue;
        
        if (grammar[i][2] == '#') {
            add(result, '#');
            continue;
        }

        for (int j = 2; grammar[i][j] != '\0'; j++) {
            char temp[20] = "";
            findFirst(temp, grammar[i][j]);
            for (int k = 0; temp[k] != '\0'; k++) {
                if (temp[k] != '#')
                    add(result, temp[k]);
            }

            if (strchr(temp, '#') == NULL)
                break;

            if (grammar[i][j + 1] == '\0')
                add(result, '#');
        }
    }
}

void findFollow(char result[], char symbol) {
    if (grammar[0][0] == symbol)
        add(result, '$');

    for (int i = 0; i < n; i++) {

        for (int j = 2; grammar[i][j] != '\0'; j++) {

            if (grammar[i][j] != symbol)
                continue;

            int next = j + 1;
            while (grammar[i][next] != '\0') {

                char temp[20] = "";
                findFirst(temp, grammar[i][next]);

                for (int k = 0; temp[k] != '\0'; k++) {
                    if (temp[k] != '#')
                        add(result, temp[k]);
                }
                if (strchr(temp, '#') == NULL)
                    break;
                next++;
            }

            if (grammar[i][next] == '\0' &&
                grammar[i][0] != symbol) {

                char temp[20] = "";
                findFollow(temp, grammar[i][0]);

                for (int k = 0; temp[k] != '\0'; k++)
                    add(result, temp[k]);
            }
        }
    }
}

int main() {

    char nonTerminals[20];
    int nonTerminalCount = 0;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (A=aB or A=#):\n");

    for (int i = 0; i < n; i++) {

        scanf("%s", grammar[i]);

        char symbol = grammar[i][0];

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
