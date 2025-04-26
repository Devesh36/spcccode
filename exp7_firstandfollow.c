// Experiment 7
// Program to compute FIRST and FOLLOW sets

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

typedef struct {
    char lhs;
    char rhs[MAX_SYMBOLS];
} Rule;

int numRules;
Rule rules[MAX_RULES];
char firstSets[26][MAX_SYMBOLS];
char followSets[26][MAX_SYMBOLS];

int isTerminal(char symbol) {
    return !isupper(symbol);
}

void addToSet(char *set, char symbol) {
    if (!strchr(set, symbol)) {
        int len = strlen(set);
        set[len] = symbol;
        set[len + 1] = '\0';
    }
}

void computeFirst(char nonTerminal) {
    for (int i = 0; i < numRules; i++) {
        if (rules[i].lhs == nonTerminal) {
            char *rhs = rules[i].rhs;
            if (isTerminal(rhs[0])) {
                addToSet(firstSets[nonTerminal - 'A'], rhs[0]);
            } else {
                computeFirst(rhs[0]);
                char *rhsFirstSet = firstSets[rhs[0] - 'A'];
                for (int j = 0; rhsFirstSet[j] != '\0'; j++) {
                    addToSet(firstSets[nonTerminal - 'A'], rhsFirstSet[j]);
                }
            }
        }
    }
}

void computeFollow() {
    addToSet(followSets[rules[0].lhs - 'A'], '$');

    int changes = 1;
    while (changes) {
        changes = 0;
        for (int i = 0; i < numRules; i++) {
            char lhs = rules[i].lhs;
            char *rhs = rules[i].rhs;
            int len = strlen(rhs);

            for (int j = 0; j < len; j++) {
                if (isupper(rhs[j])) {
                    int B_index = rhs[j] - 'A';

                    if (j + 1 < len) {
                        char next = rhs[j + 1];
                        if (isTerminal(next)) {
                            addToSet(followSets[B_index], next);
                        } else {
                            char *nextFirst = firstSets[next - 'A'];
                            for (int k = 0; nextFirst[k] != '\0'; k++) {
                                if (nextFirst[k] != '#') {
                                    addToSet(followSets[B_index], nextFirst[k]);
                                }
                            }
                        }
                    }

                    if (j + 1 == len || strchr(firstSets[rhs[j + 1] - 'A'], '#')) {
                        char *lhsFollow = followSets[lhs - 'A'];
                        for (int k = 0; lhsFollow[k] != '\0'; k++) {
                            if (!strchr(followSets[B_index], lhsFollow[k])) {
                                addToSet(followSets[B_index], lhsFollow[k]);
                                changes = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void printSets(char sets[26][MAX_SYMBOLS], char *setName) {
    int printed[26] = {0};
    printf("\n%s sets:\n", setName);
    for (int i = 0; i < numRules; i++) {
        char lhs = rules[i].lhs;
        if (!printed[lhs - 'A']) {
            printed[lhs - 'A'] = 1;
            printf("%s(%c) = { ", setName, lhs);
            for (int j = 0; sets[lhs - 'A'][j] != '\0'; j++) {
                printf("%c ", sets[lhs - 'A'][j]);
            }
            printf("}\n");
        }
    }
}

int main() {
    printf("Enter the number of rules: ");
    scanf("%d", &numRules);
    getchar();

    printf("Enter grammar rules (e.g., A->ab):\n");
    for (int i = 0; i < numRules; i++) {
        printf("Rule %d: ", i + 1);
        scanf("%c->%s", &rules[i].lhs, rules[i].rhs);
        getchar();
    }

    for (int i = 0; i < numRules; i++) {
        computeFirst(rules[i].lhs);
    }

    computeFollow();

    printSets(firstSets, "First");
    printSets(followSets, "Follow");

    return 0;
}

/*
Sample Input/Output:

Input:
Enter the number of rules: 5
Rule 1: E->TE'
Rule 2: E'->+TE'
Rule 3: E'->#
Rule 4: T->FT'
Rule 5: T'->*FT'

Output:
First(E) = { ( id }
First(E') = { + # }
First(T) = { ( id }
First(T') = { * # }
Follow(E) = { $, ) }
Follow(E') = { $, ) }
Follow(T) = { +, ), $ }
Follow(T') = { +, ), $ }
*/
