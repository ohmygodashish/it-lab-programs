/*
To implement a leaky bucket algorithm.
*/

#include <stdio.h>

int main() {
    int bucket_size, output_rate, n, incoming;
    int stored = 0; // Current number of packets in the bucket

    printf("Enter bucket size (in packets): ");
    scanf("%d", &bucket_size);

    printf("Enter output rate (packets per second): ");
    scanf("%d", &output_rate);

    printf("Enter number of incoming packet batches: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter number of packets arriving at second %d: ", i + 1);
        scanf("%d", &incoming);

        printf("Packets in bucket before arrival: %d\n", stored);

        // If bucket will overflow
        if (incoming + stored > bucket_size) {
            int dropped = (incoming + stored) - bucket_size;
            stored = bucket_size;
            printf("Bucket overflow! Dropped packets: %d\n", dropped);
        } else {
            stored += incoming;
            printf("No packet loss.\n");
        }

        // Transmit packets
        if (stored >= output_rate) {
            stored -= output_rate;
            printf("Transmitted %d packets.\n", output_rate);
        } else {
            printf("Transmitted %d packets.\n", stored);
            stored = 0;
        }

        printf("Packets remaining in bucket: %d\n", stored);
    }

    // Transmit remaining packets after last batch
    while (stored > 0) {
        if (stored >= output_rate) {
            stored -= output_rate;
            printf("\nTransmitted %d packets. Packets remaining: %d", output_rate, stored);
        } else {
            printf("\nTransmitted %d packets. Packets remaining: 0", stored);
            stored = 0;
        }
    }

    printf("\n\nAll packets have been transmitted successfully.\n");
    return 0;
}