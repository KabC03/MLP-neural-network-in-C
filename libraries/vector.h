//Generic vectors in C - uses uint8_t to index with bytes directly

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>



#define Vector(type, name)\
    Vector name;\
    vector_initialise(&name, sizeof(type));\




typedef struct Vector {

    size_t size;         //Memory of vector (num of bytes)

    size_t top;          //Top index of array (index)

    uint8_t* data;       //Data array pointer
    size_t elementSize;  //Size of individual element in array

} Vector;


bool vector_initialise(Vector *const vector, size_t elementSize);
void vector_print(const Vector *const vector);
size_t vector_get_size(const Vector *const vector);
size_t vector_get_length(const Vector *const vector);


bool vector_set_index(Vector *const vector, size_t index, const void *const data);
const uint8_t* vector_get_index(Vector *const vector, size_t index);
bool vector_insert_index(Vector *const vector, size_t index, const void *const data);
bool vector_delete_index(Vector *const vector, size_t index);
bool vector_resize(Vector *const vector, int offsetSize);
bool vector_destroy(Vector *const vector);
bool vector_quick_append(Vector *const vector, const void *const data, size_t amountOfData);

#endif // VECTOR_H



