#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define size 100


int main(int argc, char *argv[]) {

        int srcfd,desfd,readn;
        char buf[size];

        if(argc < 3)
                exit(-1);
        srcfd = open( argv[1] , O_RDONLY );

        if(srcfd < 0)
                exit(-2);
        // desfd = open( argv[2] , O_WRONLY );
        desfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

        if(srcfd < 0)
                exit(-3);

        while((readn = read(srcfd,buf,size)) > 0)
                if((write(desfd , buf , readn)) < 0)
                exit(-4);

        return 0;
}