#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char buffer[128] = {0};

    char input[1];

    while (fgets(input, 2, stdin))
    {
        if (input[0] == 'z')
        {
            memset(buffer, 0, sizeof(buffer));
        }
        else if (input[0] == 'l')
        {
            for (int i = 0; i < 128; ++i)
            {
                printf("%02x ", buffer[i]);

                if ((i + 1) % 16 == 0)
                {
                    printf("\n");
                }
            }
        }
        //printf("got: %02x\n", input[0]);
    }
}