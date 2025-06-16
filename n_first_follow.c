#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

char productions[5][10] = {"S->AbCd", "A->a", "A->Cf", "C->Ee", "E->h"};
char first[5][MAX], follow[5][MAX];
int numProductions = 5;
char nonTerminals[5] = {'S', 'A', 'C', 'E'};
int ntCount = 4;

int findIndex(char symbol) {
    for (int i = 0; i < ntCount; i++)
        if (nonTerminals[i] == symbol)
            return i;
    return -1;
}

bool isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

void addToSet(char set[], char val) {
    for (int i = 0; set[i] != '\0'; i++)
        if (set[i] == val)
            return;
    int len = strlen(set);
    set[len] = val;
    set[len + 1] = '\0';
}

void computeFirst(char symbol, char result[]) {
    if (!isNonTerminal(symbol)) {
        addToSet(result, symbol);
        return;
    }

    int idx = findIndex(symbol);
    for (int i = 0; i < numProductions; i++) {
        if (productions[i][0] == symbol) {
            char next = productions[i][3];
            if (!isNonTerminal(next))
                addToSet(result, next);
            else {
                char temp[MAX] = "";
                computeFirst(next, temp);
                for (int j = 0; temp[j]; j++)
                    addToSet(result, temp[j]);
            }
        }
    }
}

void computeFollow(char symbol, char result[]) {
    if (symbol == 'S') addToSet(result, '$');  // Start symbol

    for (int i = 0; i < numProductions; i++) {
        char *body = strchr(productions[i], '>') + 1;
        for (int j = 0; body[j]; j++) {
            if (body[j] == symbol) {
                if (body[j + 1]) {
                    char next = body[j + 1];
                    char temp[MAX] = "";
                    computeFirst(next, temp);
                    for (int k = 0; temp[k]; k++)
                        if (temp[k] != 'ε')
                            addToSet(result, temp[k]);
                }
                if (!body[j + 1] || isNonTerminal(body[j + 1]) && strchr(follow[findIndex(productions[i][0])], symbol)) {
                    char temp[MAX] = "";
                    computeFollow(productions[i][0], temp);
                    for (int k = 0; temp[k]; k++)
                        addToSet(result, temp[k]);
                }
            }
        }
    }
}

int main() {
    
    for (int i = 0; i < ntCount; i++) {
        computeFirst(nonTerminals[i], first[i]);
    }

    
    for (int i = 0; i < ntCount; i++) {
        computeFollow(nonTerminals[i], follow[i]);
    }

    
    printf("FIRST sets:\n");
    for (int i = 0; i < ntCount; i++)
        printf("FIRST(%c) = { %s }\n", nonTerminals[i], first[i]);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < ntCount; i++)
        printf("FOLLOW(%c) = { %s }\n", nonTerminals[i], follow[i]);

    return 0;
}
