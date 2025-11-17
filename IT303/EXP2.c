/*
To implement Bit stuffing.
*/

#include <stdio.h>

// Bit Stuffing function
void bitStuffing(int input[], int n, int stuffed[], int *stuffedLen) {
    int i, j = 0, count = 0;
    for (i = 0; i < n; i++) {
        stuffed[j++] = input[i];
        if (input[i] == 1) {
            count++;
        } else {
            count = 0;
        }
        if (count == 5) {
            // Stuff a zero after five consecutive ones
            stuffed[j++] = 0; 
            count = 0;
        }
    }
    *stuffedLen = j;
}

int main() {
    int n, i, frame[100], stuffed[200], destuffed[200];
    int stuffedLen;
    
    printf("Enter frame size: ");
    scanf("%d", &n);
    printf("Enter the binary frame (0s and 1s):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &frame[i]);
    }

    // Bit Stuffing
    bitStuffing(frame, n, stuffed, &stuffedLen);
    printf("After Bit Stuffing: ");
    for (i = 0; i < stuffedLen; i++) {
        printf("%d", stuffed[i]);
    }
    printf("\n"); 
    
    return 0;
}