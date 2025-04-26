// Experiment 6
// Program to check for even number of 0's in a binary string

#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    int state = 0; // Start at state q0 (even number of zeros)

    printf("Enter a binary string (only 0s and 1s): ");
    scanf("%s", input);

    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];

        if (c == '0') {
            state = 1 - state; // Toggle between 0 and 1
        } else if (c == '1') {
            continue; // Stay in same state
        } else {
            printf("Invalid character detected: %c\n", c);
            return 1;
        }
    }

    if (state == 0) {
        printf("Accepted: The string has an even number of zeros.\n");
    } else {
        printf("Rejected: The string has an odd number of zeros.\n");
    }

    return 0;
}

/*
Sample Input/Output:

Input: 1101
Output: Accepted: The string has an even number of zeros.

Input: 100
Output: Rejected: The string has an odd number of zeros.

Input: 010
Output: Accepted: The string has an even number of zeros.
*/
