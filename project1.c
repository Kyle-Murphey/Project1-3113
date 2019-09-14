#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char buffer[128] = {1};

    char input[1];

    while (fgets(input, 2, stdin))
    {
        printf("got: %02x\n", input[0]);
    }
}