//*****************#Usr_stack.h************************************//

#ifndef __USR_STACK_H
    #define __USR_STACK_H


typedef int data_type;

/* ATTENTION!!!
 * For using this lib you should write
 * typedef data_type 
 */



//*****************#Includes***************************************//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>


//*****************#Settings***************************************//



#define LOG_OUT_IN_COMMAND_LINE

#define DUMP_SPECIFIER "%d"

//#define __DEBUG_STACK__

//#define __DEBUG_STACK_CHECKSUM__

//*****************#Structures*************************************//


typedef struct stack_buf
{
    unsigned int canary_1;

    int capacity;

    int top;

    data_type* data;

#ifdef __DEBUG_STACK_CHECKSUM__
    __uint128_t checksum;
#endif

    unsigned int canary_2;

} stack;





//*****************#Constants**************************************//

const int STACK_START_SIZE =                 16;
const int STACK_INIT_VALUE =                -1;
const int STACK_ERASE_VALUE =               -2;

const unsigned int CANARY =                  0xBD5BD5BD;

const int POP_OK =                           0;
const int POP_STACK_EMPTY =                  1;
const int POP_ERROR_STK_WAS_DAMAGED =       -1;
const int POP_ERROR_INVALID_INPUT =         -2;
const int POP_ERROR_STACK =                 -3;
const int POP_ERROR =                       -4;

const int PUSH_OK =                          0;
const int PUSH_ERROR_RECREATE =             -1;
const int PUSH_ERROR_STACK =                -2;
const int PUSH_ERROR_STK_WAS_DAMAGED =      -3;
const int PUSH_ERROR =                      -4;

const int DELETESTK_OK =                     0;
const int DELETESTK_ERROR_STACK =           -1;
const int DELETESTK_ERROR =                 -2;

const int RECREATESTK_OK =                   0;
const int RECREATESTK_ERROR =               -1;

const int DUMPSTK_OK =                       0;
const int DUMPSTK_ERROR_CREATING_LOGFILE =  -1;
const int DUMPSTK_ERROR_STK_POINTER =       -2;
const int DUMPSTK_ERROR_STK_DATA_PTR =      -3;
const int DUMPSTK_ERROR =                   -4;

const int CHECKSTK_OK =                      0;
const int CHECKSTK_ERROR_STK_POINTER =      -1;
const int CHECKSTK_ERROR_STK_CANARY =       -2;
const int CHECKSTK_ERROR_COUNTERS =         -3;
const int CHECKSTK_ERROR_DATA_CANARY =      -4;

#ifdef __DEBUG_STACK_CHECKSUM__
const int CHECKSTK_ERROR_CHECKSUM =         -5;
#endif

const int CHECKSTK_ERROR =                  -6;







//*****************#Defines****************************************//

#ifdef __DEBUG_STACK__

    #define CHECK( condition )                                                  \
        {                                                                       \
            assert ( condition );                                               \
        }

#endif

#ifndef __DEBUG_STACK__
    #define CHECK( condition )              ;

#endif



#define CHECK_STK( ret )                                                        \
    {                                                                           \
        CHECK( CheckStk (inp_stack) == CHECKSTK_OK);                            \
        if ( CheckStk (inp_stack) != CHECKSTK_OK) return ( ret );               \
    }



//*****************#Functions_descriptions*************************//


/*!
 *
 *
 */


stack* CreateStk ();


int DeleteStk   (stack* inp_stack);


int Pop         (stack* inp_stack, data_type* outp_data);


int Push        (stack* inp_stack, data_type  inp_data);


int DumpStk     (stack* inp_stack);


int CheckStk    (stack* inp_stack);




#endif // __USR_STACK_H



#include "usr_stack.c"


//*****************#End_of_file************************************//
