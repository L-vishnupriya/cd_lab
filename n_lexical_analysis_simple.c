#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char input[100], word[20];
    int i = 0, j;

    printf("Enter code: ");
    scanf("%[^\n]s", input); // Read one line

    while (input[i] != '\0') {
        // Skip spaces
        if (input[i] == ' ') {
            i++;
            continue;
        }

        // Identifier or keyword
        if (isalpha(input[i])) {
            j = 0;
            while (isalnum(input[i])) {
                word[j++] = input[i++];
            }
            word[j] = '\0';

            if (strcmp(word, "int") == 0 || strcmp(word, "float") == 0)
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }

        // Number
        else if (isdigit(input[i])) {
            j = 0;
            while (isdigit(input[i])) {
                word[j++] = input[i++];
            }
            word[j] = '\0';
            printf("Number: %s\n", word);
        }

        // Operators
        else if (input[i] == '+' || input[i] == '-' || input[i] == '=') {
            printf("Operator: %c\n", input[i]);
            i++;
        }

        // Skip unknown
        else {
            i++;
        }
    }

    return 0;
}
