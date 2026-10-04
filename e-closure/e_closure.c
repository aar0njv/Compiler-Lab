
#include <stdio.h>

int n;
int epsilon_graph[20][20];
int visited[20];

void find_closure(int state) {
  printf("q%d ", state);
  visited[state] = 1;

  for (int i = 0; i < n; i++) {
    if (epsilon_graph[state][i] == 1 && !visited[i]) {
      find_closure(i);
    }
  }
}

int main() {
    int transitions, u, v;
    char symbol;

    printf("Enter the number of states: ");
    scanf("%d", &n);

    for (int i=0 ; i<n ; i++){
        for (int j=0 ; j<n ; j++){
            epsilon_graph[i][j] = 0;
        }
    }

    printf("Enter the total number of transitions: ");
    scanf("%d", &transitions);

    printf("Enter the transition: from_state symbol to_state\n");
    printf("Use 'e' for epsilon, states should be integers from 0\n");

    for (int i=0 ; i<transitions ; i++) {
        scanf("%d %c %d", &u, &symbol, &v);

        if (symbol == 'e') {
            epsilon_graph[u][v] = 1;
        }
    }

    printf("--------Epsilon Closure--------\n");

    for (int i=0 ; i<n ; i++){
        for (int j=0 ; j<n ; j++) {
            visited[j] = 0;
        }

        printf("e-closure of q%d: { ", i);
        find_closure(i);
        printf("}\n");
    }

    return 0;
}
