/**
 * @file athlete.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Athlete structure and functions
 * @version 1
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#define MAX_ID_LENGTH 50
#define MAX_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50

typedef struct athlete
{
    char athleteID[MAX_ID_LENGTH];     // Athtlete unique ID
    char athleteName[MAX_NAME_LENGTH]; // Athlete name
    int gamesParticipations;           // Number of games in which the athlete participated
    char firstGame[MAX_GAME_LENGTH];   // First game in which the athlete participated
    int athleteBirth;                  // Year of birth of the athlete
} Athlete;

/**
 * @brief Create a Athlete object
 *
 * @param name [in] Athlete name
 * @param id [in] Athlete ID
 * @param gamesParticipations [in] Number of games in which the athlete participated
 * @param firstGame [in] First game in which the athlete participated
 * @param athleteBirth [in] Year of birth of the athlete
 * @return Athlete Object
 */
Athlete createAthlete(char *id, char *name, int gamesParticipations, char *firstGame, int athleteBirth);
/**
 * @brief Prints a Athlete object
 *
 * @param arr [in] Athlete array
 * @param length [in] Athlete array length
 */
void printAthletesArray(Athlete *arr, int length);
/**
 * @brief Prints a Athletes Stats
 *
 * @param firstTimers [in] Number of Athletes that played in the Game Edition for the firt time
 * @param onlyTimers [in]  Number of Athletes that played in the Game Edition for the firt time and it was the only time they played
 * @param mean [in]  Age Mean of the players found
 */
void printAthleteStats(int firstTimers, int onlyTimers, float mean);