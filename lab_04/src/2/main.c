#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    pid_t ch1, ch2;
    int status;

    ch1 = fork();

    if (ch1 == -1) {
        perror("Can't fork process 0");
        exit(EXIT_FAILURE);
    } else if (ch1 == 0) {
        sleep(2);
        printf("Child #%d: pid: %d\tparent: %d\tgroup: %d\n", 0, getpid(), getppid(), getpgrp());
        exit(EXIT_SUCCESS);
    }

    ch2 = fork();

    if (ch2 == -1) {
        perror("Can't fork process 1");
        exit(EXIT_FAILURE);
    } else if (ch2 == 0) {
        sleep(2);
        printf("Child #%d: pid: %d\tparent: %d\tgroup: %d\n", 1, getpid(), getppid(), getpgrp());
        exit(EXIT_SUCCESS);
    }

    wait(&status);
    
    if (WIFEXITED(status)) {
        puts("\tProcess completed successfully.");
        printf("\tReturn code: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        puts("\tProcess terminated due to unhandled signal");
        printf("\tSignal number: %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        puts("\tProcess has been stopped");
        printf("\tSignal number: %d\n", WTERMSIG(status));
    }

    wait(&status);
    
    if (WIFEXITED(status)) {
        puts("\tProcess completed successfully.");
        printf("\tReturn code: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        puts("\tProcess terminated due to unhandled signal");
        printf("\tSignal number: %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        puts("\tProcess has been stopped");
        printf("\tSignal number: %d\n", WTERMSIG(status));
    }

    printf("Parent's children id: %d, %d\n", ch1, ch2);

    printf("\n Parent pid: %d\t group: %d\n", getpid(), getpgrp());

    return 0;
}
