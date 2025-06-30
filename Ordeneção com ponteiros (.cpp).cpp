
#include "ordenacao.h"

// Para Bubble Sort.
void bubbleSort(int *inicio, int *fim) {
    for (int *i = inicio; i < fim; i++) {
        for (int *j = inicio; j < fim - 1 - (i - inicio); j++) {
            if (*j > *(j + 1)) {
                int temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }
}

// Para Selection Sort.
void selectionSort(int *inicio, int *fim) {
    for (int *i = inicio; i < fim; i++) {
        int *min = i;
        for (int *j = i + 1; j < fim; j++) {
            if (*j < *min) {
                min = j;
            }
        }
        int temp = *i;
        *i = *min;
        *min = temp;
    }
}

// Para Insertion Sort.
void insertionSort(int *inicio, int *fim) {
    for (int *i = inicio + 1; i < fim; i++) {
        int chave = *i;
        int *j = i - 1;
        while (j >= inicio && *j > chave) {
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = chave;
    }
}
