// Experiment 8
// Program for Predictive Parser using Stack and Parsing Table

#include <stdio.h>
#include <string.h>

char stack[30], input[30];

// Parsing table for the grammar:
// E -> T E'
// E' -> + T E' | ε
// T -> F T'
// T' -> * F T' | ε
// F -> ( E ) | i

char table[5][6][10] = {
    //    i        +       *       (        )      $
    {"TE_", "",    "",    "TE_",  "",     ""}, // E
    {"",    "+TE_", "",   "",     "ε",    "ε"}, // E'
    {"FT_", "",    "",    "FT_",  "",     ""}, // T
    {"",    "ε",   "*FT_","",     "ε",    "ε"}, // T'
    {"i",   "",    "",    "(E)",  "",     ""}  // F
};

int getRow(char symbol) {
    switch(symbol) {
        case 'E': return 0;
        case '_': return 1; // E'
        case 'T': return 2;
        case '^': return 3; // T'
        case 'F': return 4;
        default: return -1;
    }
}

int getColumn(char symbol) {
    switch(symbol) {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

int main() {
    char temp[30];
    int top = 1, i = 0;

    printf("Enter the input string (end with $): ");
    scanf("%s", input);

    stack[0] = '$';
    stack[1] = 'E';

    printf("\nStack\t\tInput\t\tAction\n\n");

    while (stack[top] != '$') {
        printf("%s\t\t%s\t\t", stack, &input[i]);

        if (stack[top] == input[i]) {
            printf("Match %c\n", input[i]);
            top--;
            i++;
        } else if (getRow(stack[top]) != -1 && getColumn(input[i]) != -1) {
            strcpy(temp, table[getRow(stack[top])][getColumn(input[i])]);

            if (strcmp(temp, "") == 0) {
                printf("Error\n");
                break;
            } else if (strcmp(temp, "ε") == 0) {
                printf("%c -> ε\n", stack[top]);
                top--;
            } else {
                printf("%c -> %s\n", stack[top], temp);
                top--;
                for (int j = strlen(temp) - 1; j >= 0; j--) {
                    top++;
                    stack[top] = temp[j];
                }
                stack[top + 1] = '\0';
            }
        } else {
            printf("Error\n");
            break;
        }
    }

    if (stack[top] == '$' && input[i] == '$') {
        printf("$\t\t$\t\tAccepted\n");
    } else {
        printf("Parsing Failed\n");
    }

    return 0;
}

/*
Sample Input/Output:

Input:
i+i*i$

Output:
Stack       Input       Action
E           i+i*i$      E -> TE_
TE_         i+i*i$      T -> FT_
FT_E_       i+i*i$      F -> i
T_E_        +i*i$       Match i
E_          +i*i$       E' -> +TE_
+TE_        +i*i$       Match +
TE_         i*i$        T -> FT_
FT_E_       i*i$        F -> i
T_E_        *i$         Match i
E_          *i$         E' -> ε
T_          *i$         T' -> *FT_
*FT_        *i$         Match *
FT_         i$          F -> i
T_          $           Match i
E_          $           ε
$           $           Accepted
*/
