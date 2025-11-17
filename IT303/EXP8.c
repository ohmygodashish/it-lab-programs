/*
To implement IP packet forwarding.
*/

#include <stdio.h>
#include <string.h>

struct route_entry {
    char destination[20];
    char subnet_mask[20];
    char next_hop[20];
    char interface[10];
};

int main() {
    struct route_entry table[10];
    char dest_ip[20];
    int n, i, found = 0;

    printf("Enter number of routing table entries: ");
    scanf("%d", &n);

    printf("\nEnter routing table entries:\n");
    printf("(Format: Destination SubnetMask NextHop Interface)\n\n");

    for (i = 0; i < n; i++) {
        printf("Entry %d: ", i + 1);
        scanf("%s %s %s %s", 
              table[i].destination, 
              table[i].subnet_mask, 
              table[i].next_hop, 
              table[i].interface);
    }

    printf("\nRouting Table:\n");
    printf("----------------------------------------------\n");
    printf("Destination\tMask\t\tNextHop\t\tInterface\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%-15s %-15s %-15s %-10s\n", 
                table[i].destination, 
                table[i].subnet_mask, 
                table[i].next_hop, 
                table[i].interface);

    printf("\nEnter the destination IP to forward: ");
    scanf("%s", dest_ip);

    // Simple string match simulation
    for (i = 0; i < n; i++) {
        if (strcmp(dest_ip, table[i].destination) == 0) {
            printf("\nPacket forwarded to next hop %s via interface %s\n",
                   table[i].next_hop, table[i].interface);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nNo exact route found. Using default route if available.\n");

    printf("\n--- Packet forwarding simulation complete ---\n");
    return 0;
}