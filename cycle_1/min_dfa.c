#include <stdio.h>

int trans[20][10];
int final[20];
int mark[20][20];
int group[20];

int n, m;
char alpha[10];

int index(char ch) {
    for (int i = 0; i < m; i++)
        if (alpha[i] == ch)
            return i;
    return -1;
}

int main() {
    int t, f, from, to;
    char ch;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of alphabet symbols: ");
    scanf("%d", &m);

    printf("Enter alphabet: ");
    scanf("%s", alpha);

    printf("Enter number of final states: ");
    scanf("%d", &f);

    printf("Enter final states: ");
    for (int i = 0; i < f; i++) {
        int s;
        scanf("%d", &s);
        final[s] = 1;
    }

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to):\n");

    for (int i = 0; i < t; i++) {
        scanf("%d %c %d", &from, &ch, &to);

        int a = index(ch);
        if (a != -1)
            trans[from][a] = to;
    }

    // Step 1: Mark final/non-final pairs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (final[i] != final[j])
                mark[i][j] = mark[j][i] = 1;
        }
    }

    // Step 2: Mark distinguishable pairs
    int change = 1;

    while (change) {
        change = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {

                if (mark[i][j])
                    continue;

                for (int a = 0; a < m; a++) {
                    int x = trans[i][a];
                    int y = trans[j][a];

                    if (mark[x][y]) {
                        mark[i][j] = mark[j][i] = 1;
                        change = 1;
                        break;
                    }
                }
            }
        }
    }

    // Step 3: Create equivalence groups
    for (int i = 0; i < n; i++)
        group[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {

            if (!mark[i][j]) {
                for (int k = 0; k < n; k++)
                    if (group[k] == group[i])
                        group[k] = group[j];
            }
        }
    }

    // Step 4: Print minimized DFA
    printf("\n--- Minimized DFA ---\n");

    for (int i = 0; i < n; i++) {

        if (group[i] != i)
            continue;

        printf("{ ");
        for (int j = 0; j < n; j++)
            if (group[j] == i)
                printf("q%d ", j);
        printf("}");

        if (final[i])
            printf("*");

        for (int a = 0; a < m; a++) {
            int target = trans[i][a];

            printf("  %c -> { ", alpha[a]);

            for (int j = 0; j < n; j++)
                if (group[j] == group[target])
                    printf("q%d ", j);

            printf("}");
        }

        printf("\n");
    }

    return 0;
}
