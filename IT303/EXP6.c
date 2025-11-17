/*
To implement a link state route algorithm.
*/

#include <stdio.h>
#define INF 9999
#define MAX 10

void dijkstra(int graph[MAX][MAX], int n, int start) {
    int cost[MAX][MAX], distance[MAX], visited[MAX], pred[MAX];
    int count, mindistance, nextnode, i, j;

    // Create cost matrix (replace 0 with INF except for diagonal)
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (graph[i][j] == 0 && i != j)
                cost[i][j] = INF;
            else
                cost[i][j] = graph[i][j];

    // Initialize arrays
    for (i = 0; i < n; i++) {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    // Dijkstra's algorithm
    while (count < n - 1) {
        mindistance = INF;

        // Find the next node with minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }

        // Mark node as visited
        visited[nextnode] = 1;

        // Update distances of neighboring nodes
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }

        count++;
    }

    // Print the results
    printf("\nShortest paths from router %d:\n", start + 1);
    for (i = 0; i < n; i++)
        if (i != start) {
            printf("\nTo node %d: Distance = %d\tPath: %d", i + 1, distance[i], i + 1);
            j = i;
            do {
                j = pred[j];
                printf(" <- %d", j + 1);
            } while (j != start);
        }
    printf("\n");
}

int main() {
    int graph[MAX][MAX], n, start, i, j;

    printf("Enter the number of routers (nodes): ");
    scanf("%d", &n);

    printf("\nEnter the cost adjacency matrix (0 if no direct link):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("\nEnter the starting router (1 to %d): ", n);
    scanf("%d", &start);

    dijkstra(graph, n, start - 1);
    return 0;
}