// ------------------- CODE -------------------
#include<stdio.h>
#include<string.h>

void main() {
    char str[100];
    int i=0, state=0;
    printf("Enter string: ");
    gets(str);

    while(str[i]!='\0') {
        switch(state) {
            case 0:
                if(str[i]=='a') state=1;
                else if(str[i]=='b') state=0;
                else state=-1;
                break;
            case 1:
                if(str[i]=='b') state=2;
                else if(str[i]=='a') state=1;
                else state=-1;
                break;
            case 2:
                if(str[i]=='b') state=3;
                else if(str[i]=='a') state=1;
                else state=-1;
                break;
            case 3:
                state=3;
                break;
        }
        if(state==-1)
            break;
        i++;
    }

    if(state==3)
        printf("String accepted\n");
    else
        printf("String not accepted\n");
}

// ------------------- INPUT EXAMPLES -------------------
/*
Input 1:
abb

Input 2:
aabba
*/

// ------------------- OUTPUT -------------------
/*
Input 1 Output:
String accepted

Input 2 Output:
String not accepted
*/
