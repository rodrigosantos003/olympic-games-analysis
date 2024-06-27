/**
 * @file loading.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Functions to load data from files
 * @version 1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../adts/map.h"
#include "../adts/list.h"
#include "../data_structures/athlete.h"
#include "../data_structures/medal.h"
#include "../data_structures/host.h"

/**
 * @brief Load the athletes from a file
 *
 * @param athletes [in] Athlete Map
 */
void LOAD_A(PtMap athletes);

/**
 * @brief Load the medals from a file
 *
 * @param medals [in] Medal list
 */
void LOAD_M(PtList medals);

/**
 * @brief Load the hosts from a file
 *
 * @param hosts [in] Hosts array
 * @param size [in] New size of the array
 * @return int Quantity of hosts loaded
 */
void LOAD_H(Host **hosts, int *size);
