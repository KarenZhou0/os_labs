#include <stdlib.h> 
#include <stdio.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include <string.h>

int main() {
    while (1) {
        printf("lab1> ");
        char * argv = "";
        fgets(argv, 500, stdin);
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
                const char * arg_lst = strtok(argv, " ");
                char * path = "/bin/";
                strcat(path, arg_lst[0]);
                execve(path, arg_lst, NULL);
                printf("Command Not Found!\n");
                exit(0);
            }
        }
    }
    wait(NULL);
    return 0;
}