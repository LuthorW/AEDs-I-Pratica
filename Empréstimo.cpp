/* 
 * Exercício: Sistema de Aprovação de Empréstimo.
 * File:   main.cpp
 * Autor: Leticia Santos Alves.
 * RA: 2025.1.08.016
 * Local: Alfenas - MG.
 * Disciplina: AED’s I - Prática.
 * Data: 27 de março de 2025.
 * Objetivo: O objetivo desse código é avaliar solicitações bancárias com base nos dados inseridos pelo usuário, classificando o empréstimo em quatro possíveis: Negado,
 * Baixo Valor, Médio Valor e Alto Valor.
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
    
    // Declaração das variáveis que serão usadas neste código.
    int idade, NomeNeg, ParcAtrAt, ParcAtr2;
    float RendaMens;

    printf("\n\n\tSeja bem vindo(a) ao avaliador de\n\tsolicitações de empréstimos do\n\tLuthor Bank International.");

    // Entrada de dados, inseridos pelo usuário, que serão armazenados.
    printf("\n\n\tInforme sua idade: ");
    scanf("%d", &idade);
    
    printf("\n\tInforme sua renda mensal: R$ ");
    scanf("%f", &RendaMens);

    printf("\n\tNome negativado? (Insira 1 para 'Sim' ou 0 para 'Não'): ");
    scanf("%d", &NomeNeg);

    printf("\n\tQuantas parcelas estão em atraso atualmente?: ");
    scanf("%d", &ParcAtrAt);

    printf("\n\tQuantas parcelas estiveram em atraso nos últimos 2 anos?: ");
    scanf("%d", &ParcAtr2);

    
    // Avaliação das condições para a classificação do empréstimo do usuário.
    if (RendaMens < 2000 || NomeNeg == 1 || idade < 18 || idade > 70) {
        // Caso a renda seja inferior a R$2.000,00, se estiver negativado ou fora da faixa etária, o empréstimo será negado.
        printf("\n\n\tClassificação: O seu empréstimo foi negado.\n");
    } 
        else if (RendaMens >= 2000 && RendaMens < 5000 && ParcAtrAt <= 2) {
            // Caso a renda esteja entre R$2.000,00 e R$4.999,99 e houver, no máximo, 2 parcelas em atraso, o empréstimo será de baixo valor.
            printf("\n\n\tClassificação: Empréstimo de Baixo Valor (até R$ 5.000,00).\n");
        } 
            else if (RendaMens >= 5000 && RendaMens < 10000 && ParcAtr2 <= 4) {
                // Caso a renda esteja entre R$5.000,00 e R$9.999,99 e houver, no máximo, 4 atrasos nos últimos 2 anos, o empréstimo será de médio valor.
                printf("\n\n\tClassificação: Empréstimo de Médio Valor (até R$ 20.000,00).\n");
            } 
                else if (RendaMens >= 10000 && ParcAtr2 == 0) {
                    // Caso a renda seja superior a R$10.000,00 e não houver atrasos nos últimos 2 anos, o empréstimo será de alto valor.
                    printf("\n\n\tClassificação: Empréstimo de Alto Valor (acima de R$ 20.000,00).\n");
                } 
                    else {
                        // Caso contrário, o empréstimo será negado.
                        printf("\n\n\tClassificação: O seu empréstimo foi negado.\n");
                    }
    
    return (0);
    
}



