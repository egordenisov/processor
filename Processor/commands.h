/*
================================================================================================
                                Push / Pop commands
================================================================================================
*/

//*****************Push_data***************************************//

CMD_DEF( push, 1,                                                                                                                   \
                    {                                                                                                               \
                        switch (programm [ip + 1])                                                                                  \
                        {                                                                                                           \
                            case 1:                                                                                                 \
                                    data1 = *((int32_t*) (programm + ip + 2));                                                      \
                                    ip += 6;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 2:                                                                                                 \
                                    data1 = registers [ (int32_t) programm [ ip + 2]];                                              \
                                    ip += 3;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 3:                                                                                                 \
                                    data1 = ram [ registers [ (int32_t) programm [ ip + 2]]];                                       \
                                    ip += 3;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 4:                                                                                                 \
                                    data1 = ram [ registers [ (int32_t) programm [ip + 2]] + *((int32_t*) (programm + ip + 3))];    \
                                    ip += 7;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            default:                                                                                                \
                                    return PROCESSOR_ERROR_BINARY;                                                                  \
                            break;                                                                                                  \
                        }                                                                                                           \
                                                                                                                                    \
                        RET_EQUAL Push (stk, data1);                                                                                \
                                                                                                                                    \
                        ERROR_CHECK_STACKINPROCESSOR( func_ret == PUSH_OK);                                                         \
                    },                                                                                                              \
                                                                                                                                    \
                                                                                                                                    \
                    {                                                                                                               \
                        GivePushParam (str, &ip, p_data, &p_data_sz);                                                               \
                                                                                                                                    \
                        fwrite (p_data, sizeof (char), p_data_sz, file);                                                            \
                    })


//*****************Pop_data****************************************//

CMD_DEF( pop, 2,                                                                                                                    \
                    {                                                                                                               \
                        RET_EQUAL Pop (stk, &data1);                                                                                \
                                                                                                                                    \
                        ERROR_CHECK_STACKINPROCESSOR( func_ret == POP_OK);                                                          \
                                                                                                                                    \
                        switch (programm [ip + 1])                                                                                  \
                        {                                                                                                           \
                            case 1:                                                                                                 \
                                    registers [ (int32_t) programm [ ip + 2]] = data1;                                              \
                                    ip += 3;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 2:                                                                                                 \
                                    ram [ registers [ (int32_t) programm [ ip + 2]]] = data1;                                       \
                                    ip += 3;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 3:                                                                                                 \
                                    ram [ registers [ (int32_t) programm [ip + 2]] + *((int32_t*) (programm + ip + 3))] = data1;    \
                                    ip += 7;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            default:                                                                                                \
                                    return PROCESSOR_ERROR_BINARY;                                                                  \
                            break;                                                                                                  \
                        }                                                                                                           \
                    },                                                                                                              \
                                                                                                                                    \
                    {                                                                                                               \
                        GivePopParam (str, &ip, p_data, &p_data_sz);                                                                \
                                                                                                                                    \
                        fwrite (p_data, sizeof (char), p_data_sz, file);                                                            \
                    })





/*
================================================================================================
                                Arithmetic commands
================================================================================================
*/

//*****************Add*********************************************//

CMD_DEF( add, 10,                                                                           \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                        RET_EQUAL Pop (stk, &data2);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                                                                                            \
                        RET_EQUAL Push (stk, data2 + data1);                                \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })


//*****************Sub*********************************************//

CMD_DEF( sub, 11,                                                                           \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                        RET_EQUAL Pop (stk, &data2);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                                                                                            \
                        RET_EQUAL Push (stk, data2 - data1);                                \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })



//*****************Mul*********************************************//

CMD_DEF( mul, 12,                                                                           \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                        RET_EQUAL Pop (stk, &data2);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                                                                                            \
                        RET_EQUAL Push (stk, data2 * data1);                                \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })



//*****************Div*********************************************//

CMD_DEF( div, 13,                                                                           \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                        RET_EQUAL Pop (stk, &data2);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                                                                                            \
                        RET_EQUAL Push (stk, data2 / data1);                                \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })



//*****************Sqrt********************************************//

CMD_DEF( sqrt, 14,                                                                          \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                  \
                                                                                            \
                        RET_EQUAL Push (stk, (int32_t) (data1));                            \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })



/*
================================================================================================
                            `   In / Out command
================================================================================================
*/

//*****************Out_command*************************************//

CMD_DEF( out, 40,                                                                           \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                                                                                            \
                        ERROR_CHECK_STACKINPROCESSOR( func_ret == POP_OK);                  \
                                                                                            \
                        ip ++;                                                              \
                                                                                            \
                        printf ("%d", data1);                                               \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })


//*****************In_command**************************************//

CMD_DEF( in, 41,                                                                            \
                    {                                                                       \
                        scanf ("%d", &data1);                                               \
                                                                                            \
                        RET_EQUAL Push (stk, data1);                                        \
                                                                                            \
                        ERROR_CHECK_STACKINPROCESSOR( func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })


//*****************Outsymb_command*********************************//

CMD_DEF( outsymb, 42,                                                                       \
                    {                                                                       \
                        RET_EQUAL Pop (stk, &data1);                                        \
                                                                                            \
                        ERROR_CHECK_STACKINPROCESSOR( func_ret == POP_OK);                  \
                                                                                            \
                        ip ++;                                                              \
                                                                                            \
                        printf ("%c",  data1);                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })


//*****************Insymb_command**********************************//

CMD_DEF( insymb, 43,                                                                        \
                    {                                                                       \
                        scanf ("%c", (char*) &data1);                                       \
                                                                                            \
                        RET_EQUAL Push (stk, data1);                                        \
                                                                                            \
                        ERROR_CHECK_STACKINPROCESSOR( func_ret == PUSH_OK);                 \
                                                                                            \
                        ip ++;                                                              \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })



/*
================================================================================================
                                Jumps
================================================================================================
*/


CMD_DEF( jmp, 100,
                {
                    ip = programm [ip + 1];
                },

                {

                })


/*
================================================================================================
                                End of function command
================================================================================================
*/

//*****************End_command*************************************//

CMD_DEF( end, 127,                                                                          \
                    {                                                                       \
                        ip ++;                                                              \
                        free (ram);                                                         \
                        DeleteStk (stk);                                                    \
                        return PROCESSOR_OK;                                                \
                    },                                                                      \
                                                                                            \
                    {                                                                       \
                    })                                               
