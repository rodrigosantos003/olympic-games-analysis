/**
 * @file medal.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the medal functions
 * @version 1
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medal.h"

Medal createMedal(char *discipline, char *game, char *eventTitle, char gender, char medalType, char participantType, char *athleteID, char *country, char *countryCode)
{
    Medal medal;

    strcpy(medal.discipline, discipline);
    strcpy(medal.game, game);
    strcpy(medal.eventTitle, eventTitle);
    medal.gender = gender;
    medal.medalType = medalType;
    medal.participantType = participantType;
    strcpy(medal.athleteID, athleteID);
    strcpy(medal.country, country);
    strcpy(medal.countryCode, countryCode);

    return medal;
}
