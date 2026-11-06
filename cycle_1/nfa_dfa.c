
#include <stdio.h>

int nfa[10][5][10] = {0};
int dfa[100][10] = {0};
int transition[100][5];

int states, symbols;
char alphabet[5];

int get_index(char input) {
    for (int i = 0; i < symbols; i++) {
        if (alphabet[i] == input)
            return i;
    }
    return -1;
}

// Check whether two DFA states are equal
int is_same(int a[], int b[]) {
    for (int i = 0; i < states; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

// Add a new DFA state if it does not exist
int add_state(int new_state[], int *count) {
    for (int i = 0; i < *count; i++) {
        if (is_same(dfa[i], new_state))
            return i;
    }
    for (int i = 0; i < states; i++) {
        dfa[*count][i] = new_state[i];
    }
    (*count)++;
    return *count - 1;
}

int main() {
    int transitions, from, to;
    char input;

    // Input

    printf("Enter the number of states: ");
    scanf("%d", &states);

    printf("Enter the number of alphabet symbols: ");
    scanf("%d", &symbols);

    printf("Enter the alphabet symbols: ");
    scanf("%s", alphabet);

    printf("Enter the total number of transitions: ");
    scanf("%d", &transitions);

    printf("Enter transitions (from symbol to):\n");

    // Store NFA transitions

    for (int i = 0; i < transitions; i++) {
        scanf("%d %c %d", &from, &input, &to);
        int symbol = get_index(input);
        if (symbol != -1) {
            nfa[from][symbol][to] = 1;
        }
    }

    // Start DFA state = {q0}
    int count = 0;
    int done = 0;

    int start[10] = {0};
    start[0] = 1;

    add_state(start, &count);

    // Subset construction

    while (done < count) {
        for (int symbol = 0; symbol < symbols; symbol++) {
            int next[10] = {0};
            
            // Find all destination states
            for (int i = 0; i < states; i++) {
                if (dfa[done][i]) {
                    for (int j = 0; j < states; j++) {
                        if (nfa[i][symbol][j]) {
                            next[j] = 1;
                        }
                    }
                }
            }


            // Add the new DFA state

            int empty = 1;

            for (int i = 0; i < states; i++) {
                if (next[i]) {
                    empty = 0;
                    break;
                }
            }

            if (!empty) {
                transition[done][symbol] = add_state(next, &count);
            }
            else {
                transition[done][symbol] = -1;
            }
        }

        done++;
    }


    // Display DFA transition table

    printf("\n--- DFA Transition Table ---\n");
    printf("%-15s", "State");

    for (int i = 0; i < symbols; i++) {
        printf("%-15c", alphabet[i]);
    }

    printf("\n---------------------------------------------\n");


    for (int i = 0; i < count; i++) {
        printf("{ ");
        for (int j = 0; j < states; j++) {
            if (dfa[i][j]) {
                printf("q%d ", j);
            }
        }

        printf("}       ");

        for (int symbol = 0; symbol < symbols; symbol++) {
            int dest = transition[i][symbol];
            if (dest == -1) {
                printf("{ - }        ");
            }
            else {
                printf("{ ");
                for (int j = 0; j < states; j++) {
                    if (dfa[dest][j]) {
                        printf("q%d ", j);
                    }
                }
                printf("}       ");
            }
        }

        printf("\n");
    }
    return 0;
}
