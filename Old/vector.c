#include "vector.h"





/**
 * vector_get_size
 * ===============================================
 * Brief: Gets the size (in bytes) of a vector
 * 
 * Param: *vector - Pointer to the vector of interest
 *        elementSize - sizeof(element) in bytes
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool vector_initialise(Vector *const vector, size_t elementSize) {

    if(vector == NULL) {
        return false;
    } else {

        vector->data = NULL;
        vector->elementSize = elementSize;
        vector->size = 0;
        vector->top = 0;
    }

    return true;
}



/**
 * vector_print
 * ===============================================
 * Brief: Prints a vector of integers (Used for debugging)
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: void
 * 
 */
void vector_print(const Vector *const vector) {

    printf("[");
    if(vector == NULL) {

    } else if(vector->data == NULL) {

    } else {
    
        for(int i = 0; i < vector->top; i++) {
            printf("%d ",(vector->data)[i * (vector->elementSize)]);
        }
    }
    printf("]\n");
    return;
}




/**
 * vector_get_size
 * ===============================================
 * Brief: Gets the size (in elements) of a vector
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: size_t - Size of a vector in bytes
 * 
 */
size_t vector_get_size(const Vector *const vector) {


    size_t size = 0;
    if(vector == NULL) {
        
        return 0;

    } else {

        size = vector->size - 1;

    }
    return size;
}


/**
 * vector_get_len
 * ===============================================
 * Brief: Gets the index of the last element in the vector
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: size_t - Size of a vector in bytes
 * 
 */
size_t vector_get_length(const Vector *const vector) {

    size_t length = 0;
    if(vector == NULL) {
        return 0;
    } else {
        length = (vector->top) - 1;
    }

    return length;
}










/**
 * vector_get_index
 * ===============================================
 * Brief: Returns a pointer to an item in a vector (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 * Return: uint8_t - Pointer to data within the vector
 * 
 */
const uint8_t* vector_get_index(Vector *const vector, size_t index) {

    uint8_t *result = NULL;
    if(vector == NULL) {
        return NULL;
    } else {

        if(index + 1 > vector->top || vector->data == NULL) {
            return NULL;

        } else {

            result = &((vector->data)[index * vector->elementSize]);
        }
    }

    return result;
}


/**
 * vector_insert_index
 * ===============================================
 * Brief: Insert an item at an index in the vector (zero based indexing) - shifting elements
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 *        *data - Pointer to data to be inserted
 * Return: bool - T/F depending on if insertion was successful
 * 
 */
bool vector_insert_index(Vector *const vector, size_t index, const void *const data) {


    if(vector == NULL || data == NULL) {
        return false;
    } else if(vector->data == NULL) {
        return false;
    } else {



        if(index > vector->top + 1 || vector->top + 1 > (vector->size)) { 

            //top is the INDEX of the top element, size is the NUMBER OF BYTES in the array
            return false; //OOB error
            
        } else {
            for(size_t i = vector->top; i > index; i--) {
                memcpy(&((vector->data)[(i + 1) * (vector->elementSize)]), &((vector->data)[(i*vector->elementSize)]), vector->elementSize);
            }

            memcpy(&((vector->data)[index * vector->elementSize]), data, vector->elementSize);
        }
        vector->top++;
    }
    return true;
}






/**
 * vector_delete_index
 * ===============================================
 * Brief: Delete an item from the vector (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 * Return: bool - T/F depending on if deletion was successful
 * 
 */
bool vector_delete_index(Vector *const vector, size_t index) {

    if(vector == NULL) {
        return false;

    } else if(vector->data == NULL) {
        return false;

    } else {



        if(index > vector->top) { 
            //top is the INDEX of the top element, size is the NUMBER OF BYTES in the array

            return false; //OOB error
            
        } else {

            for(int i = index; i < vector->top - 1; i++) { //Dont need <= since last element holds junk data anyway
                memcpy(&((vector->data)[(i * vector->elementSize)]), &((vector->data)[(i + 1) * vector->elementSize]), vector->elementSize);
            }

        }
        vector->top--;
    }
    return true;
}



/**
 * vector_resize
 * ===============================================
 * Brief: Resize a vector by expanding or shrinking it (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        offsetSize - Offset of new size (number of elements)
 * Return: bool - T/F depending on if resize was successful
 * 
 */
bool vector_resize(Vector *const vector, int offsetSize) {

    if(vector == NULL) {
        return false;
    } else {

        if(offsetSize <= 0) {
            if(vector->size <= (-1) * offsetSize) {
                return false;
            }
        }



        size_t tempSize = vector->size;

        vector->size = vector->size + offsetSize;
        vector->data = realloc(vector->data, (vector->size) * vector->elementSize);


        if((vector->size) < (vector->top) + 1) { //If the top is beyond the size some elements were lost
            vector->top = vector->size;
        }


        if(vector->data == NULL) {
            vector->size = tempSize; //Set size back
            return false;
        }
    }
    return true;
}



/**
 * vector_destroy
 * ===============================================
 * Brief: Destroy a vector and associated memory
 * 
 * Param: *vector - Pointer to the vector of interest
 * 
 * Return: bool - T/F depending on if freeing was successful
 * 
 */
bool vector_destroy(Vector *const vector) {
    if(vector == NULL) {
        return false;
    } else if(vector->data == NULL) {
        return false;
    } else {

        free(vector->data);
        vector->data = NULL;

    }
    return true;
}







// SAFE functions - easy to use due to automatic resizing but have a small performance cost



/**
 * vector_set_index
 * ===============================================
 * Brief: Sets an index of the vector to data
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 *        *data - data of interest
 * Return: uint8_t - Pointer to data within the vector
 * 
 */
bool vector_set_index(Vector *const vector, size_t index, const void *const data) {

    if(vector == NULL || data == false) {
        return false;
    } else {

        if(index > vector->top || vector->data == NULL) {
            return false;

        } else {

            memcpy(&((vector->data)[index * vector->elementSize]),data, vector->elementSize);
        }
    }
    return true;
}





/**
 * vector_quick_append 
 * ===============================================
 * Brief: Appends an array of items to the end of the vector with automatic resizing (doubles in capacity each time) 
 * 
 * Param: *vector - Pointer to the vector of interest
 *        *data - data of interest
 *        amountOfData - amount of items to be added
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool vector_quick_append(Vector *const vector, const void *const data, size_t amountOfData) {

    if(vector == NULL || data == NULL || amountOfData == 0) {
        return false;
    } else {

        if(amountOfData > vector->size - vector->top) { //Allocate more memory
            vector->data = realloc(vector->data, (vector->size + amountOfData) * 2 * vector->elementSize);
            if(vector->data == NULL) {
                return false;
            }
            vector->size += amountOfData * 2;
        } else {
        
        }
        memcpy(&((vector->data)[vector->top * vector->elementSize]), data, amountOfData * vector->elementSize);
        vector->top += amountOfData;

    }

    return true;
}




/*
TODO:

- vector_insert_end
- vector_push_back
- vector_pop_back
- vector_clear
- vector_shrink_to_fit
- vector_set_size (set the size of the vector)
*/