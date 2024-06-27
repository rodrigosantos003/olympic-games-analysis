/**
 * @file host.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the host functions
 * @version 1
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../features/input.h"
#include "host.h"

Host createHost(char *gameSlug, char *gameEndDate, char *gameStartDate, char *gameLocation, char *gameName, char *gameSeason, char *gameYear)
{
    Host host;

    strcpy(host.gameSlug, gameSlug);
    strcpy(host.gameEndDate, gameEndDate);
    strcpy(host.gameStartDate, gameStartDate);
    strcpy(host.gameLocation, gameLocation);
    strcpy(host.gameName, gameName);
    strcpy(host.gameSeason, gameSeason);
    strcpy(host.gameYear, gameYear);

    return host;
}

int hostsClear(Host *hosts, int *size)
{
    if (hosts == NULL)
    {
        return HOSTS_NULL;
    }

    *size = 0;

    return HOSTS_OK;
}

void printHistogram(int numCountries, StringWrap *countries, char *gameType, int startYear, int hostSize, Host *hosts, PtList medals)
{
    int *numberOfEditions = findNextFourEditions(startYear, gameType, hosts, hostSize);
    if (numberOfEditions == NULL)
        return;

    printHeader();

    for (int i = 0; i < 4; i++)
    {
        int hostYear = getHostYear(numberOfEditions[i], hosts, hostSize);
        for (int j = 0; j < numCountries; j++)
        {
            printCountryMedalsInfo(j, countries[j], gameType, hostYear, hosts, hostSize, medals);
        }
    }

    free(numberOfEditions);
}

int *findNextFourEditions(int initialYear, char *gameSeason, Host *hosts, int hostSize)
{
    int *nextFourEditions = (int *)calloc(4, sizeof(int));
    if (nextFourEditions == NULL)
    {
        printf("Error allocating memory\n");
        return NULL;
    }

    hostSort(hosts, 0, hostSize - 1);
    int counter = 0;

    for (int i = 0; i < hostSize; i++)
    {
        if (counter == 4)
            break;
        if (atoi(hosts[i].gameYear) >= initialYear && strcmp(hosts[i].gameSeason, gameSeason) == 0)
        {
            nextFourEditions[counter] = i;
            counter += 1;
        }
    }

    return nextFourEditions;
}

int getHostYear(int index, Host *hosts, int hostSize)
{
    if (index < 0 || hosts == NULL || hostSize <= 0)
    {
        return -1;
    }
    return atoi(hosts[index].gameYear);
}

void printHeader()
{
    system("clear");
    printf("%-10s | %-10s | %-10s | %-10s\n ", "Country", "Edition", "Category", "Number of Medals");
    printf("--------------------------------------------------------------\n");
}

void printNumberOfMedals(int index, StringWrap country, int hostYear, int maleMedals, int femaleMedals)
{
    if (index == 0)
    {
        printf("%-10s | %-10d | %-10c | ", country.text, hostYear, 'M');
        printBar(maleMedals);
        printf(" %d\n", maleMedals);

        printf("%-10s | %-10s | %-10c | ", "", "", 'F');
        printBar(femaleMedals);
        printf(" %d\n", femaleMedals);
        printf("-------------------------------------------------\n");
    }
    else
    {
        printf("%-10s | %-10s | %-10c | ", country.text, "", 'M');
        printBar(maleMedals);
        printf(" %d\n", maleMedals);

        printf("%-10s | %-10s | %-10c | ", "", "", 'F');
        printBar(femaleMedals);
        printf(" %d\n", femaleMedals);
        printf("-------------------------------------------------\n");
    }
}

void printCountryMedalsInfo(int index, StringWrap currentCountry, char *gameType, int hostYear, Host *hosts, int hostSize, PtList medals)
{
    StringWrap country = findCountryByCode(medals, currentCountry.text);
    if (strcmp(country.text, "NOT FOUND") == 0)
    {
        return;
    }

    int slugsFound = 0;
    StringWrap *allSlugs = getAllGameSlugs(country.text, gameType, hostYear, hosts, hostSize, &slugsFound);

    int maleMedals = 0;
    int femaleMedals = 0;

    for (int w = 0; w < slugsFound; w++)
    {
        findNumberOfMedals(allSlugs[w].text, country.text, medals, &maleMedals, &femaleMedals);
    }

    free(allSlugs);

    printNumberOfMedals(index, currentCountry, hostYear, maleMedals, femaleMedals);
}

StringWrap *getAllGameSlugs(char *country, char *gameSeason, int year, Host *hosts, int hostSize, int *slugsFound)
{
    int totalNumberOfSlugs = 0;
    for (int i = 0; i < hostSize; i++)
    {
        if (strcmp(hosts[i].gameSeason, gameSeason) == 0 && atoi(hosts[i].gameYear) == year)
        {
            totalNumberOfSlugs++;
        }
    }

    if (totalNumberOfSlugs != 0)
    {
        StringWrap *gameSlugs = (StringWrap *)malloc(totalNumberOfSlugs * sizeof(StringWrap));
        if (gameSlugs != NULL)
        {
            for (int i = 0, j = 0; i < hostSize; i++)
            {
                if (strcmp(hosts[i].gameSeason, gameSeason) == 0 && atoi(hosts[i].gameYear) == year)
                {
                    gameSlugs[j++] = stringWrapCreate(hosts[i].gameSlug);
                }
            }
            *slugsFound = totalNumberOfSlugs;
            return gameSlugs;
        }
    }
    return NULL;
}

StringWrap findCountryByCode(PtList medals, char *countryCode)
{
    StringWrap country = stringWrapCreate("NOT FOUND");
    int size;
    listSize(medals, &size);

    for (int i = 0; i < size; i++)
    {
        ListElem elem;
        listGet(medals, i, &elem);
        if (strcmp(elem.countryCode, countryCode) == 0)
        {
            country = stringWrapCreate(elem.country);
            break;
        }
    }
    return country;
}

int findNumberOfMedals(char *hostGameSlug, char *country, PtList medals, int *maleMedals, int *femaleMedals)
{
    int size;
    listSize(medals, &size);
    int numberOfMedals = 0;

    for (int i = 0; i < size; i++)
    {
        ListElem elem;
        listGet(medals, i, &elem);
        if (strcmp(elem.game, hostGameSlug) == 0 && strcmp(elem.country, country) == 0 && elem.participantType == 'A')
        {
            if (elem.gender == 'M')
                *maleMedals += 1;
            else
                *femaleMedals += 1;

            numberOfMedals += 1;
        }
    }
    return numberOfMedals;
}

void printBar(int numMedals)
{
    for (int i = 0; i < numMedals; i++)
    {
        printf("#");
    }
}

void hostSwap(Host *a, Host *b)
{
    Host temp = *a;
    *a = *b;
    *b = temp;
}

int hostPartition(Host *values, int low, int high)
{
    Host pivot = values[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (atoi(values[j].gameYear) <= atoi(pivot.gameYear))
        {
            i++;
            hostSwap(&values[i], &values[j]);
        }
    }
    hostSwap(&values[i + 1], &values[high]);
    return i + 1;
}

void hostSort(Host *values, int low, int high)
{
    if (low < high)
    {
        int pi = hostPartition(values, low, high);
        hostSort(values, low, pi - 1);
        hostSort(values, pi + 1, high);
    }
}