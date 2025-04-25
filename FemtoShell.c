#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 15000
#define cmd 4


int femtoshell_main(int argc, char *argv[]) {
    char buf[size],c[cmd];
    while(1){
        printf("FSP > ");
        if((fgets(buf, size, stdin)) == NULL)
            exit(0);
        buf[strlen(buf) - 1] = 0;
        if(strlen(buf) == 0)
            continue;
        for(int i=0;i<4; ++i)
            c[i] = buf[i];
        c[cmd] = 0;
        if((strcmp(c, "exit" )) == 0){
            printf("Good Bye\n");
            return 0;
            }
        else if((strcmp(c, "echo" )) == 0){
            for(int i=5;buf[i] != 0; ++i)
                printf("%c",buf[i]);
            printf("\n");
            continue;
            }
        else
            printf("Invalid command\n"); 
            continue;           
    }
    
    
  return 0;

}