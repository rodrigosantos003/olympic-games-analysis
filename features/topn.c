/**
 * @file topn.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the functions to analyze top countries in an interval
 * @version 1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdbool.h>
#include "../adts/list.h"
#include "../data_structures/host.h"
#include "../data_structures/stringWrap.h"
#include "topn.h"
#include <string.h>
#include "../adts/set.h"

int getHostBySlug(Host *hosts, int hostCount, char *gameSlug, Host *host)
{
    for (int i = 0; i < hostCount; i++)
    {
        if (strcmp(hosts[i].gameSlug, gameSlug) == 0)
        {
            *host = hosts[i];
            return 0;
        }
    }

    return -1;
}

bool isHostInCorrectType(Host *hosts, int hostCount, char *gameSlug, char *gameSeason)
{
    Host host;
    int hostFound = getHostBySlug(hosts, hostCount, gameSlug, &host);

    if (hostFound == -1)
        return false;

    if (strcmp(host.gameSeason, gameSeason) == 0)
        return true;

    return false;
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year)
{
    if (month == 2)
    {
        if (isLeapYear(year))
        {
            return 29;
        }
        return 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    return 31;
}

void getDateValuesFromString(char *date_str, int *year, int *month, int *day)
{
    sscanf(date_str, "%d-%d-%dT%*d:%*d:%*dZ", year, month, day);
}

int getDaysDifference(char *date1_str, char *date2_str)
{
    int year1, month1, day1;
    int year2, month2, day2;

    getDateValuesFromString(date1_str, &year1, &month1, &day1);
    getDateValuesFromString(date2_str, &year2, &month2, &day2);

    int daysDiff = 0;
    while (year1 != year2 || month1 != month2 || day1 != day2)
    {
        daysDiff++;
        day1++;
        if (day1 > daysInMonth(month1, year1))
        {
            day1 = 1;
            month1++;
            if (month1 > 12)
            {
                month1 = 1;
                year1++;
            }
        }
    }

    return daysDiff;
}

int getYearFromMedal(Medal medal)
{
    int year;
    int strSize = strlen(medal.game);
    sscanf(medal.game + strSize - 4, "%d", &year);
    return year;
}

PtList getValidMedals(PtList medals, Host *hosts, int hostCount, int startYear, int endYear, char *gameSeason)
{
    PtList result = listCreate();

    int medalsCount;
    listSize(medals, &medalsCount);

    int medalsAdded = 0;

    for (int i = 0; i < medalsCount; i++)
    {
        Medal medal;
        listGet(medals, i, &medal);

        int medalYear = getYearFromMedal(medal);

        if (medalYear < startYear || medalYear > endYear)
            continue;

        if (!isHostInCorrectType(hosts, hostCount, medal.game, gameSeason))
            continue;

        listAdd(result, medalsAdded, medal);
        medalsAdded++;
    }

    return result;
}

int getTopNCountries(PtList medals, Host *hosts, int hostCount, int startYear, int endYear, char *gameSeason, int n)
{
    PtList validMedals = getValidMedals(medals, hosts, hostCount, startYear, endYear, gameSeason);

    int medalsCount;
    listSize(validMedals, &medalsCount);

    if (medalsCount == 0)
    {
        listDestroy(&validMedals);
        return -1;
    }

    // Set containing the countries that have valid medals
    PtSet countries = setCreate();

    // Add countries to the set
    for (int i = 0; i < medalsCount; i++)
    {
        Medal medal;
        listGet(validMedals, i, &medal);

        setAdd(countries, stringWrapCreate(medal.country));
    }

    int countriesCount;
    setSize(countries, &countriesCount);

    // Array containing the countries
    StringWrap *countriesArray = setValues(countries);

    // Countries data
    CountryMedalsInfo *result = (CountryMedalsInfo *)malloc(countriesCount * sizeof(CountryMedalsInfo));

    for (int i = 0; i < countriesCount; i++)
    {
        result[i] = getCountryMedalsInfo(validMedals, hosts, hostCount, startYear, endYear, gameSeason, countriesArray[i]);
    }

    countryMedalsInfoSort(result, 0, countriesCount - 1);

    printTopNCountries(result, n);

    free(countriesArray);
    free(result);
    listDestroy(&validMedals);
    setDestroy(&countries);

    return 0;
}

CountryMedalsInfo getCountryMedalsInfo(PtList validMedals, Host *hosts, int hostCount, int startYear, int endYear, char *gameSeason, StringWrap country)
{
    CountryMedalsInfo info;
    info.country = country;
    info.medalsQuantity = 0;
    info.medalsAverageEdition = 0;
    info.medalsAverageDay = 0;

    int medalsCount;
    listSize(validMedals, &medalsCount);

    int countryMedalsCount = 0;

    int daysSum = 0;

    PtSet medalSlugs = setCreate();
    for (int i = 0; i < medalsCount; i++)
    {
        Medal medal;
        listGet(validMedals, i, &medal);

        if (strcmp(medal.country, country.text) == 0)
        {
            countryMedalsCount++;
            int setAdded = setAdd(medalSlugs, stringWrapCreate(medal.game));

            if (setAdded == SET_OK)
            {
                Host host;
                getHostBySlug(hosts, hostCount, medal.game, &host);

                daysSum += getDaysDifference(host.gameStartDate, host.gameEndDate);
            }
        }
    }

    int medalSlugsCount;
    setSize(medalSlugs, &medalSlugsCount);

    info.medalsQuantity = countryMedalsCount;
    info.medalsAverageEdition = (float)countryMedalsCount / medalSlugsCount;
    info.medalsAverageDay = (float)countryMedalsCount / daysSum;

    setDestroy(&medalSlugs);

    return info;
}

void countryMedalsInfoSwap(CountryMedalsInfo *a, CountryMedalsInfo *b)
{
    CountryMedalsInfo temp = *a;
    *a = *b;
    *b = temp;
}

int countryMedalsInfoPartition(CountryMedalsInfo *countries, int low, int high)
{
    CountryMedalsInfo pivot = countries[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (countries[j].medalsQuantity > pivot.medalsQuantity)
        {
            i++;
            countryMedalsInfoSwap(&countries[i], &countries[j]);
        }
    }

    CountryMedalsInfo temp = countries[i + 1];
    countries[i + 1] = countries[high];
    countries[high] = temp;

    return i + 1;
}

void countryMedalsInfoSort(CountryMedalsInfo *countries, int low, int high)
{
    if (low < high)
    {
        int pi = countryMedalsInfoPartition(countries, low, high);
        countryMedalsInfoSort(countries, low, pi - 1);
        countryMedalsInfoSort(countries, pi + 1, high);
    }
}

void printTopNCountries(CountryMedalsInfo *countries, int n)
{
    printf("\n\nCountry                        | Total medals | Average medals by game edition | Average medals by game day\n");
    printf("-------------------------------|--------------|--------------------------------|-------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-30s | %-12d | %-30.2f | %-30.2f\n", countries[i].country.text, countries[i].medalsQuantity, countries[i].medalsAverageEdition, countries[i].medalsAverageDay);
    }
    printf("\n\n");
}