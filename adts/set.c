/**
 * @file set.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Implementation of the Set ADT
 * @version 1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct setImpl
{
    SetElem *elements;
    int size;
    int capacity;
} SetImpl;

static bool ensureCapacity(PtSet set)
{
    if (set->size == set->capacity)
    {
        int newCapacity = set->capacity * 2;
        SetElem *newArray = (SetElem *)realloc(set->elements,
                                                 newCapacity * sizeof(SetElem));
        if (newArray == NULL)
            return false;
        set->elements = newArray;
        set->capacity = newCapacity;
    }
    return true;
}

PtSet setCreate()
{
    PtSet set = (PtSet)malloc(sizeof(SetImpl));

    if (set == NULL)
        return NULL;

    set->elements = (SetElem *)calloc(SET_INITIAL_CAPACITY, sizeof(SetElem));

    if (set->elements == NULL)
    {
        free(set);
        return NULL;
    }

    set->size = 0;
    set->capacity = SET_INITIAL_CAPACITY;
    return set;
}

int setAdd(PtSet set, SetElem elem)
{
    if (set == NULL)
        return SET_NULL;

    if (!ensureCapacity(set))
        return SET_NO_MEMORY;

    if(setContains(set, elem)){
        return SET_ALREADY_IN_SET;
    }

    set->elements[set->size] = elem;

    set->size++;
    return SET_OK;
}

int setRemove(PtSet set, SetElem elem)
{
    if (set == NULL)
        return SET_NULL;
    if (set->size == 0)
        return SET_EMPTY;

    if (!setContains(set, elem))
        return SET_OK;

    for(int i = 0; i < set->size; i++)
    {
        if(strcmp(set->elements[i].text, elem.text) == 0)
        {
            for(int j = i; j < set->size - 1; j++)
            {
                set->elements[j] = set->elements[j+1];
            }
        }
    }

    set->size--;

    return SET_OK;
}

bool setContains(PtSet set, SetElem elem){
    if (set == NULL)
        return false;
    for(int i = 0; i < set->size; i++)
    {
        if(strcmp(set->elements[i].text, elem.text) == 0)
            return true;
    }
    return false;
}

int setSize(PtSet set, int *ptSize)
{
    if (set == NULL)
        return SET_NULL;
    *ptSize = set->size;
    return SET_OK;
}

bool setHasSubset(PtSet set, PtSet subSet)
{
    if (set == NULL || subSet == NULL)
        return false;

    for(int i = 0; i < subSet->size; i++)
    {
        if(!setContains(set, subSet->elements[i]))
        {
            return false;
        }
    }
    return true;
}

bool setIsEmpty(PtSet set)
{
    if (set == NULL)
        return true;
    return (set->size == 0);
}

int setClear(PtSet set)
{
    if (set == NULL)
        return SET_NULL;
    set->size = 0;
    return SET_OK;
}

SetElem *setValues(PtSet set){
    if (set == NULL || set->size == 0)
        return NULL;

    SetElem *values = (SetElem *)calloc(set->size, sizeof(SetElem));
    if (values == NULL)
        return NULL;

    for (int i = 0; i < set->size; i++)
    {
        values[i] = set->elements[i];
    }

    return values;
}

void setPrint(PtSet set)
{
    if (set == NULL)
    {
        printf("(Set NULL)\n");
    }
    else if (set->size == 0)
    {
        printf("(Set EMPTY)\n");
    }
    else
    {
        for (int rank = 0; rank < set->size; rank++)
        {
            setElemPrint(set->elements[rank]);
            printf("\n");
        }
    }
    printf("\n");
}

int setDestroy(PtSet *ptSet)
{
    PtSet set = *ptSet;

    if (set == NULL)
        return SET_NULL;

    free(set->elements);
    free(set);
    *ptSet = NULL;

    return SET_OK;
}