#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int id;
    char lhs[5];
    char rhs[20];
} Instruction;

Instruction icr[MAX];
int n;

int gen[MAX][MAX] = {0};
int kill[MAX][MAX] = {0};
int in[MAX][MAX] = {0};
int out[MAX][MAX] = {0};

// Utility: find all definitions of a variable
void computeGenKill() {
    for (int i = 0; i < n; i++) {
        // GEN: current definition
        gen[i][i] = 1;

        // KILL: other definitions with same LHS
        for (int j = 0; j < n; j++) {
            if (i != j && strcmp(icr[i].lhs, icr[j].lhs) == 0)
                kill[i][j] = 1;
        }
    }
}

void printSet(int set[MAX]) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        if (set[i]) printf("%d ", i + 1);
    }
    printf("}");
}

void computeInOut() {
    bool changed = true;

    while (changed) {
        changed = false;
        for (int i = 0; i < n; i++) {
            int new_in[MAX] = {0};
            int new_out[MAX] = {0};

            // IN[n] = Union of OUT[p] for all predecessors
            if (i > 0) {
                for (int k = 0; k < n; k++)
                    new_in[k] = out[i - 1][k];  // linear flow
            }

            // OUT[n] = GEN[n] U (IN[n] - KILL[n])
            for (int k = 0; k < n; k++)
                new_out[k] = gen[i][k] | (new_in[k] && !kill[i][k]);

            // Check if changed
            for (int k = 0; k < n; k++) {
                if (in[i][k] != new_in[k] || out[i][k] != new_out[k]) {
                    changed = true;
                    in[i][k] = new_in[k];
                    out[i][k] = new_out[k];
                }
            }
        }
    }
}

int main() {
    printf("Enter number of ICR instructions: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter instruction %d (format: a = b + c): ", i + 1);
        scanf("%s = %[^\n]", icr[i].lhs, icr[i].rhs);
        icr[i].id = i + 1;
    }

    computeGenKill();
    computeInOut();

    printf("\nReaching Definitions:\n");
    for (int i = 0; i < n; i++) {
        printf("Instruction %d: %s = %s\n", icr[i].id, icr[i].lhs, icr[i].rhs);
        printf("  IN : "); printSet(in[i]);
        printf("\n  OUT: "); printSet(out[i]);
        printf("\n");
    }

    return 0;
}
