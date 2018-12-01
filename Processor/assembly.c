//*****************#Includes***************************************//

#include "assembly.h"



//*****************#Main_function**********************************//

int main(int argc, char** argv)
{
    //.......Check input.............................

    if (argc == 1)
    {
        printf ("\x1b[1;31m\nWrite file name in command line arguments\n\x1b[0m");
        return 0;
    }
     

    //.......Copy input file to string...............

    char* str = NULL;
    long int str_size = 0;

    str = ReadText (argv[1], &str_size);

    if (str == NULL)
    {
        printf ("\n\x1b[1;31mERROR. Cannot open input file\n\n\x1b[0m");
        return -2;
    }


    //.......Update input string......................

    UpdateString (str);


    //.......Assembly input file......................

    int assembly_ret = ASSEMBLY_ERROR;

    if (argc == 2)
        assembly_ret = Assmbly (str, "a.bin", str_size);
    else
        assembly_ret = Assmbly (str, argv[2], str_size);

    free (str);

    if (assembly_ret == ASSEMBLY_OK) return 0;
    else printf ("\x1b[1;31mERROR. Assembly fault\n\x1b[0m");

    return -1;
}




//*****************#Assmbly_function********************************//

int Assmbly (const char* str, const char* file_name, const long int str_size)
{
    #define CMD_DEF( name, num, code, assem)                    \
                {                                               \
                    if (strcmp (buf, #name) == 0)               \
                    {                                           \
                        printf ("buf = %s\n", buf);             \
                        fprintf (file, "%c", (num));            \
                        (assem);                                \
                        continue;                               \
                    }                                           \
                }


    //......Check input..............................

    assert (str != NULL);
    assert (file_name != NULL);
    assert (str_size > 0);
    if (( str == NULL) || (file_name == NULL) || (str_size <= 0)) return ASSEMBLY_ERROR;


    //.......Open file...............................

    FILE* file = NULL;

    file = fopen (file_name, "w");

    assert (file != NULL);
    if (file == NULL)
    {
        printf ("\n\x1b[1;31mERROR\nCan not write in %s\x1b[0m", file_name);
        return ASSEMBLY_ERROR;
    }


    
    //.......Assembly................................
    
    char buf [CMD_MAX_SIZE] = {};
    long int ip = 0;
    int32_t data = 0;
    char p_data [30] = {};
    int p_data_sz = 0;
    long int jmp_array [10] = {};

    while (GiveStr (str, &ip, buf) != -1)
    {
        #include "commands.h"

        if (buf [0] == ':') 
    }
    fprintf (file, "%c", '\0');

    fclose (file);



    return ASSEMBLY_OK;     
}






int GiveStr (const char* str, long int* ip, char*  buf)
{
    int ip_buf = 0;
    int flag = 0; /* 0 - looking for a command
                   * 1 - copying command
                   * 2 - fast forward
                   */

    while (str [*ip] == '\n') (*ip) ++;


    while ((str [*ip] != '\0') && (str [*ip] != '\n'))
    {
        if (str [*ip] == ' ')
        {
            if (flag == 1) flag = 2;
        }
        else
        {
            if (flag == 0)
            {
                flag = 1;
                ip_buf = 0;
            }
            else
            {
                if (flag == 2)
                {
                    buf [ip_buf] = '\0';
                    return 0;
                }
            }
            buf [ip_buf] = str [*ip];
            ip_buf++;
        }

        (*ip)++;
    }

    while (str [*ip] == '\n') (*ip) ++;

    if ((flag == 1) || (flag == 2))
    {
        buf [ip_buf] = '\0';
        return 0;
    }

    return -1;
}



int GiveData (const char* str, long int* ip)
{
    int ret_data = 0;
    char* buf_str = NULL;

    ret_data = (int) strtol ((str + (*ip)), &buf_str, 10);

    *ip = (buf_str - str);

    return ret_data;
}




void UpdateString (char* stk)
{
    long int i = 0;

    while (stk [i] != '\0')
    {
        if ((stk [i] >= 'a') && (stk [i] <= 'z'))
        {
            i++;
            continue;
        }

        if ((stk [i] >= '0') && (stk [i] <= '9'))
        {
            i++;
            continue;
        }
        

        if ((stk [i] == '[') || (stk [i] == ']') || (stk [i] == '+') || (stk [i] == '-') || (stk [i] == '\n'))
        {
            i++;
            continue;
        }

        stk [i++] = ' ';
    }
}




void GivePushParam (const char* str, long int* ip, char* p_data, int* p_data_sz)
{
    int i = 0;
    int i_buf = 0;
    char data [32] = {};


    while ((str [(*ip) + i] != '\n') && (str [(*ip ) + i] != '\0'))
    {
        if (str [(*ip) + i] != ' ') data [i_buf++] = str [(*ip) + i];
        i++;
        if (i_buf >= 30)
        {
            printf ("Error here\n");
            return;
        }
    }
    data [i_buf] = '\0';


    ASM_PUSHPOP_REG( rax, 2, 1);
    ASM_PUSHPOP_REG( rbx, 2, 2);
    ASM_PUSHPOP_REG( rcx, 2, 3);
    ASM_PUSHPOP_REG( rdx, 2, 4);

    ASM_PUSHPOP_REG( [rax], 3, 1);
    ASM_PUSHPOP_REG( [rbx], 3, 2);
    ASM_PUSHPOP_REG( [rcx], 3, 3);
    ASM_PUSHPOP_REG( [rdx], 3, 4);


    p_data [0] = 1;
    *((int*) (p_data + 1)) = (int) strtol ( data, NULL, 10);
    *p_data_sz = 5;

    printf ("GivePushParam; data = %d\n", *((int*) (p_data + 1)));

    return;
}



void GivePopParam  (const char* str, long int* ip, char* p_data, int* p_data_sz)
{
    int i = 0;
    int i_buf = 0;
    char data [32] = {};


    while ((str [(*ip) + i] != '\n') && (str [(*ip ) + i] != '\0'))
    {
        if (str [(*ip) + i] != ' ') data [i_buf++] = str [(*ip) + i];
        i++;
        if (i_buf >= 30)
        {
            printf ("Error here\n");
            return;
        }
    }
    data [i_buf] = '\0';


    ASM_PUSHPOP_REG( rax, 1, 1);
    ASM_PUSHPOP_REG( rbx, 1, 2);
    ASM_PUSHPOP_REG( rcx, 1, 3);
    ASM_PUSHPOP_REG( rdx, 1, 4);

    ASM_PUSHPOP_REG( [rax], 2, 1);
    ASM_PUSHPOP_REG( [rbx], 2, 2);
    ASM_PUSHPOP_REG( [rcx], 2, 3);
    ASM_PUSHPOP_REG( [rdx], 2, 4);


    return;
}

void new_function (void)
{
	return;
}






