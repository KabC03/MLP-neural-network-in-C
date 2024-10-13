#include <time.h>
#include "../libraries/vector.h"
#include "../libraries/matrix.h"
#include "mlp.h"

int main(void) {

    MLP network;
    Vector layers;
    srand(time(NULL));

    size_t arr[] = {10, 3, 2, 2};
    if(vector_init(&layers, sizeof(size_t), 4) == false) {
        printf("Layer init failed\n");
        return 1;
    }
    vector_fill(&layers, arr);
    vector_disp(&layers, vector_print_size_t);



    if(MLP_init(&network, &layers) == false) {
        printf("Init failed\n");
        return 1;
    }
    MLP_disp(&network);

    return 0;
}





