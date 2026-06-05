
#include <stdio.h>

int main() {
    int n, i, j, temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], deadline[n];

    printf("Enter Burst Time and Deadline:\n");

    for(i = 0; i < n; i++) {
        scanf("%d%d", &burst[i], &deadline[i]);
    }

    // Sort according to earliest deadline
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {

            if(deadline[i] > deadline[j]) {

                temp = deadline[i];
                deadline[i] = deadline[j];
                deadline[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;
            }
        }
    }

    printf("\nProcess\tBurst Time\tDeadline\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n",
               i+1, burst[i], deadline[i]);
    }

    return 0;
}
