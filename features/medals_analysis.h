/**
 * @file medals_analysis.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Functions to analyze medals data
 * @version 1
 * @date 2024-05-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../adts/list.h"

typedef struct medalCount
{
    char game[MAX_GAME_LENGTH];
    char country[MAX_COUNTRY_LENGTH];
    int gold;
    int silver;
    int bronze;
} MedalCount;

/**
 * @brief Searches the index of a country on the countries array
 *
 * @param countries [in] Countries array
 * @param length [in] Length of the countries array
 * @param country [in] country to search
 * @return int Index of the country if found,
 * @return -1 if the country was not found
 */
int findCountryIndex(MedalCount *countries, int length, const char *country);

/**
 * @brief Counts medals for the given option (countries or game editions)
 *
 * @param medals [in] Pointer for the list of medals
 * @param count [out] Number of option elements (i.e number of countries or game editions)
 * @param option [in] Option [1: Countries / 2: Game editions]
 * @param athleteID [in] Athlete ID to search, in case of option 2
 * @return MedalCount* Allocated array containing the medals
 */
MedalCount *countMedals(PtList medals, int *count, int option, const char *athleteID);

/**
 * @brief Print the countries and respective medals
 *
 * @param medals [in] Pointer for the list of medals
 * @param sortByTotal [in] Boolean to check if the countries are sorted by total medals or gold ones
 * @param ascendingOrder [in] Order of the elments (ascending or desceding)
 */
void medalsCountry(PtList medals, bool sortByTotal, bool ascendingOrder);

/**
 * @brief Searches the index of a game edition on the array
 *
 * @param games [in] Game editions array
 * @param length [in] Lenght of the array
 * @param game [in] Game edition to search
 * @return int Index of the game edition if it was found,
 * @return -1 if the game edition was not found
 */
int findGameIndex(MedalCount *games, int length, const char *game);

/**
 * @brief Print the medals won by an ahtlete for each edition
 *
 * @param medals [in] Pinter for the medals list
 * @param athleteID [in] ID of the athelte to search
 */
void medalsInfo(PtList medals, const char *athleteID);

/**
 * @brief Updates the medal count for an entry on the MedalCount array
 *
 * @param medal [in] Medal
 * @param arr [in] Array of MedalCount
 * @param index [in] Index to update the count
 */
void updateMedalCount(Medal medal, MedalCount *arr, int index);

/**
 * @brief Swap two MedalCount values
 *
 * @param a [in] Country a
 * @param b [in] Country b
 */
void medalCountSwap(MedalCount *a, MedalCount *b);

/**
 * @brief Partition function for MedalCount values
 *
 * @param values [in] Values to sort
 * @param low [in] Low index
 * @param high [in] High index
 * @param ascendingOrder [in] Ascending order [true] or descending order [false]
 * @param sortByTotal [in] Sort by total medals [true] or by gold medals [false]
 * @return int Partition index
 */
int medalCountPartition(MedalCount *values, int low, int high, bool ascendingOrder, bool sortByTotal);

/**
 * @brief Sorts MedalCount values
 *
 * @param values [in] Values to sort
 * @param low [in] Low index
 * @param high [in] High index
 * @param ascendingOrder [in] Ascending order [true] or descending order [false]
 * @param sortByTotal [in] Sort by total medals [true] or by gold medals [false]
 */
void medalCountSort(MedalCount *values, int low, int high, bool ascendingOrder, bool sortByTotal);