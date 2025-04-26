// ------------------- PASS 1 CODE -------------------
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
    FILE *in,*mnt,*mdt;
    char name[20],def[50];
    int mdtp=1;

    in = fopen("macro_input.txt", "r");
    mnt = fopen("mnt.txt", "w");
    mdt = fopen("mdt.txt", "w");

    if(!in || !mnt || !mdt) {
        printf("Error Opening Files!");
        exit(0);
    }

    while(fscanf(in, "%s", name) != EOF) {
        if(strcmp(name,"MACRO")==0) {
            fscanf(in,"%s",name);
            fprintf(mnt,"%s\t%d\n",name,mdtp);

            while(fscanf(in, "%s",def) && strcmp(def,"MEND")!=0) {
                fprintf(mdt,"%d\t%s\n",mdtp++,def);
            }
            fprintf(mdt,"%d\tMEND\n",mdtp++);
        }
    }

    fclose(in);
    fclose(mnt);
    fclose(mdt);
}

// ------------------- PASS 2 CODE -------------------
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
    FILE *in,*mnt,*mdt,*out;
    char word[20],mntname[20];
    int pos,flag=0;

    in = fopen("macro_input.txt", "r");
    mnt = fopen("mnt.txt", "r");
    mdt = fopen("mdt.txt", "r");
    out = fopen("expanded.txt", "w");

    while(fscanf(in, "%s",word)!=EOF) {
        rewind(mnt);
        flag=0;
        while(fscanf(mnt, "%s%d",mntname,&pos)!=EOF) {
            if(strcmp(word,mntname)==0) {
                rewind(mdt);
                while(fscanf(mdt,"%d%s",&pos,word)!=EOF) {
                    if(strcmp(word,"MEND")==0)
                        break;
                    fprintf(out,"%s\n",word);
                }
                flag=1;
                break;
            }
        }
        if(flag==0)
            fprintf(out,"%s\n",word);
    }

    fclose(in);
    fclose(mnt);
    fclose(mdt);
    fclose(out);
}

// ------------------- INPUT FILES -------------------
// macro_input.txt
/*
MACRO
INCR A
LDA A
ADD ONE
STA A
MEND
START
INCR B
STOP
END
*/

// ------------------- OUTPUT -------------------
/*
expanded.txt:
START
LDA B
ADD ONE
STA B
STOP
END
*/
