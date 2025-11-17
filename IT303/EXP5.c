/*
To implement Sliding window protocol.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 10

int main() {
    int window_size, total_frames, sent = 0, ack;
    int i;

    srand(time(NULL)); // for random ACK simulation

    printf("Enter the total number of frames to send: ");
    scanf("%d", &total_frames);

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    printf("\n--- Simulating Sliding Window Protocol (Go-Back-N) ---\n\n");

    while (sent < total_frames) {
        printf("Sending frames: ");
        for (i = 0; i < window_size && sent + i < total_frames; i++)
            printf("[%d] ", sent + i + 1);
        printf("\n");

        // Simulate random ACK loss
        int random_loss = rand() % window_size;

        printf("Enter the last ACK received (0 if none lost, %d means all received): ", sent + window_size);
        printf("\n(Simulated ACK loss: frame %d not acknowledged)\n", sent + random_loss + 1);

        ack = sent + random_loss; // simulate missing ACK

        if (ack >= sent + window_size || ack >= total_frames) {
            printf("All frames acknowledged up to %d.\n", total_frames);
            break;
        } else {
            printf("ACK received for frame %d. Retransmitting from frame %d...\n", ack, ack + 1);
            sent = ack; // retransmit from missing ACK
        }

        sent += window_size;
        if (sent > total_frames) sent = total_frames;
        printf("\n");
    }

    printf("\nAll frames sent and acknowledged successfully.\n");
    return 0;
}