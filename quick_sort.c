#include <stdlib.h>
#include "sorts.h"

static void troca(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static int partition_hoare(int* vector, int inicio, int fim) {
    int pivo = vector[inicio + (fim - inicio) / 2];
    int i = inicio - 1;
    int j = fim + 1;

    while (1) {
        do { i++; } while (vector[i] < pivo);
        do { j--; } while (vector[j] > pivo);

        if (i >= j) return j;

        troca(&vector[i], &vector[j]);
    }
}

static int partition_lomuto(int* vector, int inicio, int fim) {
    int k = inicio + rand() % (fim - inicio + 1);
    troca(&vector[k], &vector[fim]);

    int pivo = vector[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (vector[j] <= pivo) {
            i++;
            troca(&vector[i], &vector[j]);
        }
    }
    troca(&vector[i + 1], &vector[fim]);
    return i + 1;
}

void quickSort_hoare(int* vector, int left, int right) {
    while (left < right) {
        int middle = partition_hoare(vector, left, right);
        if (middle - left < right - middle) {
            quickSort_hoare(vector, left, middle);
            left = middle + 1;
        } else {
            quickSort_hoare(vector, middle + 1, right);
            right = middle;
        }
    }
}

void quickSort_lomuto(int* vector, int left, int right) {
    while (left < right) {
        int middle = partition_lomuto(vector, left, right);
        if (middle - left < right - middle) {
            quickSort_lomuto(vector, left, middle - 1);
            left = middle + 1;
        } else {
            quickSort_lomuto(vector, middle + 1, right);
            right = middle - 1;
        }
    }
}