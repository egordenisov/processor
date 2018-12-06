//*****************#Includes***************************************//

#include <stdio.h>
#include <assert.h>
#include "usr_stack.h"



//*****************#Defines****************************************//

#define CHECK_RET( cond, ptr )              \
    {                                       \
        if ( !(cond) )                      \
        {                                   \
            DumpStk ( ptr );                \
            DeleteStk ( ptr);               \
                                            \
            assert (! #cond );              \
                                            \
            return -1;                      \
        }                                   \
    }



//*****************#Functions_definitions**************************//

int test_1 (void);

int test_2 (void);

int test_3 (void);

int test_4 (void);

int test_5 (void);



//*****************#Main_function**********************************//

int main ()
{
    assert ( !test_1() );


    assert ( !test_2() );

#ifndef __DEBUG_STACK_CHECKSUM__
    assert ( !test_3() );
#endif

    assert ( !test_4() );

#ifdef __DEBUG_STACK_CHECKSUM__
    assert ( !test_5() );
#endif

    return 0;
}





//*****************Test_1_standart_work****************************//

int test_1 (void)
{
    printf ("Test_1\n-- Creating stack\n-- Creating array with 100 elements\n-- Write random data to array\n");
    printf ("-- Write data to stack\n-- Read data from stack and check it\n\n");


    //.......Creating stack..........................

    stack* stk = NULL;

    stk = CreateStk ();

    CHECK_RET( stk != NULL, stk);


    //.......Creating array..........................

    data_type test_arr [100] = {};


    //.......Init array by random data and push it...

    int i = 0;

    for (i = 0; i < 100; i++)
    {
        test_arr [i] = (data_type) random();
        CHECK_RET( Push (stk, test_arr [i]) == PUSH_OK, stk);
    }


    data_type data_buf = 0;
    DumpStk (stk);

    //.......Pop and check data......................

    for (i =99; i >= 0; i--)
    {
        CHECK_RET( Pop (stk, &data_buf) == POP_OK, stk);
        CHECK_RET( data_buf == test_arr [i], stk);
    }

    CHECK_RET( Pop (stk, &data_buf) == POP_STACK_EMPTY, stk);




    CHECK_RET( DeleteStk (stk) == DELETESTK_OK, stk);

    printf("\n\x1b[1;32mTEST_1 COMPLETED SUCCESSFULLY\x1b[0m\n\n");

    return 0;
}



//*****************#Test_2*****************************************//

int test_2 (void)
{
    printf ("Test_2\n-- Creating 2 stacks\n-- Creating 2 array with 32 elements\n-- Write random data to arrays\n");
    printf ("-- Write data to stacks\n-- Read data from stacks and check it\n\n");

    stack* stk1 = NULL;
    stack* stk2 = NULL;

    stk1 = CreateStk ();
    stk2 = CreateStk ();

    CHECK_RET( stk1 != NULL, stk1);
    CHECK_RET( stk2 != NULL, stk2);


    data_type data1 [32] = {};
    data_type data2 [32] = {};

    int i = 0;

    for (i = 0; i < 32; i++)
    {
        data1 [i] = random ();
        data2 [i] = random ();

        CHECK_RET( Push( stk1, data1 [i]) == PUSH_OK, stk1);
        CHECK_RET( Push( stk2, data2 [i]) == PUSH_OK, stk2);
    }


    data_type data_buf = 0;

    for (i = 31; i >= 0; i--)
    {
        CHECK_RET( Pop ( stk1, &data_buf) == POP_OK, stk1);
        CHECK_RET( data_buf == data1 [i], stk1);

        CHECK_RET( Pop ( stk2, &data_buf) == POP_OK, stk2);
        CHECK_RET( data_buf == data2 [i], stk2);
    }

    CHECK_RET( Pop ( stk1, &data_buf) == POP_STACK_EMPTY, stk1);
    CHECK_RET( Pop ( stk2, &data_buf) == POP_STACK_EMPTY, stk2);

    
    CHECK_RET( DeleteStk( stk1) == DELETESTK_OK, stk1);
    CHECK_RET( DeleteStk( stk2) == DELETESTK_OK, stk2);

    printf("\n\x1b[1;32mTEST_2 COMPLETED SUCCESSFULLY\x1b[0m\n\n");

    return 0;
}


//*****************#Test_3*****************************************//

int test_3 (void)
{
    printf ("Test_3\n-- Creating stack\n-- Write elements to stack while it is possible\n");

    stack* stk = NULL;

    stk = CreateStk ();

    CHECK_RET( stk != NULL, stk);

    int push_ret = PUSH_ERROR;
    data_type data = 0;

    data = (data_type) random();

    while (1)
    {
        push_ret = Push (stk, data);

        if (push_ret == PUSH_ERROR_RECREATE) break;

        CHECK_RET( push_ret == PUSH_OK, stk);
    }


    CHECK_RET( DeleteStk ( stk) == DELETESTK_OK, stk);

    printf("\n\x1b[1;32mTEST_3 COMPLETED SUCCESSFULLY\x1b[0m\n\n");
    
    return 0;
}


//*****************#Test_4*****************************************//

int test_4 (void)
{
    printf ("Test_4\n-- Creating stack\n-- Breaking data canary\n");


    stack* stk = NULL;

    stk = CreateStk ();

    CHECK_RET( stk != NULL, stk);

    *(((char*) (stk->data)) - 1) = 0;

    int ret = CHECKSTK_ERROR;

    ret = CheckStk (stk);

    printf ("Function CheckStk returns: %d\n", ret);

    DumpStk (stk);

    CHECK_RET( ret != CHECKSTK_OK, stk);

    printf("\n\x1b[1;32mTEST_4 COMPLETED SUCCESSFULLY\x1b[0m\n\n");


    return 0;
}




//*****************#Test_5*****************************************//

int test_5 (void)
{
    printf ("Test_4\n-- Creating stack\n-- Breaking data\n");

    stack* stk = NULL;

    stk = CreateStk ();

    CHECK_RET( stk != NULL, stk);

    int i = 0;

    for (i = 0; i < 64; i++)
        CHECK_RET( Push (stk, ((data_type) random ())) == PUSH_OK, stk);


    data_type data_buf = 0;

    data_buf = stk->data [63];
    stk->data [63] = stk->data [18];
    stk->data [18] = data_buf;

    int ret = CHECKSTK_ERROR;

    ret = CheckStk (stk);

    printf ("Function CheckStk returns: %d\n", ret);

    DumpStk (stk);

    CHECK_RET( ret != CHECKSTK_OK, stk);

    printf("\n\x1b[1;32mTEST_5 COMPLETED SUCCESSFULLY\x1b[0m\n\n");


    return 0;
}












