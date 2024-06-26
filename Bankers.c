#include <stdio.h>
#include <stdbool.h>

int processes, resources;
int max[10][10], allocation[10][10], need[10][10], available[10];

bool is_safe_state() {
    bool finish[10] = {false};
    int work[10];
    int safe_sequence[10];
    int count = 0;

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (count < processes) {
        bool allocated = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    allocated = true;
                }
            }
        }
        if (!allocated) {
            break;
        }
    }

    if (count < processes) {
        printf("The system is in an unsafe state.\n");
        return false;
    } else {
        printf("The system is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < processes; i++) {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
        return true;
    }
}

void request_resources(int process_num, int request[]) {
    for (int j = 0; j < resources; j++) {
        if (request[j] > need[process_num][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
        if (request[j] > available[j]) {
            printf("Error: Resources are not available.\n");
            return;
        }
    }

    for (int j = 0; j < resources; j++) {
        available[j] -= request[j];
        allocation[process_num][j] += request[j];
        need[process_num][j] -= request[j];
    }

    if (!is_safe_state()) {
        for (int j = 0; j < resources; j++) {
            available[j] += request[j];
            allocation[process_num][j] -= request[j];
            need[process_num][j] += request[j];
        }
        printf("Request cannot be granted. The system would be in an unsafe state.\n");
    } else {
        printf("Request can be granted.\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter the maximum resources matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter the available resources:\n");
    for (int j = 0; j < resources; j++) {
        scanf("%d", &available[j]);
    }

    int process_num;
    printf("Enter process number for resource request: ");
    scanf("%d", &process_num);
    int request[10];
    printf("Enter resource request:\n");
    for (int j = 0; j < resources; j++) {
        scanf("%d", &request[j]);
    }

    request_resources(process_num, request);

    return 0;
}
