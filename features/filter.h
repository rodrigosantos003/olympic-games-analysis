/**
 * @file filter.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Functions to filter data
 * @version 1
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#define ATHELETES_NOT_FOUND -1

#include "../data_structures/athlete.h"

/**
 * @brief Sort the athletes by name
 *
 * @param athletes [in] Array of athlete values
 * @return Pointer for the allocated array containing the sorted athlete values,
 * @return NULL if an error occurred
 */
Athlete *sortAthletesByName(Athlete *athletes, int length);

/**
 * @brief Form a batch of ahtlete data
 *
 * @param athletes [in] Array of athlete values
 * @param batchStart [in] Start of the batch
 * @param batchSize [in] Size of the batch
 * @return Pointer for the allocated array containing the batch of athlete values,
 * @return NULL if an error occurred
 */
Athlete *formBatch(Athlete *athletes, int batchStart, int batchSize);

/**
 * @brief Get the athletes with the given birth year
 *
 * @param athletes [in] Array of athlete values
 * @param year [in] Birth year to search
 * @return Pointer for the allocated array containing the athletes with the given birth year,
 * @return NULL if none is found
 */
Athlete *athletesofYear(Athlete *athletes, int size, int year, int *foundAthletes);

/**
 * @brief Get the athletes that were younger than the given age on their first participation
 *
 * @param athletes [in] Array of athlete values
 * @param age [in] Age to search
 * @return Pointer for the allocated array containing the athletes that were younger than the given age on their first participation,
 * @return NULL if none is found
 */
Athlete *athletesofAge(Athlete *athletes, int size, int age, int *foundAthletes);

/**
 * @brief Paginate the athletes info
 *
 * @param athletes [in] Array of athlete values
 * @param size [in] Size of the data
 * @param batchStart [in] Start of the batch
 * @param batchSize [in] Size of the batch
 * @param command [in] Command executed
 */
void paginate(Athlete *athletes, int size, int batchStart, int batchSize, char *command);

/**
 * @brief Get the number athletes that played in a given Game edition
 *
 * @param athletes [in] Array of athlete values
 * @param size [in] Array of athletes size
 * @param gameSlug [in] Game Edition
 * @param size [in] Array of athletes size
 * @param foundAthletes_firstTime [out] Number of first time Athletes found
 * @param foundAthletes_OnlyTime [out] Number of first and only time Athletes found
 * @param size [in] Array of athletes size
 * @return Mean of the age of all the athletes  found in that game edition that played in it for the first time
 * @return -1 if none is found
 */
float athletesofGameEditions(Athlete *athletes, int size, char *gameSlug, int *foundAthletes_firstTime, int *foundAthletes_OnlyTime);
