#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define size 15000
#define pwd 1000

int picoshell_main(int argc, char *argv[]) {
    char buf[size], pwdbuf[pwd];
    int last_status = 0;

    while (1) {
        printf("FSP > ");
        fflush(stdout);

        if ((fgets(buf, size, stdin)) == NULL)
            exit(last_status);  

        buf[strlen(buf) - 1] = 0;

        if (strlen(buf) == 0)
            continue;

        char **c = NULL;
        int j = 0;
        int k = 0;
        int buflen = strlen(buf);
        char temp[buflen + 1];
        memset(temp, 0, sizeof(temp));

        for (int i = 0; i <= buflen; ++i) {
            if (buf[i] != ' ' && buf[i] != '\0') {
                temp[k++] = buf[i];
            } else {
                if (k > 0) {
                    temp[k] = '\0';
                    c = (char **) realloc(c, sizeof(char *) * (j + 1));
                    c[j] = (char *) malloc(strlen(temp) + 1);
                    strcpy(c[j], temp);
                    j++;
                    k = 0;
                }
            }
        }

        c = (char **) realloc(c, sizeof(char *) * (j + 1));
        c[j] = NULL;

        if (j == 0) {
            free(c);
            continue;
        }

        if ((strcmp(c[0], "exit")) == 0) {
            printf("Good Bye\n");
            for (int i = 0; i < j; i++)
                free(c[i]);
            free(c);
            return last_status;
        }
        else if ((strcmp(c[0], "pwd")) == 0) {
            if (getcwd(pwdbuf, pwd) == NULL) {
                for (int i = 0; i < j; i++)
                    free(c[i]);
                free(c);
                last_status = 1;
                continue;
            }
            printf("%s\n", pwdbuf);
            last_status = 0;
            continue;
        }
        else if ((strcmp(c[0], "cd")) == 0) {
            if (chdir(c[1]) == -1) {
                printf("cd: %s: No such file or directory\n", c[1]);
                last_status = 1;
                continue;
            }
            last_status = 0;
            continue;
        }
        else if ((strcmp(c[0], "echo")) == 0) {
            for (int i = 1; i < j; i++) {
                printf("%s", c[i]);
                if (i < j - 1)
                    printf(" ");
            }
            printf("\n");
            last_status = 0;
            continue;
        }
        else {
            pid_t pid = fork();
            if (pid > 0) {
                int wstatus;
                wait(&wstatus);
                if (WIFEXITED(wstatus)) {
                    last_status = WEXITSTATUS(wstatus);
                    if (last_status != 0)
                        printf("%s: command not found\n", c[0]);
                } else {
                    last_status = 1;
                }
                continue;
            }
            else if (pid == 0) {
                execvp(c[0], c);
                exit(127);  
            }
        }

        for (int i = 0; i < j; i++) free(c[i]);
        free(c);
    }

    return last_status;
}
