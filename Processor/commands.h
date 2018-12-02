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
                                    data1 = *((int32_t*) (ram + registers [ (int32_t) programm [ ip + 2]]));                        \
                                    ip += 3;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 4:                                                                                                 \
                                    data1 = *((int32_t*) (ram + registers [ (int32_t) programm [ip + 2]] + *((int32_t*) (programm + ip + 3))));\
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
                                                                                                                                    \
                        prog_ip += p_data_sz;                                                                                       \
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
                                    *((int32_t*) (ram + registers [ (int32_t) programm [ ip + 2]])) = data1;                        \
                                    ip += 3;                                                                                        \
                            break;                                                                                                  \
                                                                                                                                    \
                            case 3:                                                                                                 \
                                    *((int32_t*) (ram + registers [ (int32_t) programm [ip + 2]] + *((int32_t*) (programm + ip + 3)))) = data1;\
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
                                                                                                                                    \
                        prog_ip += p_data_sz;                                                                                       \
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
                        RET_EQUAL Push (stk, (int32_t) sqrt((double) data1));               \
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


CMD_DEF( jmp, 100,                                                                             \
                {                                                                              \
                    ip = *((long int*) (programm + ip + 1));                                   \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })



CMD_DEF( je, 101,                                                                              \
                {                                                                              \
                    RET_EQUAL Pop (stk, &data1);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    RET_EQUAL Pop (stk, &data2);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    if (data2 == data1)                                                        \
                        ip = *((long int*) (programm + ip + 1));                               \
                    else                                                                       \
                        ip += 9;                                                               \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })


CMD_DEF( jne, 102,                                                                             \
                {                                                                              \
                    RET_EQUAL Pop (stk, &data1);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    RET_EQUAL Pop (stk, &data2);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    if (data2 != data1)                                                        \
                        ip = *((long int*) (programm + ip + 1));                               \
                    else                                                                       \
                        ip += 9;                                                               \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })

CMD_DEF( jb, 103,                                                                              \
                {                                                                              \
                    RET_EQUAL Pop (stk, &data1);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    RET_EQUAL Pop (stk, &data2);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    if (data2 < data1)                                                         \
                        ip = *((long int*) (programm + ip + 1));                               \
                    else                                                                       \
                        ip += 9;                                                               \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })


CMD_DEF( jbe, 104,                                                                             \
                {                                                                              \
                    RET_EQUAL Pop (stk, &data1);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    RET_EQUAL Pop (stk, &data2);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    if (data2 <= data1)                                                        \
                        ip = *((long int*) (programm + ip + 1));                               \
                    else                                                                       \
                        ip += 9;                                                               \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })



CMD_DEF( ja, 105,                                                                              \
                {                                                                              \
                    RET_EQUAL Pop (stk, &data1);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    RET_EQUAL Pop (stk, &data2);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    if (data2 > data1)                                                         \
                        ip = *((long int*) (programm + ip + 1));                               \
                    else                                                                       \
                        ip += 9;                                                               \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })


CMD_DEF( jae, 106,                                                                             \
                {                                                                              \
                    RET_EQUAL Pop (stk, &data1);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    RET_EQUAL Pop (stk, &data2);                                               \
                    ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                         \
                                                                                               \
                    if (data2 >= data1)                                                        \
                        ip = *((long int*) (programm + ip + 1));                               \
                    else                                                                       \
                        ip += 9;                                                               \
                },                                                                             \
                                                                                               \
                {                                                                              \
                    if (str [ip] == ':')                                                       \
                    {                                                                          \
                        fwrite ( jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);\
                        ip += 2;                                                               \
                    }                                                                          \
                    else                                                                       \
                    {                                                                          \
                        long int givedataret = GiveData ( str, &ip);                           \
                        fwrite ( &givedataret, sizeof (long int), 1, file);                    \
                    }                                                                          \
                                                                                               \
                    prog_ip += sizeof (long int);                                              \
                })

/*
================================================================================================
                                Function's calls
================================================================================================
*/


CMD_DEF( call, 90,                                                                                  \
                    {                                                                               \
                        RET_EQUAL Push (ret_stk, (int) (ip + 9));                                   \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == PUSH_OK);                         \
                                                                                                    \
                        ip = *((long int*) (programm + ip + 1));                                    \
                    },                                                                              \
                                                                                                    \
                    {                                                                               \
                        fwrite (jmp_array + (str [ip + 1] - '0'), sizeof (long int), 1, file);      \
                        ip += 2;                                                                    \
                        prog_ip += sizeof (long int);                                               \
                    })



CMD_DEF( ret, 91,                                                                                   \
                    {                                                                               \
                        RET_EQUAL Pop (ret_stk, &data1);                                            \
                        ERROR_CHECK_STACKINPROCESSOR (func_ret == POP_OK);                          \
                                                                                                    \
                        ip = (long int) data1;                                                      \
                    },                                                                              \
                                                                                                    \
                    {                                                                               \
                    })




/*
================================================================================================
                                End of function command
================================================================================================
*/

//*****************End_command*************************************//

CMD_DEF( end, 127,                                                                                  \
                    {                                                                               \
                        ip ++;                                                                      \
                        free (ram);                                                                 \
                        DeleteStk (stk);                                                            \
                        return PROCESSOR_OK;                                                        \
                    },                                                                              \
                                                                                                    \
                    {                                                                               \
                    })                                               
