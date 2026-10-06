#ifndef SORTS_H
#define SORTS_H

void insertion_sort(int* vetor, int tam);
void selectionSort(int n, int* vector);
void quickSort_hoare(int* vector, int left, int right);
void quickSort_lomuto(int* vector, int left, int right);
void mergeSort(int A[], int p, int r);

#endif