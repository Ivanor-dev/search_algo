#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorts.h"

#define N_ALG   5
#define N_TIPOS 4
#define N_TAM   4

static const char* NOMES_ALG[N_ALG] = {
    "Insertion", "Selection", "Quick-Hoare", "Quick-Lomuto", "Merge"
};
static const char* NOMES_TIPO[N_TIPOS] = {
    "Aleatorio", "Poucos_unicos", "Ordenado", "Inverso"
};
static const int TAMANHOS[N_TAM] = {1000, 10000, 100000, 1000000};

#define LIMITE_QUADRATICO 100000   /* Insertion/Selection acima disso levam minutos/horas */

static void gera_array(int* v, int n, int tipo) {
    srand(12345 + n);
    for (int i = 0; i < n; i++) {
        switch (tipo) {
            case 0: v[i] = (int)((((long)rand() << 15) ^ rand()) % 1000000000L); break;
            case 1: v[i] = rand() % 10; break;   /* so 10 valores distintos */
            case 2: v[i] = i; break;             /* nao-decrescente */
            case 3: v[i] = n - i; break;         /* ordem inversa */
        }
    }
}

static void executa(int alg, int* v, int n) {
    switch (alg) {
        case 0: insertion_sort(v, n); break;
        case 1: selectionSort(n, v); break;
        case 2: quickSort_hoare(v, 0, n - 1); break;
        case 3: quickSort_lomuto(v, 0, n - 1); break;
        case 4: mergeSort(v, 0, n - 1); break;
    }
}

/* Combinacoes de custo O(n^2) que seriam inviaveis em n grande */
static int deve_pular(int alg, int tipo, int n) {
    if ((alg == 0 || alg == 1) && n > LIMITE_QUADRATICO) return 1;
    /* Lomuto com <= degenera para O(n^2/k) quando ha muitos valores repetidos */
    if (alg == 3 && tipo == 1 && n > LIMITE_QUADRATICO) return 1;
    return 0;
}

static int esta_ordenado(const int* v, int n) {
    for (int i = 1; i < n; i++)
        if (v[i - 1] > v[i]) return 0;
    return 1;
}

static double agora(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(void) {
    FILE* csv = fopen("resultados.csv", "w");
    if (!csv) { perror("resultados.csv"); return 1; }
    fprintf(csv, "algoritmo,tipo,tamanho,tempo_s\n");

    printf("%-13s %-14s %10s %12s\n", "Algoritmo", "Tipo", "Tamanho", "Tempo (s)");
    printf("---------------------------------------------------\n");

    for (int t = 0; t < N_TIPOS; t++) {
        for (int s = 0; s < N_TAM; s++) {
            int n = TAMANHOS[s];
            int reps = (n <= 10000) ? 5 : 1;   /* media em arrays pequenos */

            int* original = malloc(n * sizeof(int));
            int* copia    = malloc(n * sizeof(int));
            gera_array(original, n, t);

            for (int a = 0; a < N_ALG; a++) {
                if (deve_pular(a, t, n)) {
                    printf("%-13s %-14s %10d %12s\n", NOMES_ALG[a], NOMES_TIPO[t], n, "pulado");
                    fprintf(csv, "%s,%s,%d,\n", NOMES_ALG[a], NOMES_TIPO[t], n);
                    fflush(stdout);
                    continue;
                }

                double total = 0;
                int ok = 1;
                for (int r = 0; r < reps; r++) {
                    memcpy(copia, original, n * sizeof(int));
                    double ini = agora();
                    executa(a, copia, n);
                    total += agora() - ini;
                    if (!esta_ordenado(copia, n)) ok = 0;
                }
                double media = total / reps;

                printf("%-13s %-14s %10d %12.6f%s\n", NOMES_ALG[a], NOMES_TIPO[t], n, media,
                       ok ? "" : "  ERRO: nao ordenou!");
                fprintf(csv, "%s,%s,%d,%.6f\n", NOMES_ALG[a], NOMES_TIPO[t], n, media);
                fflush(stdout);
            }
            free(original);
            free(copia);
        }
        printf("\n");
    }
    fclose(csv);
    printf("Resultados salvos em resultados.csv\n");
    return 0;
}