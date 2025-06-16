#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char op;
    struct Node *left, *right;
    char val[10];  // for operand leaf nodes or unique key
} Node;

Node* nodeList[MAX];
int nodeCount = 0;

// Check if node already exists (for common subexpression)
Node* findOrCreate(char op, Node* left, Node* right, const char* val) {
    for (int i = 0; i < nodeCount; i++) {
        if (nodeList[i]->op == op &&
            nodeList[i]->left == left &&
            nodeList[i]->right == right &&
            strcmp(nodeList[i]->val, val) == 0)
            return nodeList[i];
    }

    Node* n = (Node*)malloc(sizeof(Node));
    n->op = op;
    n->left = left;
    n->right = right;
    strcpy(n->val, val);
    nodeList[nodeCount++] = n;
    return n;
}


Node* buildDAG(char expr[], int* i) {
    if (expr[*i] == '(') {
        (*i)++;  // skip '('
        Node* left = buildDAG(expr, i);
        char op = expr[(*i)++];
        Node* right = buildDAG(expr, i);
        (*i)++;  // skip ')'
        char dummy[2] = "";  // internal nodes don't use val
        return findOrCreate(op, left, right, dummy);
    } else {
        char val[2] = {expr[*i], '\0'};
        (*i)++;
        return findOrCreate(' ', NULL, NULL, val);
    }
}


void printDAG() {
    printf("DAG Nodes:\n");
    for (int i = 0; i < nodeCount; i++) {
        Node* n = nodeList[i];
        printf("Node %d: ", i);
        if (n->op == ' ')
            printf("Operand '%s'\n", n->val);
        else {
            printf("Operator '%c' -> Left: '%s', Right: '%s'\n",
                n->op,
                n->left->op == ' ' ? n->left->val : "(op)",
                n->right->op == ' ' ? n->right->val : "(op)");
        }
    }
}

int main() {
    char expr[MAX];
    printf("Enter fully parenthesized expression: ");
    scanf("%s", expr);

    int i = 0;
    Node* root = buildDAG(expr, &i);

    printf("\n--- DAG Output ---\n");
    printDAG();

    return 0;
}
