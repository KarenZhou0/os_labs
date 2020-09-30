#include <stdlib.h> 
#include <stdio.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include <string.h>
#define MAXLEN 1000

int main() {
    while (1) {
        printf("lab1> ");
        char argv[MAXLEN];
        fgets(argv, MAXLEN, stdin);
        printf("Parent Process %d\n", getpid());
        if (strcmp(argv, "printid\n") == 0) {
            printf("The ID of the current process is %d\n", getpid());
        } else if (strcmp(argv, "greet\n") == 0) {
            printf("Hello\n");
        } else if (strcmp(argv, "exit\n") == 0) {
            exit(0);
        } else {
            int pid = fork();
            if (pid == 0) { // we enter the child process
                printf("Child process %d will execute the command %s\n", getpid(), argv);
                // split the argv string into a list of strings with NULL at the end of the list
                char ** arg_lst = malloc(sizeof(char) * MAXLEN);
                char * token;
                token = strtok(argv, " ");
                int i = 0;
                while (token != NULL) {
                    arg_lst[i] = token;
                    token = strtok(NULL, " ");
                    i++;
                }
                arg_lst[i+1] = NULL;
                // create a path as the first argument
                char path[MAXLEN];
                strcpy(path, "/bin/");
                strcpy(path, arg_lst[0]);
                printf("path is %s\n", path);
                printf("arg_lst is %s\n", arg_lst);
                // printf("arg list is %s\n", arg_lst[0]);
                if (execve(path, arg_lst, NULL) < 0) {
                    printf("Command Not Found!\n");
                    exit(0);
                } else {
                    free(arg_lst);
                }
            }
        }
        wait(NULL);
    }
    return 0;
}