#include <stdio.h>
struct Process {
    int pid;
    int bt;
    int wt;
    int tat;
};
void fcfs(struct Process p[], int n) {
    int totalWT = 0, totalTAT = 0;
    p[0].wt = 0;
    p[0].tat = p[0].bt;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWT/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT/n);
}
int main() {
    int sys_n, user_n;
    printf("Enter number of system processes: ");
    scanf("%d", &sys_n);
    struct Process sys[sys_n];
    for (int i = 0; i < sys_n; i++) {
        sys[i].pid = i+1;
        printf("Enter burst time for System Process %d: ", sys[i].pid);
        scanf("%d", &sys[i].bt);
    }
    printf("\nEnter number of user processes: ");
    scanf("%d", &user_n);
    struct Process user[user_n];
    for (int i = 0; i < user_n; i++) {
        user[i].pid = i+1;
        printf("Enter burst time for User Process %d: ", user[i].pid);
        scanf("%d", &user[i].bt);
    }
    printf("\n--- Scheduling System Processes (Higher Priority) ---\n");
    fcfs(sys, sys_n);
    printf("\n--- Scheduling User Processes (Lower Priority) ---\n");
    fcfs(user, user_n);
    return 0;
}
