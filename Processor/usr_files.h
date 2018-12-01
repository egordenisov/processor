//*****************# usr_files.h **********************************//

#ifndef __USR_FILES_H
    #define __USR_FILES_H


//*****************#Includes***************************************//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>


//*****************#Function_defnitons*****************************//

/*!
 *  Function creates new string and copies input file in it
 *
 *  \param[in]  input_file    Name of the input file
 *  \param[out] string_size   On this pointer are being wrote
 *                            number of elements in the string including '\0'
 *  
 *  \return                   Pointer to the string
 *
 */


char*   ReadText (char* input_file, long int* string_size);  



#include "usr_files.c"

#endif      // __USR_FILES_H

//*****************# end of the file ******************************//
