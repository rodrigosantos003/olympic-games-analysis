/**
 * @file medals_analysis.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the functions to analyze medals data
 * @version 1
 * @date 2024-05-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "medals_analysis.h"

MedalCount *countMedals(PtList medals, int *count, int option, const char *athleteID)
{
    int size;
    listSize(medals, &size);

    int capacity = 10;
    MedalCount *medalCountArr = (MedalCount *)calloc(capacity, sizeof(MedalCount));
    if (medalCountArr == NULL)
    {
        printf("Error allocating memory\n");
        return NULL;
    }

    *count = 0;

    for (int i = 0; i < size; i++)
    {
        Medal elem;
        listGet(medals, i, &elem);

        int index = 0;
        if (option == 1)
        {
            index = findCountryIndex(medalCountArr, *count, elem.country);
        }
        else
        {
            if (strcmp(elem.athleteID, athleteID) != 0)
                continue;

            index = findGameIndex(medalCountArr, *count, elem.game);
        }

        if (index == -1)
        {
            if (*count >= capacity)
            {
                capacity *= 2;
                MedalCount *temp = realloc(medalCountArr, capacity * sizeof(MedalCount));
                if (temp == NULL)
                {
                    free(medalCountArr);
                    *count = 0;
                    return NULL;
                }
                medalCountArr = temp;
            }

            strcpy(medalCountArr[*count].game, elem.game);
            strcpy(medalCountArr[*count].country, elem.country);
            medalCountArr[*count].gold = 0;
            medalCountArr[*count].silver = 0;
            medalCountArr[*count].bronze = 0;
            index = (*count)++;
        }

        updateMedalCount(elem, medalCountArr, index);
    }

    return medalCountArr;
}

void updateMedalCount(Medal medal, MedalCount *arr, int index)
{
    switch (medal.medalType)
    {
    case 'G':
        arr[index].gold++;
        break;
    case 'S':
        arr[index].silver++;
        break;
    case 'B':
        arr[index].bronze++;
        break;
    }
}

int findCountryIndex(MedalCount *countries, int length, const char *country)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(countries[i].country, country) == 0)
        {
            return i;
        }
    }

    return -1;
}

int findGameIndex(MedalCount *games, int length, const char *game)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(games[i].game, game) == 0)
        {
            return i;
        }
    }

    return -1;
}

void medalsCountry(PtList medals, bool sortByTotal, bool ascendingOrder)
{
    int countryCount = 0;
    MedalCount *countries = countMedals(medals, &countryCount, 1, NULL);

    medalCountSort(countries, 0, countryCount - 1, ascendingOrder, sortByTotal);

    printf("%50s%50s\n", "Country", "Medals");
    printf("============================================================================================================================================================\n");
    for (int i = 0; i < countryCount; i++)
    {
        int total = countries[i].gold + countries[i].silver + countries[i].bronze;
        printf("%50s%50d (%d Gold / %d Silver / %d Bronze)\n", countries[i].country, total, countries[i].gold, countries[i].silver, countries[i].bronze);
    }

    free(countries);
}

void medalsInfo(PtList medals, const char *athleteID)
{
    int gamesCount = 0;
    MedalCount *games = countMedals(medals, &gamesCount, 2, athleteID);

    if (gamesCount == 0)
    {
        printf("Athlete did not win any medals\n");
        return;
    }

    printf("Athlete: %s | Country: %s\n", athleteID, games[0].country);

    printf("%50s%50s\n", "Game", "Medals");
    printf("============================================================================================================================================================\n");
    for (int i = 0; i < gamesCount; i++)
    {
        int total = games[i].gold + games[i].silver + games[i].bronze;
        printf("%50s%50d (%d Gold / %d Silver / %d Bronze)\n", games[i].game, total, games[i].gold, games[i].silver, games[i].bronze);
    }

    free(games);
}

void medalCountSwap(MedalCount *a, MedalCount *b)
{
    MedalCount temp = *a;
    *a = *b;
    *b = temp;
}

int medalCountPartition(MedalCount *values, int low, int high, bool ascendingOrder, bool sortByTotal)
{
    MedalCount pivot = values[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        bool shouldSwap = false;
        if (sortByTotal)
        {
            int aTotal = values[j].gold + values[j].silver + values[j].bronze;
            int bTotal = pivot.gold + pivot.silver + pivot.bronze;

            shouldSwap = ascendingOrder ? aTotal < bTotal : aTotal > bTotal;
        }
        else
        {
            shouldSwap = ascendingOrder ? values[j].gold < pivot.gold : values[j].gold > pivot.gold;
        }

        if (shouldSwap)
        {
            i++;
            medalCountSwap(&values[i], &values[j]);
        }
    }
    medalCountSwap(&values[i + 1], &values[high]);
    return i + 1;
}

void medalCountSort(MedalCount *values, int low, int high, bool ascendingOrder, bool sortByTotal)
{
    if (low < high)
    {
        int pi = medalCountPartition(values, low, high, ascendingOrder, sortByTotal);
        medalCountSort(values, low, pi - 1, ascendingOrder, sortByTotal);
        medalCountSort(values, pi + 1, high, ascendingOrder, sortByTotal);
    }
}