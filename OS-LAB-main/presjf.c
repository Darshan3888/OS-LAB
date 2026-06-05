#include <stdio.h>

int main() {
    int n, i, smallest, count = 0, time;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n];

    printf("Enter Burst Times:\n");

    for(i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    rt[9] = 9999;

    for(time = 0; count != n; time++) {
        smallest = 9;

        for(i = 0; i < n; i++) {
            if(rt[i] < rt[smallest] && rt[i] > 0) {
                smallest = i;
            }
        }

        rt[smallest]--;

        if(rt[smallest] == 0) {
            count++;
            tat[smallest] = time + 1;
            wt[smallest] = tat[smallest] - bt[smallest];
        }
    }

    printf("\nProcess\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n",
               i+1, bt[i], wt[i], tat[i]);
    }

    return 0;
}
