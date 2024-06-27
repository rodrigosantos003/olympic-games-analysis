/**
 * @file disciplines_analysis.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Functions to analyze medals data
 * @version 1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../adts/set.h"
#include "../data_structures/stringWrap.h"
#include "../data_structures/medal.h"
#include "../adts/list.h"

typedef struct disciplineAppearenceCount
{
    StringWrap discipline;
    PtSet slugs;
    int count;
} DisciplineAppearenceCount;

/**
 * @brief Counts the appearences of each discipline
 *
 * @param medals [in] List of medals
 */
void countDisciplineAppearences(PtList medals);

/**
 * @brief Get the Disciplines object
 *
 * @param medals [in] List of medals
 * @return PtSet Set of disciplines,
 * @return NULL if an error occured
 */
PtSet getDisciplines(PtList medals);

/**
 * @brief Swap two DisciplineAppearenceCount values
 *
 * @param a [in] Discipline a
 * @param b [in] Discipline b
 */
void disciplineSwap(DisciplineAppearenceCount *a, DisciplineAppearenceCount *b);

/**
 * @brief Partition function for DisciplineAppearenceCount values
 *
 * @param values [in] Values to sort
 * @param low [in] Low index
 * @param high [in] High index
 * @return int Partition index
 */
int disciplinePartition(DisciplineAppearenceCount *values, int low, int high);

/**
 * @brief Sorts DisciplineAppearenceCount values
 *
 * @param values [in] Values to sort
 * @param low [in] Low index
 * @param high [in] High index
 */
void disciplineSort(DisciplineAppearenceCount *values, int low, int high);