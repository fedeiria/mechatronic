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

#include "../inc/arraylist.h"

// private functions
int resizeUp(ArrayList *this);
int expand(ArrayList *this, int index);
int contract(ArrayList *this, int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10

/**
 * \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList *pAux Return (NULL) if error [if can't allocate memory]
 *                              - (pointer to new arrayList) if ok
 */
ArrayList *al_newArrayList(void)
{
    ArrayList *this = NULL;
    ArrayList *pAux = NULL;
    void *pElements = NULL;

    this = (ArrayList*)malloc(sizeof(ArrayList));

    if(this != NULL){
        pElements = malloc(sizeof(void*) * AL_INITIAL_VALUE);

        if(pElements != NULL){
            this->size = 0;
            this->pElements = pElements;
            this->reservedSize = AL_INITIAL_VALUE;
            this->add = al_add;
            this->len = al_len;
            this->set = al_set;
            this->remove = al_remove;
            this->clear = al_clear;
            this->clone = al_clone;
            this->get = al_get;
            this->contains = al_contains;
            this->push = al_push;
            this->indexOf = al_indexOf;
            this->isEmpty = al_isEmpty;
            this->pop = al_pop;
            this->subList = al_subList;
            this->containsAll = al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            pAux = this;
        }
        else
            free(this);
    }

    return pAux;
}

/**
 * \brief Add an element to arrayList and if is necessary resize the array
 * \param ArrayList *this pointer to arrayList
 * \param void *pElement Pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer]
 *                           (0) if ok
 */
int al_add(ArrayList *this, void *pElement)
{
    int value = -1;

    if(this != NULL && pElement != NULL && this->size == this->reservedSize){
        resizeUp(this);
        this->pElements[this->size] = pElement;
        this->size++;
        value = 0;
    }
    else{
        this->pElements[this->size] = pElement;
        this->size++;
        value = 0;
    }

    return value;
}

/**
 * \brief Delete arrayList
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer]
 *                           (0) if ok
 */
int al_deleteArrayList(ArrayList *this)
{
    int value = -1;

    if(this != NULL){
        free(this->pElements);
        free(this);
        value = 0;
    }

    return value;
}

/**
 * \brief Get length of arrayList
 * \param ArrayList *this pointer to arrayList
 * \return int value return length of array or (-1) if error [this is NULL pointer]
 */
int al_len(ArrayList *this)
{
    int value = -1;

    if(this != NULL)
        value = this->size;

    return value;
}

/**
 * \brief Get an element by index
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return void *pAux return (NULL) if error [this is NULL pointer or invalid index]
 *                         - (Pointer to element) if ok
 */
void *al_get(ArrayList *this, int index)
{
    void *pAux = NULL;

    if(this != NULL && (index >= 0 && index < this->size))
        pAux = this->pElements[index];

    return pAux;
}

/**
 * \brief Find if this contains at least one element pElement
 * \param ArrayList *this pointer to arrayList
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer]
 *                           (0) if ok, but not found a element
 *                           (1) if this list contains at least one element pElement
 */
int al_contains(ArrayList *this, void *pElement)
{
    int i;
    int value = -1;

    if(this != NULL && pElement != NULL){
        for(i = 0; i < this->size; i++){
            if(this->pElements[i] == pElement){
                value = 1;
                break;
            }
            else
                value = 0;
        }
    }

    return value;
}

/**
 * \brief Set a element in this at index position
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer or invalid index]
 *                           (0) if ok
 */
int al_set(ArrayList *this, int index, void *pElement)
{
    int value = -1;

    if(this != NULL && pElement != NULL){
        if(index >= 0 && index < this->size){
            this->pElements[index] = pElement;
            value = 0;
        }
    }

    return value;
}

/**
 * \brief Remove an element by index
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return int value return (-1) if error [this is NULL pointer or invalid index]
 *                           (0) if ok
 */
int al_remove(ArrayList *this, int index)
{
    int i;
    int value = -1;

    if(this != NULL && (index >= 0 && index < this->size)){
        for(i = index; i < this->size - 1; i++){
            this->pElements[i] = this->pElements[i + 1];
        }

        this->size--;
        value = 0;
    }

    return value;
}

/**
 * \brief Removes all of the elements from this list
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer]
 *                           (0) if ok
 */
int al_clear(ArrayList *this)
{
    int i;
    int value = -1;

    if(this != NULL){
        for(i = 0; i < this->reservedSize; i++){
            free(this->pElements[i]);
        }

        this->size = 0;
        value = 0;
    }

    return value;
}

/**
 * \brief Returns an array containing all of the elements in this list in proper sequence
 * \param ArrayList *this pointer to arrayList
 * \return ArrayList *pAux return (NULL) if error [this is NULL pointer]
 *                              - (New array) if ok
 */
ArrayList *al_clone(ArrayList *this)
{
    int i;
    ArrayList *pAux = NULL;

    if(this != NULL){
        pAux = al_newArrayList();

        if(pAux != NULL){
            for(i = 0; i < this->size; i++)
                al_add(pAux, al_get(this, i));
        }
    }

    return pAux;
}

/**
 * \brief Inserts the element at the specified position
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer or invalid index]
 *                           (0) if ok
 */
int al_push(ArrayList *this, int index, void *pElement)
{
    int i;
    int value = -1;

    if(this != NULL && pElement != NULL){
        if(index >= 0 && index <= this->size){
            if(this->size == this->reservedSize){
                resizeUp(this);

                for(i = index; i < this->size - 1; i++){
                    this->pElements[i + 1] = this->pElements[i];
                }

                this->pElements[index] = pElement;
                this->size++;
            }
            else{
                for(i = index; i < this->size - 1; i++){
                    this->pElements[i + 1] = this->pElements[i];
                }

                this->pElements[index] = pElement;
                this->size++;
            }
        }
        value = 0;
    }

    return value;
}

/**
 * \brief Returns the index of the first occurrence of the specified element
 * \param ArrayList *this pointer to arrayList
 * \param void *pElement pointer to element
 * \return int value return (-1) if error [this or pElement are NULL pointer]
 *                        - (index to element) if ok
 */
int al_indexOf(ArrayList *this, void *pElement)
{
    int i;
    int value = -1;

    if(this != NULL && pElement != NULL){
        for(i = 0; i < this->size; i++){
            if(this->pElements[i] == pElement){
                value = i;
                break;
            }
        }
    }

    return value;
}

/**
 * \brief Returns true if this list contains no elements.
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer]
 *                           (0) if not Empty
 *                           (1) if is Empty
 */
int al_isEmpty(ArrayList *this)
{
    int value = -1;

    if(this != NULL){
        if(this->size == 0)
            value = 1;

        else
            value = 0;
    }

    return value;
}

/**
 * \brief Remove the item at the given position in the list, and return it.
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return void *pAux return (NULL) if error [this is NULL pointer or invalid index]
 *                         - (element pointer) if ok
 */
void *al_pop(ArrayList *this, int index)
{
    void *pAux = NULL;

    if(this != NULL && (index >= 0 && index < this->size)){
        pAux = al_get(this, index);
        al_remove(this, index);
    }

    return pAux;
}

/**
 * \brief Returns a new arrayList with a portion of pList between the specified from Index, inclusive, and to Index, exclusive.
 * \param ArrayList *this pointer to arrayList
 * \param int from Initial index of the element (inclusive)
 * \param int to Final index of the element (exclusive)
 * \return ArrayList *pAux return (NULL) if error [this is NULL pointer or invalid 'from' or invalid 'to']
 *                              - (pointer to new array) if ok
 */
ArrayList *al_subList(ArrayList *this, int from, int to)
{
    int i;
    ArrayList *pAux = NULL;

    if(this != NULL && (from >= 0 && from < to && to <= this->size)){
        pAux = al_newArrayList();

        if(pAux != NULL){
            for(i = from; i <= to; i++)
                al_add(pAux, al_get(this, i));
        }
    }

    return pAux;
}

/**
 * \brief Returns true if this list contains all of the elements of this2
 * \param ArrayList *this pointer to arrayList
 * \param ArrayList *this2 pointer to arrayList
 * \return int value return (-1) if error [this or this2 are NULL pointer]
 *                           (0) if not contains all
 *                           (1) if is contains all
 */
int al_containsAll(ArrayList *this, ArrayList *this2)
{
    int i;
    int value = -1;

    if(this != NULL && this2 != NULL){
        for(i = 0; i < this->size; i++){
            if(this->pElements[i] == this2->pElements[i])
                value = 1;

            else
                value = 0;
        }
    }

    return value;
}

/**
 * \brief Sorts objects of list, use compare pFunction
 * \param ArrayList *this pointer to arrayList
 * \param pFunction (*pFunction) pointer to function to compare elements of arrayList
 * \param int order [1] indicate UP - [0] indicate DOWN
 * \return int value return (-1) if error [this or pFunc are NULL pointer]
 *                           (0) if ok
 */
int al_sort(ArrayList *this, int (*pFunction)(void*, void*), int order)
{
    int i, j;
    int value = 0;
    void *pAux = NULL;

    if(this != NULL && pFunction != NULL && (order == 1 || order == 0)){
        for(i = 0; i < this->size - 1; i++){
            for(j = i + 1; j < this->size; j++){
                if(pFunction(this->pElements[i], this->pElements[j]) > 0 && order == 1){
                    pAux = this->pElements[i];
                    this->pElements[i] = this->pElements[j];
                    this->pElements[j] = pAux;
                }
                if(!(pFunction(this->pElements[i], this->pElements[j]) > 0 && order == 0)){
                    pAux = this->pElements[i];
                    this->pElements[i] = this->pElements[j];
                    this->pElements[j] = pAux;
                }
            }
        }
        value = 1;
    }

    return value;
}

/**
 * \brief Increment the number of elements in this in AL_INCREMENT elements.
 * \param ArrayList *this pointer to arrayList
 * \return int value return (-1) if error [this is NULL pointer or if can't allocate memory]
 *                           (0) if ok
 */
int resizeUp(ArrayList *this)
{
    int value = -1;
    void *pAux = NULL;

    if(this != NULL){
        pAux = realloc(this->pElements, sizeof(void*) * (this->size + AL_INCREMENT));

        if(pAux != NULL){
            this->pElements = pAux;
            this->reservedSize = (this->size + AL_INCREMENT);
        }
        value = 0;
    }

    return value;
}

/**
 * \brief Expand an array list
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return int value return (-1) if error [this is NULL pointer or invalid index]
 *                           (0) if ok
 */
int expand(ArrayList *this, int index)
{
    int value = -1;
    void *pAux = NULL;

    if(this != NULL && (index > 0 && index <= this->reservedSize)){
        pAux = realloc(this->pElements, sizeof(void*) * (this->size + index));

        if(pAux != NULL){
            this->pElements = pAux;
            this->reservedSize = (this->size + index);
            value = 0;
        }
    }

    return value;
}

/**
 * \brief Contract an array list
 * \param ArrayList *this pointer to arrayList
 * \param int index Index of the element
 * \return int value return (-1) if error [this is NULL pointer or invalid index]
 *                           (0) if ok
 */
int contract(ArrayList *this, int index)
{
    int auxSize;
    int value = -1;
    void *pAux = NULL;

    if(this != NULL && (index > 0 && index <= this->reservedSize)){
        auxSize = (this->reservedSize - this->size);

        if(index <= auxSize)
            pAux = realloc(this->pElements, sizeof(void*) * index);

        if(pAux != NULL){
            this->pElements = pAux;
            this->reservedSize -= index;
            value = 0;
        }
    }

    return value;
}
