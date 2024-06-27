/**
 * @file topn.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Functions to analyze top countries in an interval
 * @version 1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../adts/list.h"
#include "../data_structures/host.h"
#include "../data_structures/stringWrap.h"

typedef struct CountryMedalsInfo
{
    StringWrap country;
    int medalsQuantity;
    float medalsAverageEdition;
    float medalsAverageDay;
} CountryMedalsInfo;

/**
 * @brief Get the host by its slug
 *
 * @param hosts [in] Pointer for the hosts array
 * @param hostCount [in] Lenght of the hosts array
 * @param gameSlug [in] Game slug
 * @param host [out] Host found
 * @return int 0 if the host was found,
 * @return int -1 otherwise
 */
int getHostBySlug(Host *hosts, int hostCount, char *gameSlug, Host *host);

/**
 * @brief Get the valid medals according with the search criteria
 *
 * @param medals [in] Pointer for the list of medals
 * @param hosts [in] Pointer for the Hosts array
 * @param hostCount [in] Length of the hosts
 * @param startYear [in] Start year to search medals
 * @param endYear [in] End year to search medals
 * @param gameSeason [in] Game season to search
 * @return PtList Pointer for the allocated list containing the valid medals
 */
PtList getValidMedals(PtList medals, Host *hosts, int hostCount, int startYear, int endYear, char *gameSeason);

/**
 * @brief Gets the Top N countries with the given criteria
 *
 * @param medals [in] Pointer for the list of medals
 * @param hosts [in] Pointer for the hosts array
 * @param hostCount [in] Length of the hosts array
 * @param startYear [in] Start year to search medals
 * @param endYear [in] End year to search medals
 * @param gameSeason [in] Game season to search
 * @param n [in] Number of countries to select data
 * @return int 0 If the operation was successful,
 * @return int -1 otherwise
 */
int getTopNCountries(PtList medals, Host *hosts, int hostCount, int startYear, int endYear, char *gameSeason, int n);

/**
 * @brief Get the Country Medals Info object
 *
 * @param medals [in] Pointer for the list of medals
 * @param hosts [in] Pointer for the hosts array
 * @param hostCount [in] Lenght of the hosts array
 * @param startYear [in] Start year to search medals
 * @param endYear [in] End year to search medals
 * @param gameSeason [in] Game season to search
 * @param country [in] Country to get the info
 * @return CountryMedalsInfo Array containing the info for each country
 */
CountryMedalsInfo getCountryMedalsInfo(PtList medals, Host *hosts, int hostCount, int startYear, int endYear, char *gameSeason, StringWrap country);

/**
 * @brief Swap two CountryMedalsInfo values
 *
 * @param a [in] Value a
 * @param b [in] Value b
 */
void countryMedalsInfoSwap(CountryMedalsInfo *a, CountryMedalsInfo *b);

/**
 * @brief Partition function for CountryMedalsInfo values
 *
 * @param countries [in] Array of CountryMedalsInfo values
 * @param low [in] Low index
 * @param high [in] High index
 * @return int Partition index
 */
int countryMedalsInfoPartition(CountryMedalsInfo *countries, int low, int high);

/**
 * @brief Sorts CountryMedalsInfo values
 *
 * @param countries [in] Array of CountryMedalsInfo values
 * @param low [in] Low index
 * @param high [in] High index
 */
void countryMedalsInfoSort(CountryMedalsInfo *countries, int low, int high);

/**
 * @brief Checks if a year is leap
 *
 * @param year [in] Year to check
 * @return true If the year is leap,
 * @return false otherwise
 */
bool isLeapYear(int year);

/**
 * @brief Returns the days of a month
 *
 * @param month [in] Month
 * @param year [in] year
 * @return int Days in a month
 */
int daysInMonth(int month, int year);

/**
 * @brief Get the Date Values From String object
 *
 * @param date_str [in] Date string
 * @param year [out] Year of the date
 * @param month [out] Month of the date
 * @param day [out] Day fo the date
 */
void getDateValuesFromString(char *date_str, int *year, int *month, int *day);

/**
 * @brief Returns the difference between two dates
 *
 * @param date1_str [in] Date string 1
 * @param date2_str [in] Date string 2
 * @return int Difference betwween tow dates
 */
int getDaysDifference(char *date1_str, char *date2_str);

/**
 * @brief Returns the year of a medal
 *
 * @param medal [in] Medal
 * @return int Year of the medal
 */
int getYearFromMedal(Medal medal);

/**
 * @brief Prints the Top N countries
 *
 * @param countries [in] Pointer for the countries array
 * @param n [in] Number of countries to show
 */
void printTopNCountries(CountryMedalsInfo *countries, int n);