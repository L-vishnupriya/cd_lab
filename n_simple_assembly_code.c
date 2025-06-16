#include <stdio.h>
#include <string.h>

void generateAssembly(char *tac, char *asmCode) {
    char result[10], op1[10], op[3], op2[10], label[10];

    // Assignment operations: t = a + b
    if (sscanf(tac, "%s = %s %s %s", result, op1, op, op2) == 4) {
        sprintf(asmCode + strlen(asmCode), "MOV AX, %s\n", op1);
        
        if (strcmp(op, "+") == 0)
            sprintf(asmCode + strlen(asmCode), "ADD AX, %s\n", op2);
        else if (strcmp(op, "-") == 0)
            sprintf(asmCode + strlen(asmCode), "SUB AX, %s\n", op2);
        else if (strcmp(op, "*") == 0) {
            sprintf(asmCode + strlen(asmCode), "MOV BX, %s\n", op2);
            strcat(asmCode, "MUL BX\n");
        }
        sprintf(asmCode + strlen(asmCode), "MOV %s, AX\n\n", result);
    }

    // Conditional jumps: if a > b goto 10
    else if (sscanf(tac, "if %s %s %s goto %s", op1, op, op2, label) == 4) {
        sprintf(asmCode + strlen(asmCode), "MOV AX, %s\n", op1);
        sprintf(asmCode + strlen(asmCode), "CMP AX, %s\n", op2);

        if (strcmp(op, "==") == 0)
            sprintf(asmCode + strlen(asmCode), "JE L%s\n\n", label);
        else if (strcmp(op, ">") == 0)
            sprintf(asmCode + strlen(asmCode), "JG L%s\n\n", label);
        else if (strcmp(op, "<") == 0)
            sprintf(asmCode + strlen(asmCode), "JL L%s\n\n", label);
    }

    // Unconditional jump: goto 20
    else if (sscanf(tac, "goto %s", label) == 1) {
        sprintf(asmCode + strlen(asmCode), "JMP L%s\n\n", label);
    }
}

int main() {
    char tac[100];
    char asmCode[1000] = "";

    printf("Enter TAC lines (blank line to finish):\n");
    while (fgets(tac, sizeof(tac), stdin)) {
        if (tac[0] == '\n') break;
        tac[strcspn(tac, "\n")] = 0;
        generateAssembly(tac, asmCode);
    }

    printf("\nGenerated Assembly Code:\n%s", asmCode);
    return 0;
}
