#ifndef MATRIZ_H
#define MATRIZ_H

const int TAM = 128;
typedef int Vetor[TAM][TAM];

void multiPvalor(Vetor matriz, int linhas, int colunas, int valor);
void transposta(Vetor matriz, Vetor resultado, int linhas, int colunas);
void invertcolunas(Vetor matriz, int linhas, int colunas);
void invertlinhas(Vetor matriz, int linhas, int colunas);

#endif
