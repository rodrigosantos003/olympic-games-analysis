/**
 * @file stringWrap.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Wrapper for strings
 * @version 1
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#define STRING_MAX_LEN 100

typedef struct stringWrap
{
    char text[STRING_MAX_LEN];
} StringWrap;

/**
 * @brief Creates a StringWrap object
 *
 * @param str [in] String to create
 * @return StringWrap Object
 */
StringWrap stringWrapCreate(char *str);
