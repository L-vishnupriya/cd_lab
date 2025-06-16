#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

struct Symbol {
    char name[20];
    char type[10];
    char scope[10];
    char kind[10];
    int address;
};

struct Symbol table[SIZE];
int count = 0;
int currentAddress = 1000;

int exists(char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0)
            return 1;
    }
    return 0;
}

void insert(char *name) {
    if (!exists(name)) {
        strcpy(table[count].name, name);
        strcpy(table[count].type, "int");      // default type
        strcpy(table[count].scope, "global");  // default scope
        strcpy(table[count].kind, "var");      // default kind
        table[count].address = currentAddress;
        currentAddress += 4;
        count++;
    }
}

void display() {
    printf("\n%-10s %-10s %-10s %-10s %-10s\n", "Name", "Type", "Scope", "Kind", "Address");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-10s %-10s %-10s %-10d\n",
            table[i].name,
            table[i].type,
            table[i].scope,
            table[i].kind,
            table[i].address);
    }
}

int main() {
    char input[100], temp[20];
    int i = 0, j;

    printf("Enter expression (end with $): ");
    scanf("%[^\n]s", input);  // read until newline

    while (input[i] != '\0' && input[i] != '$') {
        if (isalpha(input[i])) {
            j = 0;
            while (isalnum(input[i])) {
                temp[j++] = input[i++];
            }
            temp[j] = '\0';
            insert(temp);
        } else {
            i++; // skip operators and symbols
        }
    }

    display();

    return 0;
}
