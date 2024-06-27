/**
 * @file set.h
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Definition of the ADT Set in C.
 * @version 1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#define SET_OK 0
#define SET_NULL 1
#define SET_NO_MEMORY 2
#define SET_EMPTY 3
#define SET_FULL 4
#define SET_INVALID_RANK 5
#define SET_ALREADY_IN_SET 6
#define SET_INITIAL_CAPACITY 100

#include "setElem.h"
#include <stdbool.h>

/** Forward declaration of the data structure. */
struct setImpl;
/** Definition of pointer to the data stucture. */
typedef struct setImpl *PtSet;
/**
 * @brief Creates a new empty set.
 *
 * @return PtSet pointer to allocated data structure, or
 * @return NULL if unsufficient memory for allocation
 */
PtSet setCreate();
/**
 * @brief Add an element to a set.
 *
 * @param set [in] pointer to the set
 * @param elem [in] element to add
 *
 * @return SET_OK if successful, or
 * @return SET_FULL if no capacity available, or
 * @return SET_NO_MEMORY if unsufficient memory for allocation, or
 * @return SET_NULL if 'set' is NULL
 */
int setAdd(PtSet set, SetElem elem);
/**
 * @brief Removes an element from a set if it exists.
 *
 *
 * @param set [in] pointer to the set
 * @param elem [in] element to remove
 *
 * @return SET_OK if successful, or
 * @return SET_EMPTY if the set is empty, or
 * @return SET_NULL if 'set' is NULL
 */
int setRemove(PtSet set, SetElem elem);
/**
 * @brief Checks if an element is in a set.
 *
 *
 * @param set [in] pointer to the set
 * @param elem [in] element to search
 *
 * @return TRUE if the element is in the set, or
 * @return FALSE if the element is not in the set or if 'set' is NULL
 */
bool setContains(PtSet set, SetElem elem);
/**
 * @brief Retrieves the size of a set.
 *
 * @param set [in] pointer to the set
 * @param ptSize [out] address of variable to hold the value
 *
 * @return SET_OK if successful and value in 'ptSize', or
 * @return SET_NULL if 'set' is NULL
 */
int setSize(PtSet set, int *ptSize);
/**
 * @brief checks if a set has a subset.
 * 
 * @param set [in] pointer to main set
 * @param subSet [in] pointer to subset
 * 
 * @return TRUE if set1 has a subset, or
 * @return FALSE if set1 does not have a subset or if 'set1' or 'set2' is NULL
*/
bool setHasSubset(PtSet set, PtSet subSet);
/**
 * @brief Checks whether a set is empty.
 *
 * @param set [in] pointer to the set
 *
 * @return 'true' if empty or if 'set' is NULL, or
 * @return 'false' it not empty
 */
bool setIsEmpty(PtSet set);
/**
 * @brief Clears the contents of a set.
 *
 * This operation will remove all current elements in the set,
 * returning to an empty state.
 *
 * @param set [in] pointer to the set
 *
 * @return SET_OK if successful, or
 * @return SET_NULL if 'set' is NULL
 */
int setClear(PtSet set);
/**
 * @brief Retrieves the values of a set.
 *
 * This function returns a dynamically allocated array
 * with length equal to the size of the set, containing
 * the values of the set in no particular order.
 *
 * The caller is responsible for deallocating
 * (freeing) the array.
 *
 * @param set [in] pointer to the set
 *
 * @return array containing the values
 * @return NULL if 'set' is empty or NULL
 */
SetElem *setValues(PtSet set);
/**
 * @brief Prints the contents of a set.
 *
 * @param set [in] pointer to the set
 */
void setPrint(PtSet set);
/**
 * @brief Free all resources of a set.
 *
 * @param ptSet [in] ADDRESS OF pointer to the set
 *
 * @return SET_OK if success, or
 * @return SET_NULL if '*ptSet' is NULL
 */
int setDestroy(PtSet *ptSet);