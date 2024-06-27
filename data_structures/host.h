/**
 * @file host.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Host structure and functions
 * @version 1
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#define MAX_GAME_SLUG 50
#define MAX_GAME_END_DATE 21
#define MAX_GAME_START_DATE 21
#define MAX_GAME_LOCATION 50
#define MAX_GAME_NAME 50
#define MAX_GAME_SEASON 50
#define MAX_GAME_YEAR 5

#define HOSTS_NULL 1
#define HOSTS_OK 0

#include "../adts/list.h"
#include "stringWrap.h"

typedef struct host
{
    char gameSlug[MAX_GAME_SLUG];            // Slug of the game
    char gameEndDate[MAX_GAME_END_DATE];     // End date of the game
    char gameStartDate[MAX_GAME_START_DATE]; // Start date of the game
    char gameLocation[MAX_GAME_LOCATION];    // Location of the game
    char gameName[MAX_GAME_NAME];            // Name of the game
    char gameSeason[MAX_GAME_SEASON];        // Season of the game
    char gameYear[MAX_GAME_YEAR];            // Year of the game
} Host;

/**
 * @brief Create a Host object
 *
 * @param gameSlug [in] Slug of the game
 * @param gameEndDate [in] End date of the game
 * @param gameStartDate [in] Start date of the game
 * @param gameLocation [in] Location of the game
 * @param gameName [in] Name of the game
 * @param gameSeason [in] Season of the game
 * @param gameYear [in] Year of the game
 * @return Host Object
 */
Host createHost(char *gameSlug, char *gameEndDate, char *gameStartDate, char *gameLocation, char *gameName, char *gameSeason, char *gameYear);

/**
 * @brief Clears the contents of the hosts array.
 *
 * This operation will remove all current hosts in the array,
 * returning to an empty state.
 *
 * @param hosts [in] pointer to the hosts array
 * @param size [in] pointer to the size of the array
 *
 * @return HOSTS_OK if successful, or
 * @return HOSTS_NULL if the array is NULL
 */
int hostsClear(Host *hosts, int *size);

/**
 * @brief Finds the next four editions of given game season
 *
 * This operation will return an array containing the next four iterations of a given season starting by an initial year
 *
 * @param initialyear [in] initial year
 * @param gameSeason [*char] Game Season /Winter/ or /Summer/
 * @param hosts [in] pointer to the hosts array
 * @param size [in] pointer to the size of the array
 *
 * @return HOSTS_OK if successful, or
 * @return HOSTS_NULL if the array is NULL
 */
int *findNextFourEditions(int initialYear, char *gameSeason, Host *hosts, int hostSize);
/**
 * @brief Find the HostYear of a given index
 *
 * This operation will return integer of the year found
 *
 * @param index [in] initial year
 * @param hosts [in] pointer to the hosts array
 * @param size [in] pointer to the size of the array
 *
 * @return int Year found if successful, or
 * @return -1 if Year is not found
 */
int getHostYear(int index, Host *hosts, int hostSize);

/**
 * @brief Prints a histogram.
 *
 * This operation will print the histogram with the countries inserted by the user
 *
 * @param numCountries [in] Number of countries
 * @param countries [in] Countries
 * @param gameType [in] Game Season /Winter/ or /Summer/
 * @param startYear [in] Year to Start
 * @param hosts [in] pointer to the hosts array
 * @param size [in] pointer to the size of the array
 * @param medals [in] Medal list
 *
 */
void printHistogram(int numCountries, StringWrap *countries, char *gameType, int startYear, int hostSize, Host *hosts, PtList medals);

/**
 * @brief Gets all the game slugs of a given country, year and season
 *
 * This operation will return an StringWrap array with all the game slugs
 *
 * @param country [in] Country
 * @param gameSeason [in] Game Season /Winter/ or /Summer/
 * @param year [in] Year
 * @param hosts [in] pointer to the hosts array
 * @param size [in] pointer to the size of the array
 * @param slugsFound [out] Number of slugs found
 *
 * @return StringWrap* with all the game slugs found if successful, or
 * @return NULL if not found
 */
StringWrap *getAllGameSlugs(char *country, char *gameSeason, int year, Host *hosts, int hostSize, int *slugsFound);

/**
 * @brief Finds the country by the given country code
 *
 * This operation will return a StringWrap with the country name
 *
 * @param medals [in] pointer to the medal list
 * @param countryCode [in] Countrycode
 * @return StringWrap* with the text equal to the country name  if successful, or
 * @return StringWrap* with the text "NOT FOUND" if the country is not found
 */
StringWrap findCountryByCode(PtList medals, char *countryCode);

/**
 * @brief Finds the number of Medals
 *
 * This operation will return the number of medals (Male and female) of given country and gameSlug
 *
 * @param hostGameSlug [in] Game Slug
 * @param country [in] Country
 * @param medals [in] pointer to the medal list
 * @param maleMedals [out] Number of Male medals found
 * @param femaleMedals [out] Number of Female medals found
 *
 * @return Int with the total number of Medals  if successful, or
 * @return 0 if the no medal is not found
 */
int findNumberOfMedals(char *hostGameSlug, char *country, PtList medals, int *maleMedals, int *femaleMedals);

/**
 * @brief Prints the header of Histogram
 *
 */
void printHeader();

/**
 * @brief Prints the medals info for the current country
 *
 * @param index [in] Index of the country
 * @param currentCountry [in] Country to print info
 * @param gameType [in] Game Season /Winter/ or /Summer/
 * @param hostYear [in] Host year
 * @param hosts [in] Array of hosts
 * @param hostSize [in] Length of the hosts array
 * @param medals [in] Pointer for the list of medals
 */
void printCountryMedalsInfo(int index, StringWrap currentCountry, char *gameType, int hostYear, Host *hosts, int hostSize, PtList medals);

/**
 * @brief Prints the number of medals for a country
 *
 * @param index [in] Index of the country
 * @param country [in] Country to print the info
 * @param hostYear [in] Host year
 * @param maleMedals [in] Number of male medals
 * @param femaleMedals [in] Number of female medals
 */
void printNumberOfMedals(int index, StringWrap country, int hostYear, int maleMedals, int femaleMedals);

/**
 * @brief Prints a bar of '#'
 *
 * @param numMedals [in] number of '#' to print
 * @return char* Bar of "#"
 */
void printBar(int numMedals);

/**
 * @brief Swap two Host values
 *
 * @param a [in] Host a
 * @param b [in] Host b
 */
void hostSwap(Host *a, Host *b);

/**
 * @brief Partition function for Host values
 *
 * @param values [in] Values to sort
 * @param low [in] Low index
 * @param high [in] High index
 * @return int Partition index
 */
int hostPartition(Host *values, int low, int high);

/**
 * @brief Sorts Host values
 *
 * @param values [in] Values to sort
 * @param low [in] Low index
 * @param high [in] High index
 */
void hostSort(Host *values, int low, int high);