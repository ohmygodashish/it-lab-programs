/*
To implement Stop and Wait Protocol.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For sleep()

#define TIMEOUT 2      // Timeout in seconds
#define TOTAL_PACKETS 5 // Number of packets to send

// Simulates receiving an acknowledgment (70% chance of success)
int simulate_ack() {
    return rand() % 10 < 7;
}

int main() {
    srand(time(0));
    int packet = 1;
    int ack_received;

    while (packet <= TOTAL_PACKETS) {
        printf("Sender: Sending packet %d...\n", packet);

        // Simulate transmission delay
        sleep(1);

        ack_received = simulate_ack();

        if (ack_received) {
            printf("Receiver: ACK for packet %d received.\n\n", packet);
            packet++; // Send next packet
        } else {
            printf("Receiver: ACK for packet %d lost! Retransmitting...\n\n", packet);
            // Simulate timeout before retransmission
            sleep(TIMEOUT);
            // packet remains the same, so sender resends it
        }
    }

    printf("All packets sent successfully!\n");
    return 0;
}