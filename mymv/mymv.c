#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {

        if(argc < 3)
                exit(-1);

        if((rename( argv[1] , argv[2] )) < 0)
                exit(-2);

        return 0;
}
