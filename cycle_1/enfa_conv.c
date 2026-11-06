
#include <stdio.h>
#include <string.h>

int main() {

    int states, symbols, transitions;
    int from, to;
    char input;
    char alphabet[10];

    int closure[20][20] = {0};
    int nfa[20][10][20] = {0};
    int result[20][10][20] = {0};


    // Input

    printf("Enter the number of states: ");
    scanf("%d", &states);

    printf("Enter the number of alphabet symbols: ");
    scanf("%d", &symbols);

    printf("Enter the alphabet symbols: ");
    scanf("%s", alphabet);


    // Every state belongs to its own epsilon closure

    for (int i = 0; i < states; i++) {
        closure[i][i] = 1;
    }

    printf("Enter the total number of transitions: ");
    scanf("%d", &transitions);

    printf("Enter transitions (from symbol to):\n");
    printf("Use 'e' for epsilon.\n");


    // Store transitions

    for (int i = 0; i < transitions; i++) {
        scanf("%d %c %d", &from, &input, &to);
        if (input == 'e') {
            closure[from][to] = 1;
        }
        else {
            for (int j = 0; j < symbols; j++) {

                if (alphabet[j] == input) {
                    nfa[from][j][to] = 1;
                    break;
                }
            }
        }
    }
    // Find epsilon closures using Floyd-Warshall
    for (int k = 0; k < states; k++) {
        for (int i = 0; i < states; i++) {
            for (int j = 0; j < states; j++) {
                if (closure[i][k] && closure[k][j]) {
                    closure[i][j] = 1;
                }
            }
        }
    }
    // Convert epsilon-NFA to NFA
    for (int state = 0; state < states; state++) {
        for (int symbol = 0; symbol < symbols; symbol++) {
            for (int c = 0; c < states; c++) {
                if (closure[state][c]) {
                    for (int next = 0; next < states; next++) {
                        if (nfa[c][symbol][next]) {
                            for (int final = 0; final < states; final++) {
                                if (closure[next][final]) {
                                    result[state][symbol][final] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    // Display NFA transition table

    printf("\n--- NFA without Epsilon Transitions ---\n");

    printf("%-15s", "State");

    for (int i = 0; i < symbols; i++) {
        printf("%-15c", alphabet[i]);
    }

    printf("\n---------------------------------------------\n");


    for (int state = 0; state < states; state++) {
        printf("q%-14d", state);
        for (int symbol = 0; symbol < symbols; symbol++) {
            printf("{ ");
            int empty = 1;
            for (int dest = 0; dest < states; dest++) {
                if (result[state][symbol][dest]) {
                    printf("q%d ", dest);
                    empty = 0;
                }
            }
            if (empty) {
                printf("-");
            }
            printf("}        ");
        }
        printf("\n");
    }
    return 0;
}
