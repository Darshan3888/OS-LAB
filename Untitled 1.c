#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];


    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burst);
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }


    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        p[i].completion = current_time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        p[i].response = p[i].waiting;
        current_time = p[i].completion;
    }


    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround,
               p[i].waiting, p[i].response);
    }


    float avgTAT = 0, avgWT = 0, avgRT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
        avgRT += p[i].response;
    }
    avgTAT /= n;
    avgWT /= n;
    avgRT /= n;

    printf("\nAverage Turnaround Time: %.2f", avgTAT);
    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Response Time: %.2f\n", avgRT);

    return 0;
}
