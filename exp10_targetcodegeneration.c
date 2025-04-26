// Experiment 10
// Program for Target Code Generation

#include<stdio.h>
#include<conio.h>

int main() {
    char A[12][12] = {"T=AB", "X=T"};
    char B;
    int OP = 0;

    printf("MOV %c,R1\n", A[0][2]);
    printf("MOV %c,R2\n", A[0][3]);
    B = A[0][3];

    printf("THERE ARE TWO EXPRESSIONS:\n1. T=A op B\n2. X=T\n");
    printf("CHOOSE THE OP VALUE FROM OPTION\n1. +\n2. -\n3. *\n4. /\n");
    scanf("%d", &OP);

    switch(OP) {
        case 1:
            printf("ADD R1,R2\n");
            break;
        case 2:
            printf("SUB R1,R2\n");
            break;
        case 3:
            printf("MUL R1,R2\n");
            break;
        case 4:
            printf("DIV R1,R2\n");
            break;
        default:
            printf("Invalid Option\n");
            break;
    }

    printf("MOV R1,x\n");

    getch();
    return 0;
}

/*
Sample Input/Output:

MOV A,R1
MOV B,R2
THERE ARE TWO EXPRESSIONS:
1. T=A op B
2. X=T
CHOOSE THE OP VALUE FROM OPTION
1. +
2. -
3. *
4. /
Input: 1

Output:
ADD R1,R2
MOV R1,x
*/
