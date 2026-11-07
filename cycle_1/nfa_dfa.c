
#include <stdio.h>

int nfa_transition[10][5][10] = {0};
int dfa_states[100][10] = {0};
int dfa_transition[100][5];

int num_states, num_symbols;
char input_symbols[5];

// Find the index of an input symbol
int get_symbol_index(char symbol) {
    for (int i = 0; i < num_symbols; i++) {
        if (input_symbols[i] == symbol)
            return i;
    }
    return -1;
}

// Check whether two DFA states are equal
int is_same_state(int a[], int b[]) {
    for (int i = 0; i < num_states; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

// Add a new DFA state if it does not exist
int add_dfa_state(int new_state[], int *dfa_count) {

    for (int i = 0; i < *dfa_count; i++) {
        if (is_same_state(dfa_states[i], new_state))
            return i;
    }

    for (int i = 0; i < num_states; i++) {
        dfa_states[*dfa_count][i] = new_state[i];
    }

    (*dfa_count)++;

    return *dfa_count - 1;
}

int main() {

    int num_transitions, start_state, end_state;
    char symbol;

    // Input

    printf("Enter the number of states: ");
    scanf("%d", &num_states);

    printf("Enter the number of alphabet symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter the alphabet symbols: ");
    scanf("%s", input_symbols);

    printf("Enter the total number of transitions: ");
    scanf("%d", &num_transitions);

    printf("Enter transitions (from symbol to):\n");

    // Store NFA transitions

    for (int i = 0; i < num_transitions; i++) {

        scanf("%d %c %d", &start_state, &symbol, &end_state);

        int symbol_index = get_symbol_index(symbol);

        if (symbol_index != -1) {
            nfa_transition[start_state][symbol_index][end_state] = 1;
        }
    }

    // Initial DFA state = {q0}

    int dfa_count = 0;
    int current = 0;

    int start_set[10] = {0};
    start_set[0] = 1;

    add_dfa_state(start_set, &dfa_count);

    // Subset construction

    while (current < dfa_count) {

        for (int symbol_index = 0; symbol_index < num_symbols; symbol_index++) {

            int next_set[10] = {0};

            // Find all destination states

            for (int i = 0; i < num_states; i++) {

                if (dfa_states[current][i]) {

                    for (int j = 0; j < num_states; j++) {

                        if (nfa_transition[i][symbol_index][j]) {
                            next_set[j] = 1;
                        }
                    }
                }
            }

            // Check whether next state is empty

            int is_empty = 1;

            for (int i = 0; i < num_states; i++) {
                if (next_set[i]) {
                    is_empty = 0;
                    break;
                }
            }

            // Add DFA state and store transition

            if (!is_empty) {
                dfa_transition[current][symbol_index] =
                    add_dfa_state(next_set, &dfa_count);
            }
            else {
                dfa_transition[current][symbol_index] = -1;
            }
        }

        current++;
    }

    // Display DFA transition table

    printf("\n--- DFA Transition Table ---\n");

    printf("%-15s", "State");

    for (int i = 0; i < num_symbols; i++) {
        printf("%-15c", input_symbols[i]);
    }

    printf("\n---------------------------------------------\n");

    for (int i = 0; i < dfa_count; i++) {

        printf("{ ");

        for (int j = 0; j < num_states; j++) {
            if (dfa_states[i][j]) {
                printf("q%d ", j);
            }
        }

        printf("}       ");

        for (int symbol_index = 0; symbol_index < num_symbols; symbol_index++) {

            int destination = dfa_transition[i][symbol_index];

            if (destination == -1) {
                printf("{ - }        ");
            }
            else {

                printf("{ ");

                for (int j = 0; j < num_states; j++) {
                    if (dfa_states[destination][j]) {
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
