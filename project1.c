#include <stdio.h>
#include <string.h>

/* separators for tokens/inputs */
const char SEPARATORS[] = " \t\n";

/* renaming unsigned char to byte */
typedef unsigned char byte;


int main(int argc, char **argv)
{
    //const unsigned int BUFFER_SIZE = 128; //size of buffer
    ///*unsigned */int MAX_ARGS = 4; //max number of arguments

    byte buffer[128] /*= {1}*/;
    byte input[50];
    byte * args[4];
    byte ** arg;


    printf("Done.\n\n");

    while (fgets(input, 50, stdin))
    {
        //tokenizes input and stores in args array
        arg = args;
        *arg++ = strtok(input, SEPARATORS);
        while((*arg++ = strtok(NULL, SEPARATORS)));

        if (*args[0] == 'i')
        {
            
        }

        if (*args[0] == 'z')
        {
            memset(buffer, 0, sizeof(buffer));
        }
        else if (*args[0] == 'l')
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