/**
 * @file medal.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Medal structure and functions
 * @version 1
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#define MAX_DISC_LENGTH 50
#define MAX_GAME_LENGTH 50
#define MAX_EVENT_LENGTH 100
#define MAX_ID_A_LENGTH 50
#define MAX_COUNTRY_LENGTH 50

typedef struct medal
{
    char discipline[MAX_DISC_LENGTH];  // Discipline name
    char game[MAX_GAME_LENGTH];        // Name of the Olympic Games edition (ex beijing-2022)
    char eventTitle[MAX_EVENT_LENGTH]; // Event title ( ex Women's Ski cross)
    char gender;                       // M - Men, W- Women, X – Mixed, O - Open
    char medalType;                    // G - GOLD, S - SILVER, B - BRONZE
    char participantType;              // A - Athlete, G - GameTeam
    char athleteID[MAX_ID_A_LENGTH];   // Athlete ID
    char country[MAX_COUNTRY_LENGTH];  // Country by who the athlete is representing
    char countryCode[4];               // Country code
} Medal;

/**
 * @brief Create a Medal object
 *
 * @param discipline Discipline name
 * @param game Name of the Olympic Games edition
 * @param eventTitle Event title
 * @param gender Gender
 * @param medalType Medal type
 * @param participantType Participant type
 * @param athleteID Athlete ID
 * @param country Country by who the athlete is representing
 * @param countryCode Country code
 * @return Medal Medal object
 */
Medal createMedal(char *discipline, char *game, char *eventTitle, char gender, char medalType, char participantType, char *athleteID, char *country, char *countryCode);