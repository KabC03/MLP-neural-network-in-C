#include "matrix.h"
#define MACRO_ITERATE_MATRIX(matrixPtr, code)\
    for(size_t i = 0; i < matrixPtr->rows * matrixPtr->cols; i++) {\
        size_t currentIndex = i * matrixPtr->data.dataSize;;\
        void *current = (matrixPtr->data.data) + currentIndex;\
        code;\
    }

#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_REALLOC(ptr, numel, size) realloc(ptr, numel * size)
#define MACRO_FREE(ptr) free(ptr)
#define CONST_REALLOC_EXPANSION 2
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)


/**
 * @brief :: Print a float element of a matrix 
 *
 * @param :: *element :: Element to be printed
 * 
 * @return :: void 
 */
void matrix_print_float(void *element) {

    printf("%f ", *(float*)(element));
    return;
}

/**
 * @brief :: Print a matrix 
 *
 * @param :: *matrix :: Matrix to be printed 
 * @param :: print_element :: Function to print element 
 * 
 * @return :: void 
 */
void matrix_disp(Matrix *matrix, void print_element(void *element)) {

    MACRO_ITERATE_MATRIX(matrix, {
        print_element(current);

        if((i + 1) % matrix->cols == 0) {
            printf("\n");
        }
    });

    return;
}


/**
 * @brief :: Instantiates a matrix 
 *
 * @param :: *matrix :: Matrix to be initialised
 * @param :: dataSize :: Size of individual matrix element
 * @param :: rows :: Number of matrix rows 
 * @param :: cols :: Number of matrix columns 
 * 
 * @return :: bool :: Indication of whether matrix was successfully instantiated 
 */
bool matrix_init(Matrix *matrix, size_t dataSize, size_t rows, size_t cols) {

    matrix->rows = rows;
    matrix->cols = cols;
    if(vector_init(&(matrix->data), dataSize, rows * cols) == false) {
        return false;
    }

    return true;
}


/**
 * @brief :: Instantiates a matrix 
 *
 * @param :: *matrix :: Vector to be initialised
 * 
 * @return :: void
 */
void matrix_destroy(Matrix *matrix) {

    vector_destroy(&(matrix->data));
    matrix->cols = 0;
    matrix->rows = 0;

    return;
}


/**
 * @brief :: Fill a matrix with some values 
 *
 * @param :: *matrix :: Vector to be initialised
 * @param :: *data :: Items to be added to the matrix 
 * 
 * @return :: void 
 */
void matrix_fill(Matrix *matrix, void *data) {

    vector_fill(&(matrix->data), data);

    return;
}



/**
 * @brief :: Add two matricies to produce a third 
 *
 * @param :: *dest :: Resultant matrix 
 * @param :: *src1 :: Source matrix 1 
 * @param :: *src2 :: Source matrix 2
 * @param :: add_element :: Function to add element 
 * 
 * @return :: void 
 */
void matrix_add(Matrix *dest, Matrix *src1, Matrix *src2, void add_element(void *dest, void *src1, void *src2)) {


    MACRO_ITERATE_MATRIX(dest, {
        add_element(current, src1->data.data + currentIndex, src2->data.data + currentIndex);
    });


    return;
}




/**
 * @brief :: Sub two matricies to produce a third 
 *
 * @param :: *dest :: Resultant matrix 
 * @param :: *src1 :: Source matrix 1 
 * @param :: *src2 :: Source matrix 2
 * @param :: sub_element :: Function to subtract element 
 * 
 * @return :: void 
 */
void matrix_sub(Matrix *dest, Matrix *src1, Matrix *src2, void sub_element(void *dest, void *src1, void *src2)) {

    MACRO_ITERATE_MATRIX(dest, {
        sub_element(current, src1->data.data + currentIndex, src2->data.data + currentIndex);
    });

    return;
}




//Function to multiply two matrix elements together
void matrix_multiply_element_float(Matrix *dest, Matrix *src1, Matrix *src2, size_t i, size_t j) {

    float sum = 0;
    for(size_t k = 0; k < src1->cols; k++) {
        sum += *(float*)((src1->data.data) + (i * src1->cols * src1->data.dataSize) + (k * src1->data.dataSize)) *
        *(float*)((src2->data.data) + (k * src2->cols * src2->data.dataSize) + (j * src2->data.dataSize));
    }
    *(float*)((dest->data.data) + (i * dest->cols * dest->data.dataSize) + (j * dest->data.dataSize)) = sum;

    return;
}


/**
 * @brief :: Multiply two matricies to produce a third 
 *
 * @param :: *dest :: Resultant matrix 
 * @param :: *src1 :: Source matrix 1 
 * @param :: *src2 :: Source matrix 2
 * @param :: multiply_element :: Function to multiply element 
 * 
 * @return :: void 
 */
void matrix_multiply(Matrix *dest, Matrix *src1, Matrix *src2, 
void multiply_element(Matrix *dest, Matrix *src1, Matrix *src2, size_t i, size_t j)) {

    for(size_t i = 0; i < src1->rows; i++) { //For row
        for(size_t j = 0; j < src2->cols; j++) { //For col
        
            multiply_element(dest, src1, src2, i, j);
        }
    }

    return;
}





//Scale a matrix by 2 (this is a test function)
void matrix_activate_scale_2(void *element) {

    *(float*)(element) = *(float*)(element) * 2;
    return;
}


/**
 * @brief :: Activate a matrix with a function 
 *
 * @param :: *matrix:: Matrix to activate 
 * @param :: *activate :: Function to activate matrix with 
 * 
 * @return :: void 
 */
void matrix_activate(Matrix *matrix, void activate(void *element)) {

    MACRO_ITERATE_MATRIX(matrix, {
        activate(current);
    });

    return;
}





/**
 * @brief :: Transpose a matrix
 *
 * @param :: *dest :: Destination (In dimensions of desired output already)
 * @param :: *src:: Src matrix 
 * 
 * @return :: void 
 */
void matrix_transpose(Matrix *dest, Matrix *src) {

    //Assume dest is already the correct dimensions
    for(size_t i = 0; i < src->rows; i++) {
        for(size_t j = 0; j < src->cols; j++) {
            void *srcAdr = src->data.data + (src->cols * i + j) * src->data.dataSize;
            void *destAdr = dest->data.data + (dest->cols * j + i) * dest->data.dataSize;
            MACRO_MEMCPY(destAdr, srcAdr, src->data.dataSize);
        }
    }

    return;
}






/**
 * @brief :: Randomise a float element within a matrix 
 *
 * @param :: *element :: Element to randomise
 * @param :: *min :: Min value
 * @param :: *max :: Max value
 * 
 * @return :: void 
 */
void matrix_randomise_float(void *element, void *min, void *max) {

    float floatMin = *(float*)min;
    float floatMax = *(float*)max;

    float number = floatMin + (floatMax - floatMin) * ((float)rand() / (float)RAND_MAX);

    *(float*)element = number;

    return;
}


/**
 * @brief :: Fill a matrix with random values
 *
 * @param :: *matrix :: Matrix to randomise
 * @param :: *min :: Min value
 * @param :: *max :: Max value
 * @param :: *randomise :: Randomise function for individual element 
 * 
 * @return :: void 
 */
void matrix_randomise(Matrix *matrix, void *min, void *max, void randomise(void *element, void *min, void *max)) {

    //Assume dest is already the correct dimensions
    for(size_t i = 0; i < matrix->rows * matrix->cols; i++) {
        void *element = matrix->data.data + i * matrix->data.dataSize; 
        randomise(element, min, max);
    }

    return;
}





