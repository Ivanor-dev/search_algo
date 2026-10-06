#include "sorts.h"

void insertion_sort(int* vetor, int tam) {
    for (int i = 1; i < tam; i++) {
        int pivo = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > pivo) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = pivo;
    }
}