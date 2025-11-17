/*
To implement Cyclic Redundancy Check (CRC).
*/

#include <stdio.h>
#include <string.h>

// Function to perform XOR between two binary strings
void xor(char *dividend, char *divisor, int len) {
    for (int i = 1; i < len; i++)
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
}

// Function to perform Modulo-2 division
void mod2div(char *data, char *key, char *remainder) {
    int datalen = strlen(data);
    int keylen = strlen(key);
    char temp[100];
    strncpy(temp, data, keylen);
    temp[keylen] = '\0';

    int i = keylen;
    while (i < datalen) {
        if (temp[0] == '1')
            xor(temp, key, keylen);
        else
            // Assuming key length 4 for example
            xor(temp, "0000", keylen);
        // Shift left and bring down next bit
        memmove(temp, temp + 1, keylen - 1);
        temp[keylen - 1] = data[i++];
        temp[keylen] = '\0';
    }
    // Final XOR
    if (temp[0] == '1')
        xor(temp, key, keylen);
    else
        xor(temp, "0000", keylen); // for key length 4
    // The remainder is the last (keylen-1) bits
    strncpy(remainder, temp + 1, keylen - 1);
    remainder[keylen - 1] = '\0';
}

int main() {
    char data[100], key[20], encoded[120], remainder[20];

    // Example: data = "100100", key = "1101"
    printf("Enter data bits: ");
    scanf("%s", data);
    printf("Enter key (polynomial): ");
    scanf("%s", key);

    int datalen = strlen(data);
    int keylen = strlen(key);

    // Sender side: Append k-1 zeros to data
    strcpy(encoded, data);
    for (int i = 0; i < keylen - 1; i++)
        encoded[datalen + i] = '0';
    encoded[datalen + keylen - 1] = '\0';

    // Get CRC remainder
    mod2div(encoded, key, remainder);

    // Append remainder to data to get code word
    printf("CRC remainder: %s\n", remainder);
    printf("Transmitted code word: %s%s\n", data, remainder);

    // Receiver side: Check for errors in received code word
    printf("Enter received code word to check: ");
    scanf("%s", encoded);

    mod2div(encoded, key, remainder);

    // If remainder is all zeros, data is correct
    int isError = 0;
    for (int i = 0; i < keylen - 1; i++) {
        if (remainder[i] != '0') {
            isError = 1;
            break;
        }
    }
    if (isError)
        printf("Error detected in received code word!\n");
    else
        printf("No error detected in received code word.\n");

    return 0;
}