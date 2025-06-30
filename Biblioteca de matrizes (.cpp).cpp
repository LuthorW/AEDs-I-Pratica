#include "matriz.h"

void multiPvalor(Vetor matriz, int linhas, int colunas, int valor) { // Para multiplicar por algum valor.
    int *p = &matriz[0][0];
    for (int i = 0; i < linhas * colunas; i++) {
        *(p + i) *= valor;
    }
}

void transposta(Vetor matriz, Vetor resultado, int linhas, int colunas) { // Para matriz transposta.
    int *origem = &matriz[0][0];
    int *destino = &resultado[0][0];

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            *(destino + j * TAM + i) = *(origem + i * TAM + j);
        }
    }
}

void invertcolunas(Vetor matriz, int linhas, int colunas) { // Para inverter as colunas.
    for (int i = 0; i < linhas; i++) {
        int *inicio = &matriz[i][0];
        int *fim = &matriz[i][colunas - 1];
        for (int j = 0; j < colunas / 2; j++) {
            int temp = *(inicio + j);
            *(inicio + j) = *(fim - j);
            *(fim - j) = temp;
        }
    }
}

void invertlinhas(Vetor matriz, int linhas, int colunas) { // Para inverter as linhas.
    for (int i = 0; i < linhas / 2; i++) {
        int *linha1 = &matriz[i][0];
        int *linha2 = &matriz[linhas - 1 - i][0];
        for (int j = 0; j < colunas; j++) {
            int temp = *(linha1 + j);
            *(linha1 + j) = *(linha2 + j);
            *(linha2 + j) = temp;
        }
    }
}
