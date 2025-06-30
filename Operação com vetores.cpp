/*
 * Exercício: Operações com Vetores- AED’s I.
 * File:   operacaovet.cpp
 * Autor: Leticia Santos Alves.
 * RA: 2025.1.08.016
 * Local: Alfenas - MG.
 * Disciplina: AED’s I - Prática.
 * Data: 21 de maio de 2025.
 * Objetivo: Realizar operações nos valores armazenados em um vetor, como:
 * contar ocorrências, buscar, excluir, inserir e outras funções...
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>

using namespace std;

#define TAM 100
// Inserir um valor em uma posição.
int inserirvalor(int vetor[], int* tamanho, int valor, int posicao) {
    if (*tamanho >= TAM || posicao < 0 || posicao > *tamanho) {
        return 0;
    }

    for (int i = *tamanho; i > posicao; i--) {
        vetor[i] = vetor[i - 1];
    }

    vetor[posicao] = valor;
    (*tamanho)++;
    return 1;
}
// Excluir a primeira ocorrencia de um valor.
int exc1oc(int vetor[], int* tamanho, int valor) {
    for (int i = 0; i < *tamanho; i++) {
        if (vetor[i] == valor) {
            for (int j = i; j < *tamanho - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*tamanho)--;
            return 1;
        }
    }
    return 0;
}
// Contar ocorrências de um vetor.
int contoc(int vetor[], int tamanho, int valor) { 
    int count = 0;
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) count++;
    }
    return count;
}
// Contar ocorrências de um vetor em um intervalo.
int contint(int vetor[], int tamanho, int inicio, int fim) {
    int count = 0;
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] >= inicio && vetor[i] <= fim) count++;
    }
    return count;
}
// Buscar a primeira ocorrencia de um valor informado.
int busc1oc(int vetor[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}
// Remover valores repetidos.
int remorep(int vetor[], int* tamanho) {
    int removidos = 0;
    for (int i = 0; i < *tamanho; i++) {
        for (int j = i + 1; j < *tamanho;) {
            if (vetor[i] == vetor[j]) {
                for (int k = j; k < *tamanho - 1; k++) {
                    vetor[k] = vetor[k + 1];
                }
                (*tamanho)--;
                removidos++;
            } else {
                j++;
            }
        }
    }
    return removidos;
}
// Imprimir o vetor.
int imprivet(int vetor[], int tamanho) {
    cout << "Vetor atual (" << tamanho << " elemento(s)): ";
    for (int i = 0; i < tamanho; i++) {
        cout << vetor[i] << " ";
    }
    cout << endl;
    return 1;
}

int main() {
    int vetor[TAM];
    int tamanho = 0;
    int opcao, valor, posicao, inicio, fim, resultado, n;

    cout << "☼Seja bem vindo ao operador de\n    vetores da Luthor Corp." << endl << endl;
    
    // Inserir o tamanho do vetor, máximo de 100.
    cout << "Quantos valores deseja inserir inicialmente (máximo 100)? ";
    cin >> n;

    if (n > TAM || n < 0) {
        cout << "Quantidade inválida." << endl;
        return 1;
    }
    // Inserir os vetores
    cout << "Digite os " << n << " valores:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> valor;
        vetor[i] = valor;
    }
    tamanho = n;

    // Menu de opções.
    while (true) {
        cout << "\n=======Menu de operações=======" << endl;
        cout << "1- Inserir valor em posição;" << endl;
        cout << "2- Contar ocorrências de um valor;" << endl;
        cout << "3- Contar ocorrências em um intervalo;" << endl;
        cout << "4- Buscar primeira ocorrência;" << endl;
        cout << "5- Excluir primeira ocorrência;" << endl;
        cout << "6- Remover valores repetidos;" << endl;
        cout << "7- Imprimir vetor;" << endl;
        cout << "0- Sair." << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Insira o valor e a posição: ";
                cin >> valor >> posicao;
                resultado = inserirvalor(vetor, &tamanho, valor, posicao);
                if (resultado)
                    cout << "Valor inserido com sucesso." << endl;
                else
                    cout << "Erro ao inserir valor." << endl;
                break;

            case 2:
                cout << "Informe o valor a contar: ";
                cin >> valor;
                resultado = contoc(vetor, tamanho, valor);
                cout << "O valor " << valor << " aparece " << resultado << " vez(es)." << endl;
                break;

            case 3:
                cout << "Informe o intervalo: ";
                cin >> inicio >> fim;
                resultado = contint(vetor, tamanho, inicio, fim);
                cout << "Existe " << resultado << " valor(es) entre " << inicio << " e " << fim << "." << endl;
                break;

            case 4:
                cout << "Informe o valor a buscar: ";
                cin >> valor;
                resultado = busc1oc(vetor, tamanho, valor);
                if (resultado != -1)
                    cout << "Valor encontrado na posição " << resultado << "." << endl;
                else
                    cout << "Valor não encontrado." << endl;
                break;

            case 5:
                cout << "Informe o valor a excluir: ";
                cin >> valor;
                resultado = exc1oc(vetor, &tamanho, valor);
                if (resultado)
                    cout << "Valor excluído com sucesso." << endl;
                else
                    cout << "Valor não encontrado." << endl;
                break;

            case 6:
                resultado = remorep(vetor, &tamanho);
                cout << resultado << " valor(es) repetido(s) foram removido(s)." << endl;
                break;

            case 7:
                imprivet(vetor, tamanho);
                break;

            case 0:
                cout << "Finalizando o programa.\nA Luthor Corp agradece." << endl;
                return 0;

            default:
                cout << "Opção inválida." << endl;
        }
    }

    return 0;
}