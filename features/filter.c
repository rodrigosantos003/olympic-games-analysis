/**
 * @file filter.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the functions to filter data
 * @version 1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"
#include "input.h"
#include "../adts/map.h"

Athlete *sortAthletesByName(Athlete *athletes, int length)
{
    printf("Sorting Athletes...\n");

    if (athletes == NULL)
    {
        printf("Error allocating memory\n");
        return NULL;
    }

    mapSort(athletes, 0, length - 1);

    return athletes;
}

Athlete *athletesofYear(Athlete *athletes, int size, int year, int *foundAthletes)
{
    printf("Searching athletes...\n");

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (athletes[i].athleteBirth == 0)
            continue;

        if (athletes[i].athleteBirth == year)
        {
            count++;
        }
    }

    *foundAthletes = count;
    Athlete *athletesOfYearArr = (Athlete *)calloc(count, sizeof(Athlete));

    for (int i = 0, j = 0; i < size; i++)
    {
        if (athletes[i].athleteBirth == 0)
            continue;

        if (athletes[i].athleteBirth == year)
        {
            athletesOfYearArr[j++] = athletes[i];
        }
    }

    free(athletes);

    return athletesOfYearArr;
}

Athlete *athletesofAge(Athlete *athletes, int size, int age, int *foundAthletes)
{
    printf("Searching athletes...\n");

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (athletes[i].athleteBirth == 0)
            continue;

        int firstGameYear = atoi(athletes[i].firstGame + strlen(athletes[i].firstGame) - 4);

        int ageAtFirstGame = firstGameYear - athletes[i].athleteBirth;

        if (ageAtFirstGame < 0)
            continue;

        if (ageAtFirstGame < age)
        {
            count++;
        }
    }

    *foundAthletes = count;
    Athlete *athletesOfAgeArr = (Athlete *)calloc(count, sizeof(Athlete));

    for (int i = 0, j = 0; i < size; i++)
    {
        if (athletes[i].athleteBirth == 0)
            continue;

        int firstGameYear = atoi(athletes[i].firstGame + strlen(athletes[i].firstGame) - 4);

        int ageAtFirstGame = firstGameYear - athletes[i].athleteBirth;

        if (ageAtFirstGame < 0)
            continue;

        if (ageAtFirstGame < age)
        {
            athletesOfAgeArr[j++] = athletes[i];
        }
    }

    free(athletes);

    return athletesOfAgeArr;
}

float athletesofGameEditions(Athlete *athletes, int size, char *gameSlug, int *foundAthletes_firstTime, int *foundAthletes_OnlyTime)
{
    printf("Searching athletes...\n");

    int countFirstTimers = 0;
    int countOnlyTimers = 0;
    int countTotalAges = 0;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(athletes[i].firstGame, gameSlug) == 0 && athletes[i].gamesParticipations == 1)
        {
            countOnlyTimers++;
        }
        if (strcmp(athletes[i].firstGame, gameSlug) == 0)
        {
            countFirstTimers++;
            int firstGameYear = atoi(athletes[i].firstGame + strlen(athletes[i].firstGame) - 4);

            int ageAtFirstGame = firstGameYear - athletes[i].athleteBirth;
            if (ageAtFirstGame < 0)
                continue;
            else
            {
                countTotalAges++;
            }
        }
    }

    *foundAthletes_firstTime = countFirstTimers;
    *foundAthletes_OnlyTime = countOnlyTimers;

    int ageSum = 0;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(athletes[i].firstGame, gameSlug) == 0)
        {
            int firstGameYear = atoi(athletes[i].firstGame + strlen(athletes[i].firstGame) - 4);

            int ageAtFirstGame = firstGameYear - athletes[i].athleteBirth;
            if (ageAtFirstGame < 0)
                continue;
            else
            {
                ageSum += ageAtFirstGame;
            }
        }
    }

    free(athletes);

    if (countFirstTimers == 0 && countOnlyTimers == 0)
        return ATHELETES_NOT_FOUND;

    return (float)(ageSum / countFirstTimers);
}

Athlete *formBatch(Athlete *athletes, int batchStart, int batchSize)
{
    Athlete *batch = (Athlete *)calloc(batchSize, sizeof(Athlete));
    if (batch == NULL)
    {
        printf("Error allocating memory\n");
        free(athletes);
        return NULL;
    }

    for (int i = batchStart, j = 0; i < batchStart + batchSize; j++, i++)
    {
        batch[j] = athletes[i];
    }

    return batch;
}

void paginate(Athlete *athletes, int size, int batchStart, int batchSize, char *command)
{
    int pageOption;

    while (true)
    {
        int currentBatchSize = (batchStart + batchSize > size) ? size - batchStart : batchSize;
        Athlete *currentBatch = formBatch(athletes, batchStart, currentBatchSize);
        printAthletesArray(currentBatch, currentBatchSize);

        printf("Lines %d to %d\n", batchStart + 1, currentBatchSize + batchStart);
        printf("%s Paginated\n", command);
        printf("1.Next 50\n");
        printf("2.Quit\n");
        readInteger(&pageOption);

        if (pageOption == 2)
        {
            free(currentBatch);
            break;
        }
        else
        {
            if (batchStart + batchSize >= size)
            {
                printf("No more data to show\n");
                free(currentBatch);
                break;
            }
            else
            {
                system("clear");
                free(currentBatch);
                batchStart += batchSize;
            }
        }
    }

    free(athletes);
}