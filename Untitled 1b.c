#include <stdio.h>
struct Process {
    int pid, at, bt, ct, tat, wt, rt, remaining, completed;
};
void non_preemptive_sjf(struct Process p[], int n) {
    int time = 0, completed = 0;
    printf("\n--- Non-preemptive SJF ---\nGantt Chart (Order): ");
    while (completed != n) {
        int idx = -1, min_bt = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt;
            p[idx].completed = 1;
            completed++;
            printf("P%d ", p[idx].pid);
        } else time++;
    }
    printf("\n");
}
void preemptive_sjf(struct Process p[], int n) {
    int time = 0, completed = 0;
    printf("\n--- Preemptive SJF (SRTF) ---\nGantt Chart (Order): ");
    while (completed != n) {
        int idx = -1, min_bt = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].remaining < min_bt) {
                    min_bt = p[i].remaining;
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            if (p[idx].remaining == p[idx].bt) {
                p[idx].rt = time - p[idx].at;
            }
            p[idx].remaining--;
            time++;
            static int last = -1;
            if (last != p[idx].pid) {
                printf("P%d ", p[idx].pid);
                last = p[idx].pid;
            }
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } else time++;
    }
    printf("\n");
}
int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining = p[i].bt;
        p[i].completed = 0;
    }
    printf("\nChoose Scheduling:\n1. Non-preemptive SJF\n2. Preemptive SJF (SRTF)\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: non_preemptive_sjf(p, n); break;
        case 2: preemptive_sjf(p, n); break;
        default: printf("Invalid choice!\n"); return 0;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        avg_rt += p[i].rt;
    }
    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage WT  = %.2f", avg_wt / n);
    printf("\nAverage RT  = %.2f\n", avg_rt / n);
    return 0;
}
