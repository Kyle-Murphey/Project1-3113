#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* separators for tokens/inputs */
const char SEPARATORS[] = " \t\n";

/* renaming unsigned char to byte */
typedef unsigned char byte;


int main(int argc, char **argv)
{
    //const unsigned int BUFFER_SIZE = 128; //size of buffer
    ///*unsigned */int MAX_ARGS = 4; //max number of arguments

    byte buffer[128] = {0};
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
            int intVal = atoi(args[2]);
            int intLoc = atoi(args[1]);
            int * intLocation = (int*)(&buffer[intLoc]);
            printf("0x%02x\n", atoi(args[2]));

            *intLocation = intVal;
        }
        //prints integer output
        else if (*args[0] == 'I')
        {
            byte output[50] = {0}; //output array
            int j = 0; //index for output array
            int total = 0; //total integer value
            const int base = 16; //hex is base 16
            int factor = 0; //factor increases by 2 for each group of bytes

            //starts at index specified by arg, and increments until \0 (empty mem in buffer) and stores into output array
            for (int i = atoi(args[1]); buffer[i] != '\0'; ++i)
            {
                output[j++] = buffer[i];
            }

            int length = strlen(output); //number of hexes to parse
            
            //takes each hex value as a decimal and sums up the entries to give total int value
            for (int i = 0; i < length; ++i)
            {
                total += (output[i] * pow(base, factor));
                factor += 2;
            }
            //output integer
            printf ("%d\n", total);
        }
        //zero out the buffer
        if (*args[0] == 'z')
        {
            memset(buffer, 0, sizeof(buffer));
        }
        //list contents of buffer
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