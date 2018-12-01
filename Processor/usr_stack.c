/*
===========================================================================================================================================
                                                     file  "usr_stack.c"                     
===========================================================================================================================================
*/                              

#ifndef __USR_STACK_C
    #define __USR_STACK_C



//*****************#Includes***************************************//

#include "usr_stack.h"





/*
===========================================================================================================================================
                                                     internal functions
===========================================================================================================================================
*/



//*****************#CountChecksum**********************************//

#ifdef __DEBUG_STACK_CHECKSUM__

__uint128_t CountChecksum (stack* inp_stack)
{
    __uint128_t checksum_buf = 0;
    unsigned int i = 0;

    for (i = 0; i < (inp_stack->capacity * sizeof (data_type)); i++)
        checksum_buf += ((*(((unsigned char*) (inp_stack->data)) + i)) * (i + 1));
    
    return checksum_buf;
}

#endif




//*****************#ReCreateStk_function***************************//

int ReCreateStk (stack* inp_stack)
{
    //.......Check stack.............................

    CHECK_STK( RECREATESTK_ERROR);


    //.......Allocate memory.........................

    size_t new_size = 0;
    new_size = 2 * inp_stack->capacity * sizeof (data_type) + 2 * sizeof (unsigned int);

    CHECK( new_size < INT_MAX);
    if (new_size >= INT_MAX) return RECREATESTK_ERROR;


    void* old_ptr = NULL;
    old_ptr = (void*) (((unsigned int*) (inp_stack->data)) - 1);

    void* new_ptr = NULL;
    new_ptr = realloc (old_ptr, new_size);

    CHECK( new_ptr != NULL);
    if (new_ptr == NULL) return RECREATESTK_ERROR;


    //.......Calculate adress of arr start...........

    data_type* data = NULL;

    data = (data_type*) (((unsigned int*) new_ptr) + 1);


    //.......Init new array..........................

    int i = 0;

    for (i = inp_stack->capacity; i < 2 * inp_stack->capacity; i++)
        data [i] = STACK_INIT_VALUE;

    inp_stack->capacity *= 2;

    *((unsigned int*) (data + inp_stack->capacity)) = CANARY;

    inp_stack->data = data;

#ifdef __DEBUG_STACK_CHECKSUM__
    inp_stack->checksum = CountChecksum (inp_stack);
#endif



    //.......Exit from function......................

    CHECK_STK( RECREATESTK_ERROR);
    
    return RECREATESTK_OK;    
}




/*
===========================================================================================================================================
                                                     Init and Deinit function
===========================================================================================================================================
*/


//*****************#CreateStk_function*****************************//

stack* CreateStk ()
{
    //.......Create stack structure..................

    stack* outp_stack = NULL;

    outp_stack = (stack*) calloc (1, sizeof (stack));

    CHECK( outp_stack != NULL)
    if (outp_stack == NULL) return NULL;

    
    //.......Create data array.......................

    void* ptr_buf = NULL;

    ptr_buf = calloc (1, STACK_START_SIZE * sizeof (data_type) + 2 * sizeof (unsigned int));

    CHECK( ptr_buf != NULL);
    if (ptr_buf == NULL)
    {
        free (outp_stack);
        return NULL;
    }

    
    //.......Calculate adress of arr start...........

    data_type* data = NULL;
    
    data = (data_type*)  (((unsigned int*) ptr_buf) + 1);


    //.......Initialization of stack structure.......


    //.Stk canaries
    outp_stack->canary_1 = CANARY;
    outp_stack->canary_2 = CANARY;

    //.Counters
    outp_stack->capacity = STACK_START_SIZE;
    outp_stack->top      = 0;

    //.Pointer to data
    outp_stack->data     = data;

    //.Data canaries
    *(((unsigned int*) data) - 1) =                 CANARY;
    *((unsigned int*) (data + STACK_START_SIZE)) =  CANARY;

    //.Init data
    int counter = 0;

    for (counter = 0; counter < STACK_START_SIZE; counter++)
        data[counter] = STACK_INIT_VALUE;

    //.Init checksum

#ifdef __DEBUG_STACK_CHECKSUM__
    outp_stack->checksum = CountChecksum (outp_stack);
#endif


    //.......Exit from function......................

    CHECK( CheckStk (outp_stack) == CHECKSTK_OK);
    if ( CheckStk (outp_stack) != CHECKSTK_OK) return NULL;

    return outp_stack;
}


//*****************#DeleteStk_function*****************************//

int DeleteStk (stack* inp_stack)
{
    //.......Check stack.............................

    CHECK_STK( DELETESTK_ERROR_STACK)


    //.......Delete data.............................

    free (((unsigned int*) (inp_stack->data)) - 1);
    

    //.......Delete stack............................

    free (inp_stack);


    //.......Exit from function......................

    return DELETESTK_OK;
}








/*
===========================================================================================================================================
                                                     standart operating functions (push, pop)
===========================================================================================================================================
*/


//*****************#Push_function**********************************//

int Push (stack* inp_stack, data_type inp_data)
{
    //.......Check input.............................

    CHECK_STK( PUSH_ERROR_STACK);


    //.......Check recreating........................

    if (inp_stack->top >= inp_stack->capacity)
    {
        int recreatestk_ret = RECREATESTK_ERROR;

        recreatestk_ret = ReCreateStk (inp_stack);

        CHECK( recreatestk_ret == RECREATESTK_OK);
        if ( recreatestk_ret != RECREATESTK_OK) return PUSH_ERROR_RECREATE;
    }


    //.......Push elem...............................

    inp_stack->data [inp_stack->top] = inp_data;
    inp_stack->top++;

#ifdef __DEBUG_STACK_CHECKSUM__
    inp_stack->checksum = CountChecksum (inp_stack);
#endif
    

    //.......Exit from function......................

    CHECK_STK( PUSH_ERROR_STK_WAS_DAMAGED);

    return PUSH_OK;
}


//*****************#Pop_function***********************************//

int Pop (stack* inp_stack, data_type* outp_data)
{
    //.......Check input.............................

    CHECK( outp_data != NULL);
    if (outp_data == NULL) return POP_ERROR_INVALID_INPUT;


    //.......Check stack.............................

    CHECK_STK( POP_ERROR_STACK);


    //.......Check empty.............................

    if (inp_stack->top <= 0) return POP_STACK_EMPTY;


    //.......Pop elem................................

    *outp_data = inp_stack->data [(inp_stack->top) - 1];

    inp_stack->data [(inp_stack->top) - 1] = STACK_ERASE_VALUE;

    inp_stack->top--;

#ifdef __DEBUG_STACK_CHECKSUM__
    inp_stack->checksum = CountChecksum (inp_stack);
#endif


    //.......Exit from function......................

    CHECK_STK( POP_ERROR_STK_WAS_DAMAGED);

    return POP_OK;
}






/*
===========================================================================================================================================
                                                     debug and check functions
===========================================================================================================================================
*/


//*****************#CheckStk_function******************************//

int CheckStk (stack* inp_stack)
{
    //.......Check stk pointer.......................

    CHECK( inp_stack != NULL)
    if (inp_stack == NULL) return CHECKSTK_ERROR_STK_POINTER;


    //.......Check stk canaries......................
    
    CHECK( inp_stack->canary_1 == CANARY);
    CHECK( inp_stack->canary_2 == CANARY);

    if ((inp_stack->canary_1 != CANARY) || (inp_stack->canary_2 != CANARY))
        return CHECKSTK_ERROR_STK_CANARY;


    //.......Check shecksums.........................

#ifdef __DEBUG_STACK_CHECKSUM__
    CHECK( inp_stack->checksum == CountChecksum (inp_stack));
    if (inp_stack->checksum != CountChecksum (inp_stack)) return CHECKSTK_ERROR_CHECKSUM;
#endif


    //.......Check counters..........................

    CHECK( inp_stack->top >= 0);
    CHECK( inp_stack->top <= inp_stack->capacity);

    if ((inp_stack->top < 0) || (inp_stack->top > inp_stack->capacity))
        return CHECKSTK_ERROR_COUNTERS;


    //.......Check data canaries.....................

    CHECK( *(((unsigned int*) inp_stack->data) - 1) == CANARY);

    if (*(((unsigned int*) inp_stack->data) - 1) != CANARY)
        return CHECKSTK_ERROR_DATA_CANARY;

    CHECK( *((unsigned int*) (inp_stack->data + inp_stack->capacity)) == CANARY);

    if (*((unsigned int*) (inp_stack->data + inp_stack->capacity)) != CANARY)
        return CHECKSTK_ERROR_DATA_CANARY;


    //.......Exit from function......................

    return CHECKSTK_OK;
}



//*****************#DumpStk_function*******************************//

int DumpStk (stack* inp_stack)
{

#ifndef LOG_OUT_IN_COMMAND_LINE

    FILE* log_file = NULL;

    log_file = fopen ("Stack.log", "w");

    if (log_file == NULL) return DUMPSTK_ERROR_CREATING_LOGFILE;
#endif

#ifdef LOG_OUT_IN_COMMAND_LINE

    #define log_file stdout

#endif


    //.......Stk struct..............................

    fprintf (log_file, "\n\x1b[1;32mData Structure Stack\x1b[0m\n\n");


    //.Stack pointer

    fprintf (log_file, "Stack [ %p ] ", (void*) inp_stack);

    if (inp_stack == NULL)
    {
        fprintf (log_file, "\x1b[1;31mINVALID ADRESS\x1b[0m\n");
        return DUMPSTK_ERROR_STK_POINTER;
    }
    fprintf (log_file, "----------------------------valid adress\n\n{\n");


    //.Stack canary 1

    fprintf (log_file, "    Stack.canary_1 = 0x%X; ", inp_stack->canary_1);

    if (inp_stack->canary_1 != 0xBD5BD5BD)
        fprintf (log_file, "\x1b[1;31mCANARY SHOULD BE = 0xBD5BD5BD\x1b[0m\n");

    else fprintf (log_file, "--------------------valid value\n\n");


    //.Stack capacity

    fprintf (log_file, "    Stack.capacity = %d; ", inp_stack->capacity);

    if (inp_stack->capacity < STACK_START_SIZE)
        fprintf (log_file, "\x1b[1;31mCAPACITY SHOULD BE >= STACK_START_SIZE (= %d)\x1b[0m\n", STACK_START_SIZE);
    
    else fprintf (log_file, "----------------------------valid value\n\n");

    //.Stack top

    fprintf (log_file, "    Stack.top      = %d; ", inp_stack->top);

    if (inp_stack->top > inp_stack->capacity)
        fprintf (log_file, "\x1b[1;31mTOP SHOULD BE LESS THAN CAPACITY (= %d)\x1b[0m\n", inp_stack->capacity);
        
    else fprintf (log_file, "-----------------------------valid value\n\n");


    //.Stack data

    fprintf (log_file, "    Stack.data = [ %p ]; ", (void*) inp_stack->data);

    if (inp_stack->data == NULL)
    {
        fprintf (log_file, "\x1b[1;31mDATA POINTER SHOULD BE NOT NULL\x1b[0m\n");
        return DUMPSTK_ERROR_STK_DATA_PTR;
    }
    fprintf (log_file, "----------------valid value\n\n");

#ifdef __DEBUG_STACK_CHECKSUM__
    
    fprintf (log_file, "    Stack.checksum = %llu; ",  (unsigned long long int) inp_stack->checksum);

    if (inp_stack->checksum != CountChecksum (inp_stack))
        fprintf (log_file, "\x1b[1;31mCHECK SUM SHOULD BE EQUAL %llu\x1b[0m\n", (unsigned long long int) CountChecksum (inp_stack));

    else fprintf (log_file, "----------------valid value\n\n");

#endif


    //.Stack canary 2

    fprintf (log_file, "    Stack.canary_2 = 0x%X; ", inp_stack->canary_2);

    if (inp_stack->canary_2 != 0xBD5BD5BD)
        fprintf (log_file, "\x1b[1;31mCANARY SHOULD BE = 0xBD5BD5BD\x1b[0m\n");

    else fprintf (log_file, "--------------------valid value\n}\n\n");


    //.Data check

    int i = 0;
    data_type* data_arr = NULL;


    data_arr = inp_stack->data;

    
    //.Check data canary

   fprintf (log_file, "\n\nData canary 1 = 0x%X; ", *(((unsigned int*) data_arr) - 1));


    if ( *(((unsigned int*) data_arr) - 1) != 0xBD5BD5BD)
        fprintf (log_file, "\x1b[1;31mCANARY SHOULD BE = 0xBD5BD5BD\x1b[0m\n");

    else fprintf (log_file, "--------------------valid value\n");

    fprintf (log_file, "\x1b[1;32mSTACK DATA:\x1b[0m\n");

    fprintf (log_file, "\x1b[1;32m");

    for (i = 0; i < inp_stack->capacity; i++)
    {  
        if (i == inp_stack->top) fprintf (log_file, "\x1b[0m");

        fprintf (log_file, "data[ %d ] ", i);
        if (i < 100)
        {
            if (i < 10) fprintf (log_file, "  ");
            else fprintf (log_file, " ");
        }

        fprintf (log_file, "= "DUMP_SPECIFIER";\n", data_arr[i]);
    }
    fprintf (log_file, "\x1b[0m");

    fprintf (log_file, "Data canary 2 = 0x%X; ", *((unsigned int*) (data_arr + inp_stack->capacity)));

    if ( *((unsigned int*) (data_arr + inp_stack->capacity)) != 0xBD5BD5BD)
        fprintf (log_file, "\x1b[1;31mCANARY SHOULD BE = 0xBD5BD5BD\x1b[0m\n");

    else fprintf (log_file, "--------------------valid value\n\n");

    fprintf (log_file, "\n\n\x1b[1;32mSTACK DUMPED SUCCESSFULLY\n\n\x1b[0m");
    fprintf (log_file, "\x1b[0m");

#ifdef LOG_OUT_IN_COMMAND_LINE

    #undef log_file

#endif

#ifndef LOG_OUT_IN_COMMAND_LINE

    fclose (log_file);

#endif


    return DUMPSTK_OK;
}



#endif // __USR_STACK_C

/*
===========================================================================================================================================
                                                     End of the file
===========================================================================================================================================
*/
