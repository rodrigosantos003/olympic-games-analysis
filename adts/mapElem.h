/**
 * @file mapElem.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Map element for Map ADT
 * @version 1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../data_structures/stringWrap.h"
#include "../data_structures/athlete.h"

typedef StringWrap MapKey;
typedef Athlete MapValue;

/**
 * @brief Prints a map key
 *
 * @param key [in] Key to print
 */
void mapKeyPrint(MapKey key);

/**
 * @brief Prints a map value
 *
 * @param value [in] Value to print
 */
void mapValuePrint(MapValue value);

/**
 * @brief Compares two map keys
 *
 * @param key1 [in] Map key 1
 * @param key2 [in] Map key 2
 * @return int 0 if the keys are equal, other value otherwise
 */
int mapKeyCompare(MapKey key1, MapKey key2);