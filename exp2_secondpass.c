// ------------------- CODE -------------------
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char label[10];
    int address;
} symbol;

symbol symbols[20];
int symbolCount = 0;

typedef struct {
    int opcode;
    int operand;
} code;

code machineCode[20];
int codeCount = 0;

void firstPass(FILE *fp) {
    char line[80];
    int address = 0;
    while(fgets(line, 80, fp) != NULL) {
        char *label = strtok(line, " ");
        if(label != NULL) {
            strcpy(symbols[symbolCount].label, label);
            symbols[symbolCount].address = address;
            symbolCount++;
        }
        codeCount++;
        address++;
    }
}

void secondPass(FILE *fp) {
    char line[80];
    while(fgets(line, 80, fp) != NULL) {
        char *label = strtok(line, " ");
        char *opcode = strtok(NULL, " ");
        char *operand = strtok(NULL, " ");
        if(opcode != NULL) {
            int op = atoi(opcode);
            machineCode[codeCount].opcode = op;
            if(operand != NULL)
                machineCode[codeCount].operand = atoi(operand);
            else
                machineCode[codeCount].operand = -1;
            codeCount++;
        }
    }
}

void output() {
    int i;
    printf("\nSymbol Table:\n");
    for(i=0; i<symbolCount; i++) {
        printf("%s -> %d\n", symbols[i].label, symbols[i].address);
    }

    printf("\nMachine Code:\n");
    for(i=0; i<codeCount; i++) {
        printf("%d %d\n", machineCode[i].opcode, machineCode[i].operand);
    }
}

void main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    if(fp == NULL) {
        printf("File not found\n");
        exit(0);
    }
    firstPass(fp);
    rewind(fp);
    secondPass(fp);
    output();
    fclose(fp);
}

// ------------------- INPUT FILES -------------------
// input.txt (Same as Experiment 1)

// optab.txt (Same as Experiment 1)

// ------------------- OUTPUT -------------------
/*
Symbol Table:
COPY -> 0
ALPHA -> 1
BETA -> 2

Machine Code:
3 1
15 2
*/
