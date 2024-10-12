//Return codes for other libraries

#ifndef RETURN_CODE_H
#define RETURN_CODE_H

typedef enum RETURN_CODE {


    _INVALID_ARG_PASS_,      //Invalid argument (e.g NULL ptr)
    _INVALID_MODE_PASS_,     //Used for functions that might accept modes based on a char

    _ALLOC_FAILURE_,         //If dynamic memory allocation fails

    _FILE_NOT_OPENED_,       //If a file was not opened
    _FILE_NOT_CLOSED_,       //If a file was not closed

    _ALREADY_EXISTS_,        //If an item already exists and trying to create another

    _KEY_ERROR_,             //Key error (e.g key does not exist in dict)
    _VALUE_ERROR_,           //Value error (e.g value not found in array or dict)

    _INDEX_ERROR_,           //Index error (e.g access beyond array bounds)



    _CRITICAL_ERROR_,        //Exit the program ASAP - warning to caller
    _INTERNAL_ERROR_,        //Program did something it wasn't supposed to (wrong logic)

    _SUCCESS_,               //Function ran successfully

} RETURN_CODE;



#endif //RETURN_CODE_H


