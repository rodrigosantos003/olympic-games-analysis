/**
 * @file disciplines_analysis.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the functions to analyze medals data
 * @version 1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "disciplines_analysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../adts/set.h"
#include "../adts/list.h"

DisciplineAppearenceCount createDisciplineAppearenceCount(StringWrap discipline, PtList medals, int medalsCount)
{
    DisciplineAppearenceCount disciplineAppearenceCount;

    disciplineAppearenceCount.discipline = discipline;
    disciplineAppearenceCount.count = 0;
    disciplineAppearenceCount.slugs = setCreate();

    if (disciplineAppearenceCount.slugs == NULL)
    {
        printf("There was a problem allocating memory\n");
    }

    for (int j = 0; j < medalsCount; j++)
    {
        Medal auxMedal;

        listGet(medals, j, &auxMedal);

        if (strcmp(discipline.text, auxMedal.discipline) != 0)
        {
            continue;
        }

        setAdd(disciplineAppearenceCount.slugs, stringWrapCreate(auxMedal.game));
    }
    setSize(disciplineAppearenceCount.slugs, &disciplineAppearenceCount.count);

    return disciplineAppearenceCount;
}

PtSet getDisciplines(PtList medals)
{
    PtSet disciplineSet = setCreate();

    if (disciplineSet == NULL)
    {
        printf("Error allocating memory\n");
        return NULL;
    }

    int medalsCount;
    listSize(medals, &medalsCount);

    for (int i = 0; i < medalsCount; i++)
    {
        Medal auxMedal;

        listGet(medals, i, &auxMedal);

        StringWrap discipline = stringWrapCreate(auxMedal.discipline);

        setAdd(disciplineSet, discipline);
    }

    return disciplineSet;
}

void countDisciplineAppearences(PtList medals)
{
    PtSet disciplineSet = getDisciplines(medals);

    int disciplineCount;
    setSize(disciplineSet, &disciplineCount);

    int medalsCount;
    listSize(medals, &medalsCount);

    StringWrap *disciplines = setValues(disciplineSet);

    DisciplineAppearenceCount *disciplineAppearenceCount = (DisciplineAppearenceCount *)calloc(disciplineCount, sizeof(DisciplineAppearenceCount));

    if (disciplineAppearenceCount == NULL)
    {
        setDestroy(&disciplineSet);
        printf("Error allocating memory\n");
        return;
    }

    for (int i = 0; i < disciplineCount; i++)
    {
        disciplineAppearenceCount[i] = createDisciplineAppearenceCount(disciplines[i], medals, medalsCount);
    }

    disciplineSort(disciplineAppearenceCount, 0, disciplineCount - 1);

    printf("Disciplines found: %d\n\n", disciplineCount);
    printf("Discipline                    Appearances\n");
    printf("===============================================\n");
    for (int i = 0; i < disciplineCount; i++)
    {
        printf("%-30s %d\n", disciplineAppearenceCount[i].discipline.text, disciplineAppearenceCount[i].count);
    }

    printf("\n");

    for (int i = 0; i < disciplineCount; i++)
    {
        setDestroy(&disciplineAppearenceCount[i].slugs);
    }

    setDestroy(&disciplineSet);
    free(disciplines);
    free(disciplineAppearenceCount);
}

void disciplineSwap(DisciplineAppearenceCount *a, DisciplineAppearenceCount *b)
{
    DisciplineAppearenceCount temp = *a;
    *a = *b;
    *b = temp;
}

int disciplinePartition(DisciplineAppearenceCount *values, int low, int high)
{
    DisciplineAppearenceCount pivot = values[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (strcmp(values[j].discipline.text, pivot.discipline.text) <= 0)
        {
            i++;
            disciplineSwap(&values[i], &values[j]);
        }
    }
    disciplineSwap(&values[i + 1], &values[high]);
    return i + 1;
}

void disciplineSort(DisciplineAppearenceCount *values, int low, int high)
{
    if (low < high)
    {
        int pi = disciplinePartition(values, low, high);
        disciplineSort(values, low, pi - 1);
        disciplineSort(values, pi + 1, high);
    }
}