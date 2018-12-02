/*
===========================================================================================================================================
                                                    file cpu.c
===========================================================================================================================================
*/


//*****************#Includes***************************************//

#include "cpu.h"



//*****************#Main_function**********************************//

int main (int argc, char** argv)
{
    //.......Check input.............................

    if (argc == 1)
    {
        printf ("\x1b[1;31m\nWrite file name in command line arguments\n\x1b[0m");
        return 0;
    }


    //.......Write programm to string................

    char* programm = NULL;
    long int prog_size = 0;

    programm = (char*) ReadText (argv[1], &prog_size);

    if ((programm == NULL) || (prog_size < 1))
    {
        printf ("\x1b[1;31mERROR. Cannot open binary file\n\x1b[0m");
        return -1;
    }


    //.......Program launch..........................

    int processor_return = PROCESSOR_ERROR_UNKNOWN;

    processor_return = processor (programm, prog_size);

    free (programm);

    return ProcRetSwitch (processor_return);
}




//*****************#ProcRetSwitch_function*************************//

int ProcRetSwitch (int processor_return)
{
    switch (processor_return)
    {
        case PROCESSOR_OK:
                            return 0;
        break;

        case PROCESSOR_ERROR_BINARY:
                            printf ("\x1b[1;31m\n\nInful file consists invalid symbols or commands\n\n\x1b[0m");
                            return -1;
        break;

        case PROCESSOR_ERROR_UNKNOWN:
                            printf ("\x1b[1;31m\n\nERROR unknown\n\n\x1b[0m");
                            return -1;
        break;

        case PROCESSOR_ERROR_ALLOCMEM:
                            printf ("\x1b[1;31m\n\nERROR no enought memory\n\n\x1b[0m");
                            return -1;
        break;

        case PROCESSOR_ERROR_STACK:
                            printf ("\x1b[1;31m\n\nStack error\n\n\x1b[0m");
                            return -1;
        break;

        case PROCESSOR_ERROR_EOF:
                            printf ("\x1b[1;31m\n\nEnd of file without end command\x1b[0m\n\n");
                            return -1;
        break;

        case PROCESSOR_ERROR_INPINVALID:
                            printf ("\x1b[1;31m\n\nInvalid input in function 'processor'\x1b[0m\n\n");
                            return -1;

        default:
                            printf ("\x1b[1;31m\n\nFunction processor returns unknown number = %d\n\n\x1b[0m", processor_return);
                            return -1;

        break;
    }

    
    return -2;
}



//*****************#Processor_function*****************************//

int processor (char* programm, long int prog_size)
{

#define CMD_DEF( name, num, code, assem )   \
        case (num):                         \
                    (code);                 \
        break;                              \



    //.......Check_input.............................

    assert (programm != NULL);
    assert (prog_size > 0);
    if ((programm == NULL) || (prog_size <= 0)) return PROCESSOR_ERROR_INPINVALID;
    
    
    //.......Creating data structs (RAM, reg, stack).
    
    int32_t registers [REGISTERS_NUMBER] = {};


    char* ram = NULL;
    ram = (char*) calloc (RAM_SIZE, sizeof (char));

    assert (ram != NULL);
    if (ram == NULL) return PROCESSOR_ERROR_ALLOCMEM;


    stack* stk = NULL;
    stk = CreateStk ();
    
    stack* ret_stk = NULL;
    ret_stk = CreateStk ();

    assert (stk != NULL);
    assert (ret_stk != NULL);
    if ((stk == NULL) || (ret_stk == NULL))
    {
        free (ram);
        return PROCESSOR_ERROR_STACK;
    }


    //.......Creating buf elements...................


    long int ip = 0;
    
    int32_t data1 = 0;
    int32_t data2 = 0;
   
#ifdef __DEBUG_CPU__ 
    int func_ret = 0;
#endif // __DEBUG_CPU__
    
        
    //.......Launch programm.........................
    while (1)
    {
        if (ip >= prog_size)
        {
            free (ram);
            DeleteStk (stk);
            return PROCESSOR_ERROR_EOF;
        }    

        switch (programm [ip])
        {
            #include "commands.h"

            default:
                    free (ram);
                    DeleteStk (stk);
                    DeleteStk (ret_stk);
                    return PROCESSOR_ERROR_BINARY;
            break;
        }
    }


    //.......Exir from fumction......................

    free (ram);
    DeleteStk (stk);
    DeleteStk (ret_stk);
    
    return PROCESSOR_ERROR_UNKNOWN;

#undef CMD_DEF
}
