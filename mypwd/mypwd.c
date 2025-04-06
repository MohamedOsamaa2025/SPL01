#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define s 1000

int main(void)
{
    char buf[s];

    if (getcwd(buf, s) == NULL)
    {
        exit(-1);
    }

    printf("%s\n", buf);

    return 0;
}
