/**
 * @file main.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Main file
 * @version 1
 * @date 2024-04-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "features/input.h"
#include "adts/map.h"
#include "adts/mapElem.h"
#include "features/loading.h"
#include "adts/list.h"
#include "adts/set.h"
#include "adts/setElem.h"
#include "features/filter.h"
#include "features/medals_analysis.h"
#include "features/disciplines_analysis.h"
#include "features/topn.h"

#define COMMAND_LENGTH 20
#define BATCH_START 0
#define BATCH_SIZE 50

int main()
{
    PtMap athletes = mapCreate();                   // Map of athletes
    PtList medals = listCreate();                   // Array of medals
    Host *hosts = (Host *)calloc(50, sizeof(Host)); // Array of hosts

    if (athletes == NULL || medals == NULL || hosts == NULL)
    {
        printf("Error creating data structures\n");
        return EXIT_FAILURE;
    }

    // Sizes of data structures
    int athletesSize = 0;
    int medalsSize = 0;
    int hostsSize = 0;

    bool quit = false; // Flag to control the loop

    char command[COMMAND_LENGTH] = ""; // Command typed by the user

    printf("**** Olympic Games Data Analysis ****\n");

    while (!quit)
    {
        // Read the command typed by the user
        printf("Type a command: ");
        readString(command, COMMAND_LENGTH);
        stringToUpperCase(command);

        if (strcmp(command, "LOAD_A") == 0)
        {
            LOAD_A(athletes);

            mapSize(athletes, &athletesSize);
            printf("%d ahtletes records imported\n", athletesSize);
        }
        else if (strcmp(command, "LOAD_M") == 0)
        {
            // Check if there are athletes loaded
            if (mapIsEmpty(athletes))
            {
                printf("Please load athlete data first\n");
                continue;
            }

            LOAD_M(medals);
            listSize(medals, &medalsSize);
            printf("%d medals records imported\n", medalsSize);
        }
        else if (strcmp(command, "LOAD_H") == 0)
        {
            LOAD_H(&hosts, &hostsSize);
            printf("%d hosts records imported\n", hostsSize);
        }
        else if (strcmp(command, "SHOW_ALL") == 0)
        {
            // Check if there are athletes loaded
            if (mapIsEmpty(athletes))
            {
                printf("No athlete data available\n");
                continue;
            }

            // Show all athletes sorted by name
            Athlete *sortedAthletes = sortAthletesByName(mapValues(athletes), athletesSize);

            printf("%d ATHLETES FOUND\n", athletesSize);

            paginate(sortedAthletes, athletesSize, BATCH_START, BATCH_SIZE, command);
        }
        else if (strcmp(command, "SHOW_YEAR") == 0)
        {
            // Check if there are athletes loaded
            if (mapIsEmpty(athletes))
            {
                printf("No athlete data available\n");
                continue;
            }

            // Get the birth year from user input
            int year = 0;
            printf("Enter the birth year to search: ");
            readInteger(&year);

            // Show the athletes with the given birth year, sorted by name
            int foundAthletes = 0;
            Athlete *ahtletesOfYearArr = athletesofYear(mapValues(athletes), athletesSize, year, &foundAthletes);
            if (ahtletesOfYearArr == NULL)
            {
                printf("Athlete data not available for this birth year <%d>", year);
                continue;
            }

            Athlete *sortedAthletes = sortAthletesByName(ahtletesOfYearArr, foundAthletes);

            printf("%d ATHLETES FOUND\n", foundAthletes);

            paginate(sortedAthletes, foundAthletes, BATCH_START, BATCH_SIZE, command);
        }
        else if (strcmp(command, "SHOW_AGE") == 0)
        {
            // Check if there are athletes loaded
            if (mapIsEmpty(athletes))
            {
                printf("No athlete data available\n");
                continue;
            }

            // Get the age from user input
            int age = 0;
            printf("Enter the age to search: ");
            readInteger(&age);

            // Show the athletes that were younger than the given age on their first participation, sorted by name
            int foundAthletes = 0;
            Athlete *athletesOfAgeArr = athletesofAge(mapValues(athletes), athletesSize, age, &foundAthletes);
            if (athletesOfAgeArr == NULL)
            {
                printf("No athletes found with less than years on their first participation <%d>", age);
                continue;
            }
            Athlete *sortedAthletes = sortAthletesByName(athletesOfAgeArr, foundAthletes);

            printf("%d ATHLETES FOUND\n", foundAthletes);

            paginate(sortedAthletes, foundAthletes, BATCH_START, BATCH_SIZE, command);
        }
        else if (strcmp(command, "ATHLETES_STATS") == 0)
        {
            // Check if there are athletes loaded
            if (mapIsEmpty(athletes))
            {
                printf("Please load athelets data\n");
                continue;
            }

            // Check if there are hosts loaded
            if (hostsSize == 0)
            {
                printf("Please load hosts data\n");
                continue;
            }

            // Get the game slug from user input
            char gameSlug[MAX_GAME_SLUG] = "";
            printf("\nPlease insert in the format <GAME COUNTRY> <GAME YEAR>");
            printf("\nGame Edition: ");
            readString(gameSlug, MAX_GAME_SLUG);

            // Show the number athletes that played in a given Game edition
            printf("\n%s\n", gameSlug);
            int firstTimers = 0;
            int onlyTimers = 0;

            float mean = athletesofGameEditions(mapValues(athletes), athletesSize, gameSlug, &firstTimers, &onlyTimers);
            if (mean == -1)
            {
                printf("\nEdition Game data not available\n");
                continue;
            }

            printAthleteStats(firstTimers, onlyTimers, mean);
        }
        else if (strcmp(command, "LIST_D") == 0)
        {
            // Check if there are medals loaded
            if (listIsEmpty(medals))
            {
                printf("No medals data available\n");
                continue;
            }

            countDisciplineAppearences(medals);
        }
        else if (strcmp(command, "MEDALS_COUNTRY") == 0)
        {
            // Check if there are medals loaded
            if (listIsEmpty(medals))
            {
                printf("No medals data available\n");
                continue;
            }

            // Get the order and sorting for the medals from user input
            int order, sorting;
            printf("Order by total number of medals or by gold medals? [1: Total / 2: Gold]\n");
            readInteger(&order);
            printf("Ascending or Descending sorting? [1: Ascending / 2: Descending]\n");
            readInteger(&sorting);

            medalsCountry(medals, order == 1 ? true : false, sorting == 1 ? true : false);
        }
        else if (strcmp(command, "MEDALS_INFO") == 0)
        {
            // Check if there are medals loaded
            if (listIsEmpty(medals))
            {
                printf("No medals data available\n");
                continue;
            }

            // Get athlete ID from user input
            char athleteID[MAX_ID_A_LENGTH];
            printf("Enter the athlete ID to search medals: ");
            readString(athleteID, MAX_ID_A_LENGTH);

            medalsInfo(medals, athleteID);
        }
        else if (strcmp(command, "TOPN") == 0)
        {
            // Check if there are medals loaded
            if (listIsEmpty(medals))
            {
                printf("Please load medals data first\n");
                continue;
            }

            // Check if there are hosts loaded
            if (hostsSize == 0)
            {
                printf("Please load hosts data first\n");
                continue;
            }

            // Get the number of countries from user input
            int n = 0;
            printf("Enter the number of countries to show: ");
            readInteger(&n);

            int startYear = 0;
            int endYear = 0;

            // Get start year from user input
            printf("Enter the start year: ");
            readInteger(&startYear);

            // Get end year from user input
            printf("Enter the end year: ");
            readInteger(&endYear);

            char gameType[MAX_GAME_SEASON] = "";

            bool confirmation_GameType = false;

            // Get parameters from user input
            while (confirmation_GameType != true)
            {
                printf("Game Type (\"Winter\" Or \"Summer\"): ");
                readString(gameType, MAX_GAME_SEASON);
                stringToUpperCase(gameType);
                if (strcmp(gameType, "WINTER") == 0)
                {
                    confirmation_GameType = true;
                    strcpy(gameType, "Winter");
                }
                else if (strcmp(gameType, "SUMMER") == 0)
                {
                    confirmation_GameType = true;
                    strcpy(gameType, "Summer");
                }
                else
                {
                    printf("\nSelect one of the default Game types (\"Winter\" Or \"Summer\") \n");
                }
            }

            // Show Top N countries with more medals within the year interval
            int error = getTopNCountries(medals, hosts, hostsSize, startYear, endYear, gameType, n);

            if (error != 0)
            {
                printf("No data found for the requested period.\n");
            }
        }
        else if (strcmp(command, "HISTOGRAM") == 0)
        {
            // Check if there are medals loaded
            if (listIsEmpty(medals))
            {
                printf("No medals data available\n");
                continue;
            }

            // Check if there are hosts loaded
            if (hostsSize == 0)
            {
                printf("No hosts data available\n");
                continue;
            }

            printf("Insert Country Codes (max 4):\n");
            printf("(Type 'END' to Stop)\n");

            // Get parameters from user input
            int numCountries = 0;
            StringWrap countries[4];

            char gameType[MAX_GAME_SEASON] = "";

            int startYear = 0;

            bool protectionFlag = false;

            while (numCountries < 4)
            {
                char input[5] = "";
                printf("Country %d: ", numCountries + 1);
                readString(input, 5);
                stringToUpperCase(input);

                if (strcmp(input, "END") == 0)
                    break;
                else
                {
                    StringWrap found = findCountryByCode(medals, input);

                    if (strcmp(found.text, "NOT FOUND") == 0)
                    {
                        printf("\nError - Country not found\n");
                        protectionFlag = true;
                        break;
                    }
                    countries[numCountries] = stringWrapCreate(input);
                    numCountries++;
                }
            }
            if (protectionFlag)
                continue;
            if (numCountries < 1)
            {
                printf("Error:at least 1 country must be inserted.\n");
                continue;
            }

            printf("Game Type (\"Winter\" Or \"Summer\"): ");
            readString(gameType, MAX_GAME_SEASON);
            stringToUpperCase(gameType);
            if (strcmp(gameType, "WINTER") == 0)
            {
                strcpy(gameType, "Winter");
            }
            else if (strcmp(gameType, "SUMMER") == 0)
            {
                strcpy(gameType, "Summer");
            }
            else
            {
                printf("\nSelect one of the default Game types (\"Winter\" Or \"Summer\") \n");
                continue;
            }

            printf("Insert the year of the first four editions to consider: ");
            readInteger(&startYear);

            if (startYear < 0)
            {
                printf("\nPlease Select a valid initial year ! \n");
            }

            // Show the histogram
            printHistogram(numCountries, countries, gameType, startYear, hostsSize, hosts, medals);
        }
        else if (strcmp(command, "CLEAR") == 0)
        {
            // Clear athletes
            int athletesDeleted = athletesSize;
            int errorAthletes = mapClear(athletes);
            if (errorAthletes != MAP_OK)
            {
                printf("Error clearing athletes\n");
            }
            else
            {
                athletesSize = 0;
            }

            // Clear medals
            int medalsDeleted = medalsSize;
            int errorMedals = listClear(medals);
            if (errorMedals != LIST_OK)
            {
                printf("Error clearing medals\n");
            }
            else
            {
                medalsSize = 0;
            }

            // Clear hosts
            int hostsDeleted = hostsSize;
            int errorHosts = hostsClear(hosts, &hostsSize);
            if (errorHosts != HOSTS_OK)
            {
                printf("Error clearing hosts\n");
            }

            printf("Records deleted from Athletes (< %d >) | Medals (< %d >) | Hosts (< %d >)\n", athletesDeleted, medalsDeleted, hostsDeleted);
        }
        else if (strcmp(command, "QUIT") == 0)
        {
            // Exit program
            quit = true;
        }
        else if (strcmp(command, "HELP") == 0)
        {
            printf("Possible commands: \n");
            printf("- LOAD_A (Load athletes data)\n");
            printf("- LOAD_M (Load medals data)\n");
            printf("- LOAD_H (Load hosts data)\n");
            printf("- SHOW_ALL (Show all athletes)\n");
            printf("- SHOW_YEAR (Show athletes with a given birth year)\n");
            printf("- SHOW_AGE (Show athletes who, at their first participation in the Olympic Games, were less than than a given age\n");
            printf("- ATHLETES_STATS (Show stats for an Olympic Games edition\n");
            printf("- LIST_D (Show all disciplines)\n");
            printf("- MEDALS_COUNTRY (Show the countries that have medals=\n");
            printf("- MEDALS_INFO (Show the medals for an athlete)\n");
            printf("- TOPN (Show the top N countries that had medals)\n");
            printf("- HISTOGRAM (Show an histogram of medals)\n");
            printf("- CLEAR (Discard the info currently loaded)\n");
            printf("- QUIT (Quit the program)\n");
        }
        else
        {
            printf("Unknown command\n");
        }
    }

    // Free allocated memory
    mapDestroy(&athletes);
    listDestroy(&medals);
    free(hosts);

    return EXIT_SUCCESS;
}