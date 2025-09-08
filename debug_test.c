#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Test grep with the exact pattern that's causing trouble
    char *cmd = "/usr/bin/grep";
    char *args[] = {"/usr/bin/grep", ");\"\\\$", NULL};
    pid_t pid;
    int status;

    printf("Testing: %s '%s'\n", cmd, args[1]);
    printf("Pattern should be: ');\"$\n");
    printf("Number of args: 2 (program name + pattern)\n");

    pid = fork();
    if (pid == 0) {
        // Child process
        // Provide empty input via stdin
        int pipefd[2];
        pipe(pipefd);
        close(pipefd[1]); // Close write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to read from pipe
        close(pipefd[0]);

        execv(cmd, args);
        exit(1); // exec failed
    } else {
        // Parent process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Exit code: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
