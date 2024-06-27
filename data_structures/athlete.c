/**
 * @file athlete.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of athlete functions
 * @version 1
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "athlete.h"

Athlete createAthlete(char *id, char *name, int gamesParticipations, char *firstGame, int athleteBirth)
{
    Athlete athlete;

    strcpy(athlete.athleteID, id);
    strcpy(athlete.athleteName, name);
    athlete.gamesParticipations = gamesParticipations;
    strcpy(athlete.firstGame, firstGame);
    athlete.athleteBirth = athleteBirth;

    return athlete;
}

void printAthletesArray(Athlete *arr, int length)
{
    printf("%50s%50s%30s%20s%10s\n", "ATHLETE ID", "FULL NAME", "PARTICIPATIONS", "FIRST GAME", "BIRTH YEAR");
    printf("============================================================================================================================================================\n");

    for (int i = 0; i < length; i++)
    {
        printf("%50s%50s%30d%20s%10d\n", arr[i].athleteID, arr[i].athleteName, arr[i].gamesParticipations, arr[i].firstGame, arr[i].athleteBirth);
    }
}

void printAthleteStats(int firstTimers, int onlyTimers, float mean)
{
    printf("----------------------------------------------------------------------------------\n");
    printf("%-30s| %-35s| %-35s\n", "Number of Athletes First Time", "Number of Athletes Only one Time", " Age mean");
    printf("----------------------------------------------------------------------------------\n");
    printf("%-30d| %-35d| %-35.2f\n", firstTimers, onlyTimers, mean);
    printf("----------------------------------------------------------------------------------\n");
}