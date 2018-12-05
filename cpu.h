#ifndef __CPU_H
    #define __CPU_H


//*****************#Includes***************************************//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "usr_files.h"
#include "usr_stack.h"




#define __DEBUG_CPU__

//*****************#Functions_definitions**************************//

int Processor (char* programm, long int prog_size);
int ProcRetSwitch (int processor_return);






//*****************#Constants**************************************//


#define RAM_SIZE                             2097152
#define REGISTERS_NUMBER                     8

#define PROCESSOR_OK                         0
#define PROCESSOR_ERROR_UNKNOWN             -1
#define PROCESSOR_ERROR_BINARY              -2
#define PROCESSOR_ERROR_INPINVALID          -3
#define PROCESSOR_ERROR_STACK               -4
#define PROCESSOR_ERROR_EOF                 -5
#define PROCESSOR_ERROR_INPFILE             -6
#define PROCESSOR_ERROR_ALLOCMEM            -7





//*****************#Defines****************************************//


#ifdef __DEBUG_CPU__
    #define ERROR_CHECK_STACKINPROCESSOR( condition )                                       \
        {                                                                                   \
            assert ( condition );                                                           \
                                                                                            \
            if ( ! (condition))                                                             \
            {                                                                               \
                free (ram);                                                                 \
                DeleteStk (stk);                                                            \
                return PROCESSOR_ERROR_STACK;                                               \
            }                                                                               \
        }


    #define RET_EQUAL func_ret =
#endif


#ifndef __DEBUG_CPU__
    #define ERROR_CHECK_STACKINPROCESSOR( condition )                                       ;

    #define RET_EQUAL
#endif









#endif // __CPU_H
