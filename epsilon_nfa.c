// Selsabil Maâche - Group 2 - Réseaux
// Rahma Khalfoune - Group 2 - Réseaux
#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 20
#define MAX_TRANS 50
#define ALPHABET 2   // a , b

typedef struct {
    int from;
    int symbol;   // 0=a , 1=b , -1=epsilon
    int to;
} Transition;

/* Global variables */
int n_states, n_trans;
Transition trans[MAX_TRANS];

int final_states[MAX_STATES];
int new_final[MAX_STATES];

int eclosure[MAX_STATES][MAX_STATES];
int ecount[MAX_STATES];

/* ---------- Task 1: Read NFA ---------- */
void readNFA() {
    int i;
    printf("Number of states: ");
    scanf("%d", &n_states);

    printf("Number of transitions: ");
    scanf("%d", &n_trans);

    for (i = 0; i < n_trans; i++) {
        printf("Transition %d (from symbol to) [a=0, b=1, e=-1]: ", i + 1);
        scanf("%d %d %d", &trans[i].from, &trans[i].symbol, &trans[i].to);
    }

    printf("Final states (1 if final, 0 otherwise):\n");
    for (i = 0; i < n_states; i++)
        scanf("%d", &final_states[i]);
}

/* ---------- Task 2: Epsilon Closure ---------- */
void epsilonClosure(int s, int visited[]) {
    int i;
    visited[s] = 1;
    eclosure[s][ecount[s]++] = s;

    for (i = 0; i < n_trans; i++) {
        if (trans[i].from == s && trans[i].symbol == -1) {
            if (!visited[trans[i].to])
                epsilonClosure(trans[i].to, visited);
        }
    }
}

void computeEclosures() {
    int i;
    for (i = 0; i < n_states; i++) {
        int visited[MAX_STATES] = {0};
        ecount[i] = 0;
        epsilonClosure(i, visited);
    }
}

/* ---------- Task 3: New Transitions ---------- */
void computeNewTransitions() {
    int i, j, a, t, k;

    printf("\nNew transitions (without epsilon):\n");

    for (i = 0; i < n_states; i++) {
        for (a = 0; a < ALPHABET; a++) {

            int marked[MAX_STATES] = {0};

            for (j = 0; j < ecount[i]; j++) {
                int p = eclosure[i][j];

                for (t = 0; t < n_trans; t++) {
                    if (trans[t].from == p && trans[t].symbol == a) {
                        int q = trans[t].to;

                        for (k = 0; k < ecount[q]; k++) {
                            int r = eclosure[q][k];

                            if (!marked[r]) {
                                marked[r] = 1;
                                printf("(%d, %c) -> %d\n", i, a + 'a', r);
                            }
                        }
                    }
                }
            }
        }
    }
}

/* ---------- Task 4: New Final States ---------- */
void computeNewFinalStates() {
    int i, j;

    for (i = 0; i < n_states; i++) {
        new_final[i] = 0;
        for (j = 0; j < ecount[i]; j++) {
            if (final_states[eclosure[i][j]]) {
                new_final[i] = 1;
                break;
            }
        }
    }
}

/* ---------- Task 5: Display Automaton ---------- */
void displayAutomaton() {
    int i;
    printf("\nInitial state: 0\n");

    printf("\nNew Final States:\n");
    for (i = 0; i < n_states; i++) {
        if (new_final[i])
            printf("State %d is final\n", i);
    }
}

/* ---------- Main ---------- */
int main() {

    readNFA();               // Task 1
    computeEclosures();      // Task 2
    computeNewTransitions(); // Task 3
    computeNewFinalStates(); // Task 4
    displayAutomaton();      // Task 5

    return 0;
}
