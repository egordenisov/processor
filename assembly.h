#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usr_files.h"




const int ASSEMBLY_OK = 0;
const int ASSEMBLY_ERROR = -1;

#define CMD_MAX_SIZE 20



int GiveStr (const char* str, long int* ip, char*  buf);
int Assmbly (const char* str, const char* file_name, const long int str_size);
long int GiveData (const char* str, long int* ip);
char Find1R (const int data);
char Find2R (const int data);
char Find3R (const int data);
char Find4R (const int data);
void UpdateString (char* stk);
void GivePushParam (const char* str, long int* ip, char* p_data, int* p_data_sz);
void GivePopParam  (const char* str, long int* ip, char* p_data, int* p_data_sz);



#define ASM_PUSHPOP_REG( reg_name, com, reg)                            \
            {                                                           \
                if ( strcmp (#reg_name, data) == 0)                     \
                {                                                       \
                    p_data [0] = (com);                                 \
                    p_data [1] = (reg);                                 \
                    *p_data_sz = 2;                                     \
                    *ip += i;                                           \
                    return;                                             \
                }                                                       \
            }
