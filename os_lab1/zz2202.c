#include <stdlib.h> 
#include <stdio.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include <string.h>
#define ARGLEN 1000
#define PATHLEN 100

int main() {
    while (1) {
        printf("lab1> ");
        char argv[ARGLEN];
        fgets(argv, ARGLEN, stdin);
        argv[strlen(argv) - 1] = '\0';
        printf("Parent Process %d\n", getpid());
        if (strcmp(argv, "printid") == 0) {
            printf("The ID of the current process is %d\n", getpid());
        } else if (strcmp(argv, "greet") == 0) {
            printf("Hello\n");
        } else if (strcmp(argv, "exit") == 0) {
            exit(0);
        } else {
            int pid = fork();
            if (pid == 0) { // we enter the child process
                printf("Child process %d will execute the command %s\n", getpid(), argv);
                char * arg_list[] = {argv, NULL};
                char path[PATHLEN] = "/bin/";
                strcat(path, argv);
                if (strcmp(argv, "ls") == 0 || strcmp(argv, "pwd") == 0 || strcmp(argv, "ps") == 0 || strcmp(argv, "date") == 0 || strcmp(argv, "lscpu") == 0) {
                    execve(path, arg_list, NULL);
                } else {
                    // execve failed
                    printf("Command Not Found!\n");
                    exit(0);
                }
            }
        }
        wait(NULL);
    }
    return 0;
}