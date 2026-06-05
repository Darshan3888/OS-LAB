#include <stdio.h>

int main() {
    int n, i;
    float total = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int tickets[n];

    printf("Enter number of tickets for each process:\n");

    for(i = 0; i < n; i++) {
        scanf("%d", &tickets[i]);
        total += tickets[i];
    }

    printf("\nProcess\tTickets\tCPU Share\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%.2f%%\n",
               i+1,
               tickets[i],
               (tickets[i] / total) * 100);
    }

    return 0;
}
