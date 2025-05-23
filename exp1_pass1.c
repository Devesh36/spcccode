// ------------------- CODE -------------------
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
    FILE *f1, *f2, *f3;
    int lc, sa, op1, o, len;
    char m1[20], la[20], op[20], otp[20];
    f1 = fopen("input.txt", "r");
    f3 = fopen("symtab.txt", "w");

    fscanf(f1, "%s %s %d", la, m1, &op1);
    if(strcmp(m1, "START") == 0) {
        sa = op1;
        lc = sa;
        printf("\n%s\t%s\t%d\n", la, m1, op1);
    } else
        lc = 0;

    fscanf(f1, "%s %s", la, m1);
    while(!feof(f1)) {
        fscanf(f1, "%s", op);
        printf("\n%d\t%s\t%s\t%s\n", lc, la, m1, op);
        if(strcmp(la, "-") != 0)
            fprintf(f3, "\n%d\t%s", lc, la);

        f2 = fopen("optab.txt", "r");
        fscanf(f2, "%s %d", otp, &o);
        while(!feof(f2)) {
            if(strcmp(m1, otp) == 0) {
                lc += 3;
                break;
            }
            fscanf(f2, "%s %d", otp, &o);
        }
        fclose(f2);

        if(strcmp(m1, "WORD") == 0)
            lc += 3;
        else if(strcmp(m1, "RESW") == 0) {
            op1 = atoi(op);
            lc += (3 * op1);
        }
        else if(strcmp(m1, "BYTE") == 0) {
            if(op[0]=='X')
                lc += 1;
            else {
                len = strlen(op) - 2;
                lc += len;
            }
        }
        else if(strcmp(m1, "RESB") == 0) {
            op1 = atoi(op);
            lc += op1;
        }
        fscanf(f1, "%s %s", la, m1);
    }

    if(strcmp(m1, "END") == 0)
        printf("\nProgram length = %d", lc - sa);

    fclose(f1);
    fclose(f3);
}

// ------------------- INPUT FILES -------------------
// input.txt
/*
COPY START 1000
- LDA ALPHA
- STA BETA
ALPHA RESW 1
BETA RESW 1
- END -
*/

// optab.txt
/*
LDA 03
STA 0F
*/

// ------------------- OUTPUT -------------------
// symtab.txt
/*
1000    COPY
1003    ALPHA
1006    BETA
*/
