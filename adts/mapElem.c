/**
 * @file mapElem.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of map element for Map ADT
 * @version 1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <string.h>
#include "mapElem.h"

void mapKeyPrint(MapKey key)
{
    printf("%s", key.text);
}

void mapValuePrint(MapValue value)
{
    printf("%50s%50s%30d%20s%10d", value.athleteID, value.athleteName, value.gamesParticipations, value.firstGame, value.athleteBirth);
}

int mapKeyCompare(MapKey key1, MapKey key2)
{
    return strcmp(key1.text, key2.text);
}