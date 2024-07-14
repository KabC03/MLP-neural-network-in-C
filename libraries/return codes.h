//Return codes for other libraries

#ifndef RETURN_CODE_H
#define RETURN_CODE_H

typedef enum RETURN_CODE {

    _NULL_PTR_PASS_,
    _UNRECOGNISED_ARGUMENT_PASS_,

    _MEMORY_ALLOCATION_FAILURE_,
    _INITIALISATION_FAILURE,


    _FAILED_TO_OPEN_FILE_,
    _FAILED_TO_CLOSE_FILE_,

    _TRUE_,
    _FALSE_,


    _GENERIC_FAILURE_,
    _NEUTRAL_,
    _SUCCESS_,

} RETURN_CODE;



#endif //RETURN_CODE_H 

 
