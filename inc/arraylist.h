/**
* Copyrigth (c) 2023, Iriarte Federico (fedeiria@gmail.com)
*
* This program is free software: you can redistribute it and/or modify it under the terms of the GNU
* General Public License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program. If not, see
* <https://www.gnu.org/licenses/>.
*/

#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ArrayList{

    int size;
    void **pElements;
    int reservedSize;

    int     (*add)();
    int     (*len)();
    int     (*set)();
    int     (*push)();
    int     (*sort)();
    int     (*clear)();
    int     (*remove)();
    int     (*indexOf)();
    int     (*isEmpty)();
    int     (*contains)();
    int     (*containsAll)();
    int     (*deleteArrayList)();
    void*   (*get)();
    void*   (*pop)();
    struct ArrayList* (*clone)();
    struct ArrayList* (*subList)();

}typedef ArrayList;

/**
 * \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList *pAux Return (NULL) if error [if can't allocate memory]
 *                              - (pointer to new arrayList) if ok
 */
ArrayList *al_newArrayList(void);

/**
 * \brief Add an element to arrayList and if is necessary resize the array
 * \param ArrayList *this pointer to arrayList
 * \param void *pElement Pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer]
 *                           (0) if ok
 */
int al_add(ArrayList *this, void *pElement);

/**
 * \brief Delete arrayList
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer]
 *                           (0) if ok
 */
int al_deleteArrayList(ArrayList *this);

/**
 * \brief Get length of arrayList
 * \param ArrayList *this pointer to arrayList
 * \return int value return length of array or (-1) if error [this is NULL pointer]
 */
int al_len(ArrayList *this);

/**
 * \brief Get an element by index
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return void *pAux return (NULL) if error [this is NULL pointer or invalid index]
 *                         - (Pointer to element) if ok
 */
void *al_get(ArrayList *this, int index);

/**
 * \brief Find if this contains at least one element pElement
 * \param ArrayList *this pointer to arrayList
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer]
 *                           (0) if ok, but not found a element
 *                           (1) if this list contains at least one element pElement
 */
int al_contains(ArrayList *this, void *pElement);

/**
 * \brief Set a element in this at index position
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer or invalid index]
 *                           (0) if ok
 */
int al_set(ArrayList *this, int index, void *pElement);

/**
 * \brief Remove an element by index
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return int value return (-1) if error [this is NULL pointer or invalid index]
 *                           (0) if ok
 */
int al_remove(ArrayList *this, int index);

/**
 * \brief Removes all of the elements from this list
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer]
 *                           (0) if ok
 */
int al_clear(ArrayList *this);

/**
 * \brief Returns an array containing all of the elements in this list in proper sequence
 * \param ArrayList *this pointer to arrayList
 * \return ArrayList *pAux return (NULL) if error [this is NULL pointer]
 *                              - (New array) if ok
 */
ArrayList *al_clone(ArrayList *this);

/**
 * \brief Inserts the element at the specified position
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer or invalid index]
 *                           (0) if ok
 */
int al_push(ArrayList *this, int index, void *pElement);

/**
 * \brief Returns the index of the first occurrence of the specified element
 * \param ArrayList *this pointer to arrayList
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer]
 *                        - (index to element) if ok
 */
int al_indexOf(ArrayList *this, void *pElement);

/**
 * \brief Returns true if this list contains no elements.
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer]
 *                           (0) if not Empty
 *                           (1) if is Empty
 */
int al_isEmpty(ArrayList *this);

/**
 * \brief Remove the item at the given position in the list, and return it.
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return void *pAux return (NULL) if error [this is NULL pointer or invalid index]
 *                         - (element pointer) if ok
 */
void *al_pop(ArrayList *this, int index);

/**
 * \brief Returns a new arrayList with a portion of pList between the specified
 *                               from Index, inclusive, and to Index, exclusive.
 * \param ArrayList *this pointer to arrayList
 * \param int from Initial index of the element (inclusive)
 * \param int to Final index of the element (exclusive)
 * \return ArrayList *pAux return (NULL) if error [this is NULL pointer or invalid 'from' or invalid 'to']
 *                              - (pointer to new array) if ok
 */
ArrayList *al_subList(ArrayList *this, int from, int to);

/**
 * \brief Returns true if this list contains all of the elements of this2
 * \param ArrayList *this pointer to arrayList
 * \param ArrayList *this2 pointer to arrayList
 * \return int value return (-1) if error [this or this2 are NULL pointer]
 *                           (0) if not contains all
 *                           (1) if is contains all
 */
int al_containsAll(ArrayList *this, ArrayList *this2);

/**
 * \brief Sorts objects of list, use compare pFunction
 * \param ArrayList *this pointer to arrayList
 * \param pFunction (*pFunction) pointer to function to compare elements of arrayList
 * \param int order [1] indicate UP - [0] indicate DOWN
 * \return int value return (-1) if error [this or pFunc are NULL pointer]
 *                           (0) if ok
 */
int al_sort(ArrayList *this, int (*pFunction)(void*, void*), int order);


// PRIVATE FUNCTIONS
/**
 * \brief Increment the number of elements in this in AL_INCREMENT elements.
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer or if can't allocate memory]
 *                           (0) if ok
 */
int resizeUp(ArrayList *this);

/**
 * \brief Expand an array list
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return int value return (-1) if error [this is NULL pointer or invalid index]
 *                           (0) if ok
 */
int expand(ArrayList *this, int index);

/**
 * \brief Contract an array list
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return int value return (-1) if error [this is NULL pointer or invalid index]
 *                           (0) if ok
 */
int contract(ArrayList *this, int index);

#endif // ARRAYLIST_H_INCLUDED
