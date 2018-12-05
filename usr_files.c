#ifndef __USR_FILES_C
    #define __USR_FILES_C


//*****************#Includes***************************************//

#include "usr_files.h"





//*****************#ReadText_function******************************//

char* ReadText (char* input_file, long int* string_size)
{
    //........Check_input..................

#ifdef __DEBUG_READTEXT__
    assert (input_file != NULL);
    assert (string_size != NULL);
#endif

    if ((input_file == NULL) || (string_size == NULL)) return NULL;


    //.......Open_file.....................

    FILE* input = NULL;

    input = fopen (input_file, "r"); /* Start function */

#ifdef __DEBUG_READTEXT__
    assert (input != NULL);
#endif

    if (input == NULL) return NULL;


    //.......Calculate_string_size.........
  
    int stat_return = -1;
    struct stat struct_for_search_filesize;

    struct_for_search_filesize.st_size = -1;

    stat_return = stat (input_file, &struct_for_search_filesize); /* Start function */

#ifdef __DEBUG_READTEXT__
    assert (stat_return == 0);
    assert (struct_for_search_filesize.st_size > 0);
#endif

    if ((stat_return != 0) || (struct_for_search_filesize.st_size <= 0)) return NULL;



    *string_size = struct_for_search_filesize.st_size;
    

    //.......Creating_string...............

    char* output_string = NULL;

    output_string = (char*) calloc (*string_size, sizeof (char)); /* Start function */

#ifdef __DEBUG_READTEXT__
    assert (output_string != NULL);
#endif

    if (output_string == NULL) return NULL;


    //.......Copy_file_to_the_string.......

    long int fread_return = 0;

    fread_return = fread (output_string, 1, *string_size, input); /* Start function */
    
#ifdef __DEBUG_READTEXT__
    assert (fread_return == *string_size);
#endif
    if (fread_return != *string_size) return NULL;


    output_string [*string_size - 1] = '\0';    

    //.......Close_file....................

    fclose (input);

    
    //.......Exit..........................

    return output_string;   
}

#endif // __USR_FILES_C
