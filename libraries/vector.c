#include "vector.h"
//23 September 2024

#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_REALLOC(ptr, numel, size) realloc(ptr, numel * size)
#define MACRO_FREE(ptr) free(ptr)
#define CONST_REALLOC_EXPANSION 2
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)





/**
 * @brief :: Helper function for printing size_t (for use in vector_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void vector_print_size_t(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%zu ", *((size_t*)ptr));
    }
    return;
}
/**
 * @brief :: Helper function for printing integers (for use in vector_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void vector_print_integer(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d ", *((int*)ptr));
    }
    return;
}



/**
 * @brief :: Helper function for printing uint8_t (for use in vector_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void vector_print_uint8_t(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%u ", *((uint8_t*)ptr));
    }
    return;
}


/**
 * @brief :: Display the status of a vector and all of its elements
 *
 * @param :: *vector :: Vector to be displayed
 * @param :: print_element :: Print function for individual element
 * 
 * @return :: void
 */
void vector_disp(Vector *vector, void print_element(void *element)) {

    printf("=====VECTOR STATUS=====\n");
    if(vector == NULL) {
        printf("NULL\n");
        return;
    }
    printf("\tCapacity: %zu\n\tTop: %zu\n\tData size: %d\n\n",vector->capacity, vector->top, vector->dataSize);

    printf("Data:\n");
    if(vector->data == NULL) {
        printf("NULL\n");
        return;
    }
    for(size_t i = 0; i < vector->top; i++) {
        print_element((void*)(&((vector->data)[i * vector->dataSize])));
    }
    printf("\n=======================\n");

    return;
}

/**
 * @brief :: Initialises a vector with a specified datasize and initial capacity
 *
 * @param :: *vector :: Vector to be initialised
 * @param :: dataSize :: Size of individual vector element
 * @param :: numel :: Number of initial elements in vector
 * 
 * @return :: bool :: Indicates if memory was successfully allocated for vector
 */
bool vector_init(Vector *vector, uint8_t dataSize, size_t numel) {

    vector->data = MACRO_MALLOC(dataSize, numel);
    if(vector->data == NULL) {
        return false;
    }
    vector->capacity = numel;

    vector->dataSize = dataSize;
    vector->top = 0;

    return true;
}



/**
 * @brief :: Destroys a vector and all associated data
 *
 * @param :: *vector :: Vector to be destroyed
 * 
 * @return :: void
 */
void vector_destroy(Vector *vector) {

    MACRO_FREE(vector->data);
    vector->data = NULL;
    vector->capacity = 0;
    vector->top = 0;

    return;
}



/**
 * @brief :: Resize a vector. Upon failure the vector is unchanged
 *
 * @param :: numel :: Number of elements the vector should hold
 * 
 * @return :: bool :: Indicates if resizing was successful
 */
bool vector_resize(Vector *vector, size_t numel ) {

    vector->data = MACRO_REALLOC(vector->data, numel, vector->dataSize);
    if(vector->data == NULL) {
        //NOTE: Realloc function is responsible for maintaining original vector state if allocation fails
        return false;

    } else {
        vector->capacity = numel;
        vector->top = (vector->top < numel ? vector->top : numel);
    }

    return true;
}



/**
 * @brief :: Append elements to a vector. Upon failure the vector is unchanged
 *
 * @param :: *vector :: Vector of interest
 * @param :: *data :: Data to be appended to vector
 * @param :: numel :: Number of elements to be appended
 * 
 * @return :: void* :: Newly inserted item in the vector 
 */
void *vector_append(Vector *vector, void *data, size_t numel) {

    if(vector->capacity >= vector->top + numel) {
        //No reallocation required
    } else {
        //Allocation required
        vector->data = MACRO_REALLOC(vector->data, (vector->capacity + numel) * CONST_REALLOC_EXPANSION, vector->dataSize);
        if(vector->data == NULL) {
            //NOTE: Realloc function is responsible for maintaining original vector state if allocation fails 
            return NULL;
        } else {
            vector->capacity = (vector->capacity + numel) * CONST_REALLOC_EXPANSION;
        }
    }
    void *position = vector->data + vector->top * vector->dataSize;
    MACRO_MEMCPY(position, data, numel * vector->dataSize); 
    vector->top += numel;



    return position;
}




/**
 * @brief :: Access a vector at an index. UNSAFE
 *
 * @param :: *vector :: Vector of interest
 * @param :: index ::  Index of access 
 * 
 * @return :: *void :: Data at index of interest
 */
void *vector_access_index(Vector *vector, size_t index) {

    return (void*)(&((vector->data)[index * vector->dataSize]));
}


/**
 * @brief :: Set a vector index to a value. The top is adjusted to be equal to the index. UNSAFE
 *
 * @param :: *vector :: Vector of interest
 * @param :: *data :: Data to place into vector
 * @param :: index ::  Index of access
 * 
 * @return :: void* :: Data at index of interest
 */
void *vector_set_index(Vector *vector, void *data, size_t index) {

    void *dest = &((vector->data)[index * vector->dataSize]);
    MACRO_MEMCPY(dest, data, vector->dataSize);

    if(index > vector->top - 1) {
        vector->top = index + 1; 
    }
    return dest;
}


/**
 * @brief :: Fill a matrix with data 
 *
 * @param :: *vector :: Vector of interest
 * @param :: *data :: Data to place into vector
 * 
 * @return :: void
 */
void vector_fill(Vector *vector, void *data) {

    vector->top = vector->capacity;
    uint8_t *ptr = data;
    for(size_t i = 0; i < vector->top; i++) {
        size_t index = i * vector->dataSize;
        MACRO_MEMCPY(&((vector->data)[index]), &((ptr)[index]), vector->dataSize);
    }

    return;    
}






