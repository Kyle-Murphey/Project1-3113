#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "storage.h"

#define MAX_BUF 128
#define MAX_ARGS 4
#define STORAGE_NAME "storage.bin"

/* separators for tokens/inputs */
const char SEPARATORS[] = " \t\n";

/* renaming unsigned char to byte */
typedef unsigned char byte;

/*
 * stores integer value in the buffer
 */
void input_int(byte * args[], byte * buffer)
{
    byte * checkArgs = args[2]; //used to scan over inputs to check for invalid commands/values

    //checks each digit for int value
    for (int i = 0; i < strlen(args[2]); ++i)
    {
        if (*checkArgs != '-' && (*checkArgs < '0' || *checkArgs > '9'))
        {
            fprintf(stderr, "invalid integer\n");
            return;
        }
        ++checkArgs;
    }
    int value = atoi(args[2]); //value to store
    int location = atoi(args[1]); //location in buffer to get stored
    int * ptr_location = (int*)(&buffer[location]); //pointer to the location in the buffer to store value
    *ptr_location = value; //set val of location to inputted value
}

/*
 * stores byte value in the buffer
 */
void input_byte(byte * args[], byte * buffer)
{
    byte value = atoi(args[2]);
    int location = atoi(args[1]);
    byte * ptr_location = (byte*)(&buffer[location]);
    *ptr_location = value;
}

/*
 * main function
 */
int main(int argc, char **argv)
{
    byte buffer[MAX_BUF] = {0}; //buffer to store values in
    byte input[50]; //stores input from cl
    byte * args[MAX_ARGS] = {0}; //stores arguments from input
    byte ** arg; //pointer to arguments
    byte * checkArgs; //used to check for invalid commands

    STORAGE * file = init_storage(STORAGE_NAME); //open or create file for storage

    //main input loop, continues until EOF
    while (fgets(input, 50, stdin))
    {
        //tokenizes input and stores in args array
        arg = args;
        *arg++ = strtok(input, SEPARATORS);
        while((*arg++ = strtok(NULL, SEPARATORS)));

        //only enter is pressed
        if (args[0] == 0) continue;

        //checks if first input is only one character
        if (strlen(args[0]) != 1)
        {
            fprintf(stderr, "invalid command\n");
            continue;
        }
        checkArgs = args[1];

        //checks each digit for location
        for (int i = 0; i < strlen(args[1]); ++i)
        {
            if (*checkArgs < '0' || *checkArgs > '9' )
            {
                fprintf(stderr, "invalid location\n");
                continue;
            }
            ++checkArgs;
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
        //writes content from the buffer to the file
        else if (*args[0] == 'w')
        {
            int write = put_bytes(file, buffer, atoi(args[1]), atoi(args[2]));
        }
        //reads content from the file into the buffer
        else if (*args[0] == 'r')
        {
            int read = get_bytes(file, buffer, atoi(args[1]), atoi(args[2]));
        }
        //input integer value
        else if (*args[0] == 'i')
        {
            input_int(args, buffer);
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
            input_byte(args, buffer);
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
        //input string value
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
        //prints string value
        else if (*args[0] == 'S')
        {
            char * ptr_loc = (char*)(&buffer[atoi(args[1])]);
            printf("%s\n", ptr_loc);
        }
        //bad command
        else
        {
            fprintf(stderr, "invalid command\n");
        }
    }

    //closing file
    int close = close_storage(file);
}