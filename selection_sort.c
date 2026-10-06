#include "sorts.h"

void selectionSort(int n, int* vector) {
    for (int i = 0; i < n - 1; i++) {
        int i_min = i;
        for (int j = i + 1; j < n; j++) {
            if (vector[j] < vector[i_min]) {
                i_min = j;
            }
        }
        if (i != i_min) {
            int temp = vector[i];
            vector[i] = vector[i_min];
            vector[i_min] = temp;
        }
    }
}