#include <stdio.h>
#include <stdbool.h>

bool is_deadlock(int allocation[][10], int request[][10], int available[], int processes, int resources) {
    int work[10];
    bool finish[10] = {false};

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool allocated_process = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    allocated_process = true;
                    break;
                }
            }
        }
        if (!allocated_process) {
            break;
        }
    }

    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    int processes, resources;
    int allocation[10][10], request[10][10], available[10];

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int j = 0; j < resources; j++) {
        scanf("%d", &available[j]);
    }

    if (is_deadlock(allocation, request, available, processes, resources)) {
        printf("Deadlock detected.\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}
