#include <stdio.h>

int main() {
    int ns, nu, i;
    
    printf("Enter number of System processes: ");
    scanf("%d", &ns);

    int sbt[ns], swt[ns], stat[ns];

    printf("Enter burst times for System processes:\n");
    for(i = 0; i < ns; i++) {
        scanf("%d", &sbt[i]);
    }

    printf("Enter number of User processes: ");
    scanf("%d", &nu);

    int ubt[nu], uwt[nu], utat[nu];

    printf("Enter burst times for User processes:\n");
    for(i = 0; i < nu; i++) {
        scanf("%d", &ubt[i]);
    }

    // FCFS for System Processes
    swt[0] = 0;

    for(i = 1; i < ns; i++) {
        swt[i] = swt[i-1] + sbt[i-1];
    }

    for(i = 0; i < ns; i++) {
        stat[i] = swt[i] + sbt[i];
    }

    // FCFS for User Processes
    uwt[0] = stat[ns-1];

    for(i = 1; i < nu; i++) {
        uwt[i] = uwt[i-1] + ubt[i-1];
    }

    for(i = 0; i < nu; i++) {
        utat[i] = uwt[i] + ubt[i];
    }

    printf("\nSystem Processes:\n");
    printf("Process\tBT\tWT\tTAT\n");

    for(i = 0; i < ns; i++) {
        printf("S%d\t%d\t%d\t%d\n",
               i+1, sbt[i], swt[i], stat[i]);
    }

    printf("\nUser Processes:\n");
    printf("Process\tBT\tWT\tTAT\n");

    for(i = 0; i < nu; i++) {
        printf("U%d\t%d\t%d\t%d\n",
               i+1, ubt[i], uwt[i], utat[i]);
    }

    return 0;
}
