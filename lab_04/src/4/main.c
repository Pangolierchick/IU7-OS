#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void print_status(int s) {
    if (WIFEXITED(s)) {
        puts("\tProcess completed successfully.");
        printf("\tReturn code: %d\n", WEXITSTATUS(s));
    } else if (WIFSIGNALED(s)) {
        puts("\tProcess terminated due to unhandled signal");
        printf("\tSignal number: %d\n", WTERMSIG(s));
    } else if (WIFSTOPPED(s)) {
        puts("\tProcess has been stopped");
        printf("\tSignal number: %d\n", WTERMSIG(s));
    }
}

const char *msgs[] = { "Message 1 ", "Mes 2" };

int main(void) {
    pid_t ch1, ch2;
    int status;

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Cant pipe.");
        return EXIT_FAILURE;
    }

    ch1 = fork();

    if (ch1 == -1) {
        perror("Can't fork process 0");
        exit(EXIT_FAILURE);
    } else if (ch1 == 0) {
        close(fd[0]);
        write(fd[1], msgs[0], strlen(msgs[0]));
        printf("Child #%d: pid: %d\tparent: %d\tgroup: %d\n", 0, getpid(), getppid(), getpgrp());
        exit(EXIT_SUCCESS);
    }

    ch2 = fork();

    if (ch2 == -1) {
        perror("Can't fork process 1");
        exit(EXIT_FAILURE);
    } else if (ch2 == 0) {
        close(fd[0]);
        write(fd[1], msgs[1], strlen(msgs[1]));
        printf("Child #%d: pid: %d\tparent: %d\tgroup: %d\n", 1, getpid(), getppid(), getpgrp());
        exit(EXIT_SUCCESS);
    }

    wait(&status);
    print_status(status);

    wait(&status);
    print_status(status);

    close(fd[1]);

    const int buff_size = 50;
    char buff[buff_size];

    read(fd[0], buff, buff_size);

    printf("  Read: %s\n", buff);

    printf("Parent's children id: %d, %d\n", ch1, ch2);

    printf("\n Parent pid: %d\t group: %d\n", getpid(), getpgrp());

    return 0;
}
