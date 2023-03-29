#include <stdio.h>
#include <stdlib.h>


/******************************ATTENTION -> DO NOT FORGET TO FREE THE STORAGE AFTER THE USAGE****************************************/



int* createarray(int length);           //just declares an array in the heap
int* createinitarray(int length);       //declares an array in the heap and initialises with 0s
int* insertontop(int* array, int length, int value);            //void - inserts a value while realloc (if unsuccesful --> NULL)
void delete_index(int* array, int length, int index);                      //void - removes while realloc
void delete_element(int* array, int length, int element);       //--||--
int* append(int* array1, int length1, int* array2, int length2);    //void - appends array2 to array1 while realloc (if unsuccessful - Null-Pointer)
void sort(int* array, int length);                                      //void - sort with BubbleSort
void printarray(int* array, int length);                                   //void - prints array
void insertto(int* array, int length, int value, int index);


/************************************************************************************************************************************/

int* createarray(int length) {
    int* array = malloc(length * sizeof(int));      //allocate storage in the heap
    if (array == NULL) {    //if unsuccessful, deliver NULLPointer
        free(array);
        return NULL;
    }
    return array;   //return pointer to array
}

int* createinitarray(int length) {
    int* array = calloc(length, sizeof(int));      //allocate storage and initialise with 0s
    if (array == NULL) {
        free(array);
        return NULL;
    }

    return array;
}

int* insertontop(int* array, int length, int value) {
    array = realloc(array, (length+1)*sizeof(int));
    if (array == NULL) {        //if the reallocation was unsuccessful, return the NullPointer
        free(array);
        return NULL;
    }
    array[length] = value;
    return array;
}

void delete_index(int* array, int length, int index) {
    for (int i = index+1; i < length; i++)      //just move everything 1 index on left since the index u wann delete
        array[i-1] = array[i];
    
    array = realloc(array, (length+1)*sizeof(int));          //realloc
}

void delete_element(int* array, int length, int element) {
    int index = -1;
    for (int i = 0; i < length; i++) {      
        if (array[i] == element) {  //firstly search for the element
            index = i;
            break;
        }
    }

    if (index < 0)      //if element not found, do nothing
        return;
    
    for (int i = index+1; i < length; i++)      //move everything left
        array[i-1] = array[i];
    
    array = realloc(array, (length+1)*sizeof(int));        //realloc space
}

int* append(int* array1, int length1, int* array2, int length2) {
    array1 = realloc(array1, (length1+length2) + sizeof(int));
    if (array1 == NULL) {
        return NULL;            //if the reallocation was unsuccessful, return the NULL-Pointer
    }
    for (int i = 0; i < length2; i++)
        array1[length1+i] = array2[i];
    
    return array1;
}

void sort(int* array, int length) {
    int sorted = 1;
    for (int i = 1; i < length; i++) {
        if (array[i] < array[i-1]) {        //just exchange 2 pairs, if not sorted
            sorted = 0;             //set sorted on 0 for recursion
            int temp = array[i];
            array[i] = array[i-1];
            array[i-1] = temp;
        }
    }

    if (!sorted)
        sort(array, length);
}

void printarray(int* array, int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        if (i < length-1)
            printf("%d, ", array[i]);
        else
            printf("%d", array[i]);
    }
    printf("]\n");
}

void insertto(int* array, int length, int value, int index) {
    if (index > length-1) {
        int* p = insertontop(array, length,value);
        if (p == NULL) {
            free(p);
            return;
        }
    }

    else
        array[index] = value;
}
