#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* separators for tokens/inputs */
const char SEPARATORS[] = " \t\n";

/* renaming unsigned char to byte */
typedef unsigned char byte;

/*
 * main function
*/
int main(int argc, char **argv)
{
    byte buffer[128] = {0}; //buffer to store values in
    byte input[50]; //stores input from cl
    byte * args[4]; //stores arguments from input
    byte ** arg; //pointer to arguments

    //main input loop, continues until EOF
    while (fgets(input, 50, stdin))
    {
        //tokenizes input and stores in args array
        arg = args;
        *arg++ = strtok(input, SEPARATORS);
        while((*arg++ = strtok(NULL, SEPARATORS)));

        //input integer value
        if (*args[0] == 'i')
        {
            int value = atoi(args[2]); //value to store
            int location = atoi(args[1]); //location in buffer to get stored
            int * ptr_location = (int*)(&buffer[location]); //pointer to the location in the buffer to store value
            *ptr_location = value; //set val of location to inputted value
        }
        //prints integer output
        else if (*args[0] == 'I')
        {
            int * ptr_loc = (int*)(&buffer[atoi(args[1])]); //pointer to location in buffer to read
            printf("%d\n", *ptr_loc); //print integer at given location
        }
        //input byte value
        else if (*args[0] == 'b')
        {
            byte value = atoi(args[2]);
            int location = atoi(args[1]);
            byte * ptr_location = (byte*)(&buffer[location]);
            *ptr_location = value;
        }
        //prints byte value
        else if (*args[0] == 'B')
        {
            byte * ptr_loc = (byte*)(&buffer[atoi(args[1])]);
            printf("%d\n", *ptr_loc);
        }
        //input hex value
        else if (*args[0] == 'h')
        {
            int hex = (int)strtol(args[2], NULL, 16);
            int location = atoi(args[1]);
            byte * ptr_location = (byte*)(&buffer[location]);
            *ptr_location = hex;
        }
        //prints hex value
        else if (*args[0] == 'H')
        {
            byte * ptr_loc = (byte*)(&buffer[atoi(args[1])]);
            printf("%02x\n", *ptr_loc);
        }
        //input char value
        else if (*args[0] == 'c')
        {
            char value = *args[2];
            int location =  atoi(args[1]);
            char * ptr_location = (char*)(&buffer[location]);
            *ptr_location = value;
        }
        //prints char value
        else if (*args[0] == 'C')
        {
            char * ptr_loc = (char*)(&buffer[atoi(args[1])]);
            printf("%c\n", *ptr_loc);
        }
        //input float value
        else if (*args[0] == 'f')
        {
            float value = atof(args[2]);
            int location = atoi(args[1]);
            float * ptr_location = (float*)(&buffer[location]);
            *ptr_location = value;
        }
        //prints float value
        else if (*args[0] == 'F')
        {
            float * ptr_loc = (float*)(&buffer[atoi(args[1])]);
            printf("%f\n", *ptr_loc);
        }
        else if (*args[0] == 's')
        {
            char * string = args[2];
            int strLength = strlen(args[2]);
            int location = atoi(args[1]);

            //stores each char of string into buffer
            for (int i = 0; i < strLength; ++i)
            {
                buffer[location++] = *string++;
            }
        }
        else if (*args[0] == 'S')
        {
            char * ptr_loc = (char*)(&buffer[atoi(args[1])]);
            printf("%s\n", ptr_loc);
        }
        //zero out the buffer
        else if (*args[0] == 'z')
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
        else
        {
            fprintf(stderr, "invalid command\n");
        }
    }
}