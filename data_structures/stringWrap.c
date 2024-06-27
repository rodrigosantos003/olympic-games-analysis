/**
 * @file stringWrap.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of wrapper for strings
 * @version 1
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "stringWrap.h"
#include <string.h>

StringWrap stringWrapCreate(char *str)
{
    StringWrap sw;
    if (str != NULL)
    {
        strncpy(sw.text, str, STRING_MAX_LEN - 1);
        sw.text[STRING_MAX_LEN - 1] = '\0';
    }
    else
    {
        sw.text[0] = '\0';
    }
    return sw;
}