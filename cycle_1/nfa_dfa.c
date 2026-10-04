#include <stdio.h>

int nfa[10][5][10] = {0};
int dfa[100][10] = {0};
int dtrans[100][5];

int n, m;
char alpha[5];

int index(char ch) {
    for (int i = 0; i < m; i++)
        if (alpha[i] == ch)
            return i;
    return -1;
}

int same(int a[], int b[]) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

int add_state(int state[], int *count) {
    for (int i = 0; i < *count; i++)
        if (same(dfa[i], state))
            return i;

    for (int i = 0; i < n; i++)
        dfa[*count][i] = state[i];

    (*count)++;
    return *count - 1;
}

int main() {
    int t, from, to;
    char ch;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    printf("Enter alphabet: ");
    scanf("%s", alpha);

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to):\n");

    for (int i = 0; i < t; i++) {
        scanf("%d %c %d", &from, &ch, &to);

        int a = index(ch);
        if (a != -1)
            nfa[from][a][to] = 1;
    }

    int count = 0, done = 0;

    // Start DFA state = {q0}
    int start[10] = {0};
    start[0] = 1;
    add_state(start, &count);

    // Subset construction
    while (done < count) {

        for (int a = 0; a < m; a++) {

            int next[10] = {0};

            // Find all NFA destinations
            for (int i = 0; i < n; i++) {
                if (dfa[done][i]) {
                    for (int j = 0; j < n; j++) {
                        if (nfa[i][a][j])
                            next[j] = 1;
                    }
                }
            }

            // Add the new DFA state
            int empty = 1;

            for (int i = 0; i < n; i++)
                if (next[i])
                    empty = 0;

            if (!empty)
                dtrans[done][a] = add_state(next, &count);
            else
                dtrans[done][a] = -1;
        }

        done++;
    }

    // Print DFA table
    printf("\n--- DFA Transition Table ---\n");

    printf("%-15s", "State");
    for (int a = 0; a < m; a++)
        printf("%-15c", alpha[a]);

    printf("\n---------------------------------------------\n");

    for (int i = 0; i < count; i++) {

        printf("{");
        for (int j = 0; j < n; j++)
            if (dfa[i][j])
                printf("q%d ", j);
        printf("}       ");

        for (int a = 0; a < m; a++) {

            int to = dtrans[i][a];

            if (to == -1) {
                printf("%-15s", "{ - }");
            } else {
                printf("{");
                for (int j = 0; j < n; j++)
                    if (dfa[to][j])
                        printf("q%d ", j);
                printf("}       ");
            }
        }

        printf("\n");
    }

    return 0;
}
