#include <stdio.h>
#include <string.h>

int main() {

    int num_states, num_symbols, num_transitions;
    int from, to;
    char symbol;
    char alphabet[10];

    int e_closure[20][20] = {0};

    int transition[20][10][20] = {0};

    int new_transition[20][10][20] = {0};


    // ---------------- INPUT ----------------

    printf("Enter the number of states: ");
    scanf("%d", &num_states);

    printf("Enter the number of alphabet symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter the alphabet symbols: ");
    scanf("%s", alphabet);


    // Every state is part of its own ε-closure
    for (int i = 0; i < num_states; i++) {
        e_closure[i][i] = 1;
    }

    printf("Enter the total number of transitions: ");
    scanf("%d", &num_transitions);

    printf("Enter transitions (from symbol to):\n");
    printf("Use 'e' for epsilon.\n");


    // Store all transitions
    for (int i = 0; i < num_transitions; i++) {
        scanf("%d %c %d", &from, &symbol, &to);
        if (symbol == 'e') {
            e_closure[from][to] = 1;
        } else {
            for (int j = 0; j < num_symbols; j++) {
                if (alphabet[j] == symbol) {
                    transition[from][j][to] = 1;
                    break;
                }
            }
        }
    }


    // -------- FIND ε-CLOSURES --------

    /*
       Floyd-Warshall algorithm is used here.

       If:
           i -> k
       and
           k -> j

       then:
           i -> j

       Therefore, we can find every state reachable
       using only epsilon transitions.
    */

    for (int middle = 0; middle < num_states; middle++) {

        for (int start = 0; start < num_states; start++) {

            for (int end = 0; end < num_states; end++) {

                if (e_closure[start][middle] &&
                    e_closure[middle][end]) {

                    e_closure[start][end] = 1;
                }
            }
        }
    }


    // -------- CONVERT ε-NFA TO NFA --------

    /*
       For every state and every input symbol:

       1. Find ε-closure of the current state.
       2. Follow the input symbol.
       3. Find ε-closure of the resulting states.

       Formula:

       δ'(q, a) =
       ε-closure( δ( ε-closure(q), a ) )
    */

    for (int state = 0; state < num_states; state++) {

        for (int symbol_index = 0 ; symbol_index < num_symbols ; symbol_index++) {

            for (int closure_state = 0 ; closure_state < num_states ; closure_state++) {
                if (!e_closure[state][closure_state])
                    continue;


                // Step 2:
                // Follow the input symbol

                for (int next_state = 0 ; next_state < num_states ; next_state++) {
                    if (!transition[closure_state][symbol_index][next_state])
                        continue;


                    // Step 3:
                    // Find ε-closure of the destination

                    for (int final_state = 0; final_state < num_states ; final_state++) {
                        if (e_closure[next_state][final_state]) {
                            new_transition[state][symbol_index][final_state] = 1;
                        }
                    }
                }
            }
        }
    }


    printf("\n--- NFA without Epsilon Transitions ---\n");

    printf("%-15s", "State");

    for (int i = 0; i < num_symbols; i++) {
        printf("%-15c", alphabet[i]);
    }

    printf("\n---------------------------------------------\n");


    for (int state = 0; state < num_states; state++) {

        printf("%-15s", state == 0 ? "q0" :
                        state == 1 ? "q1" :
                        state == 2 ? "q2" : "q3");

        for (int symbol_index = 0 ; symbol_index < num_symbols ; symbol_index++) {

            printf("{ ");

            int empty = 1;

            for (int destination = 0 ; destination < num_states ; destination++) {

                if (new_transition[state][symbol_index][destination]) {
                    printf("q%d ", destination);
                    empty = 0;
                }
            }

            if (empty)
                printf("-");

            printf("}        ");
        }

        printf("\n");
    }

    return 0;
}
