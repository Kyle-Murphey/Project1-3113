#include <stdio.h>
#include <string.h>

/* separators for tokens/inputs */
const char SEPARATORS[] = " \t\n";
/* size of buffer */
const unsigned int BUFFER_SIZE = 128;
/* max number of arguments */
const unsigned int MAX_ARGS = 3;

/* renaming unsigned char to byte */
typedef unsigned char byte;

int main(int argc, char **argv)
{
    byte buffer[BUFFER_SIZE] /*= {1}*/;
    byte input[1];

    printf("Done.\n\n");

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