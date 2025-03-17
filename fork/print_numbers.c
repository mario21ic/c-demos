#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROCESSES 4
#define NUMBERS_PER_PROCESS 25

void print_numbers(int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%d\n", i);
    }
}

int main() {
    pid_t pids[NUM_PROCESSES];
    int start, end;

    for (int i = 0; i < NUM_PROCESSES; i++) {
        start = i * NUMBERS_PER_PROCESS;
        end = start + NUMBERS_PER_PROCESS - 1;

        if ((pids[i] = fork()) < 0) {
            perror("fork");
            exit(1);
        } else if (pids[i] == 0) {
            print_numbers(start, end);
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}
