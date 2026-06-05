#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];
    int finish[n];
    int work[m];

    // Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Request Matrix
    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Available resources
    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    // Initialize finish array
    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Deadlock detection logic
    int found;

    do {
        found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j]) {
                        break;
                    }
                }

                if(j == m) {
                    // Process can finish
                    for(k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

    } while(found == 1);

    // Check for deadlock
    int deadlock = 0;

    printf("\nDeadlocked Processes: ");

    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0) {
        printf("None (No Deadlock)");
    }

    printf("\n");

    return 0;
}
