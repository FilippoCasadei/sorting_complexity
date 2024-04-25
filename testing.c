#include "testing.h"
#include <stdio.h>

void stampa_array(int array[], int lunghezza) {
    printf("[");
    for (int i = 0; i < lunghezza; i++) {
        printf("%d", array[i]);
        if (i < lunghezza - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}