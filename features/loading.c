/**
 * @file loading.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the functions to load data from files
 * @version 1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../features/input.h"
#include "../features/loading.h"

void LOAD_A(PtMap athletes)
{
    printf("Loading athletes data...\n");

    FILE *stream = fopen("athletes.csv", "r");

    if (stream == NULL)
    {
        printf("File not found\n");
        return;
    }

    char line[1024];

    // Ignore the header line
    fgets(line, 1024, stream);

    while (fgets(line, 1024, stream))
    {
        char *tmp = strdup(line);

        char **tokens = splitString(tmp, 5, ";");

        int athleteBirth = tokens[4] == NULL ? 0 : atoi(tokens[4]);
        int gamesParticipations = atoi(tokens[2]);

        mapPut(athletes, stringWrapCreate(tokens[0]), createAthlete(tokens[0], tokens[1], gamesParticipations, tokens[3], athleteBirth));

        free(tokens);
        free(tmp);
    }

    fclose(stream);
}

void LOAD_M(PtList medals)
{
    printf("Loading medals data...\n");

    FILE *stream = fopen("medals.csv", "r");

    if (stream == NULL)
    {
        printf("File not found\n");
        return;
    }

    int count = 0;
    char line[1024];

    // Ignore the header line
    fgets(line, 1024, stream);

    while (fgets(line, 1024, stream))
    {
        char *tmp = strdup(line);

        char **tokens = splitString(tmp, 10, ";");

        if (tokens[7] == NULL && tokens[5][0] == 'A')
            tokens[7] = "UNKNOWN";

        listAdd(medals,
                count,
                createMedal(tokens[0], tokens[1], tokens[2], tokens[3][0], tokens[4][0], tokens[5][0], tokens[7], tokens[8], tokens[9]));

        count++;

        free(tokens);
        free(tmp);
    }

    fclose(stream);
}

void LOAD_H(Host **hosts, int *size)
{
    printf("Loading hosts data...\n");

    int arraySize = 50;

    FILE *stream = fopen("hosts.csv", "r");

    if (stream == NULL)
    {
        printf("File not found\n");
        return;
    }

    int count = 0;
    char line[1024];

    // Ignore the header line
    fgets(line, 1024, stream);

    while (fgets(line, 1024, stream))
    {
        if (count == arraySize)
        {
            arraySize *= 2;
            *hosts = realloc(*hosts, arraySize * sizeof(Host));
            if (*hosts == NULL)
            {
                // Handle error
                fprintf(stderr, "Failed to reallocate memory for hosts\n");
                exit(1);
            }
        }

        char *tmp = strdup(line);

        char **tokens = splitString(tmp, 7, ";");

        (*hosts)[count++] = createHost(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]);

        free(tokens);
        free(tmp);
    }

    fclose(stream);

    *size = count;
}
