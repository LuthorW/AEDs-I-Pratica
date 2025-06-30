/* 
 * Projeto: Cena Gráfica - 01.
 * File:   main.cpp
 * Autor: Leticia Santos Alves.
 * RA: 2025.1.08.016
 * Local: Alfenas - MG.
 * Disciplina: AED’s I - Prática.
 * Data: 21 de abril de 2025.
 * Objetivo: Permitir o usuário criar um arquivo de texto (.txt), com os dados necessários
 para a realização dos cálculos no próximo código.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    // Definição das variáveis que serão usadas.
    ofstream arquivoSaida("cenagrafica.txt");
    int opcao, continuar;
    float v1, v2, v3;
    
    continuar = 1; // Será usado para saber quando o 'while' deverá parar.

    if (!arquivoSaida.is_open()) {
        cout << "\n\tErro ao abrir o arquivo!" << endl;
        return 1;
    }
    
    cout << "\n\tSeja bem vindo ao\n\tCriador de Cena Gráfica\n";

    while (continuar >> 0) { 
        cout << "\n\tEscolha a figura desejada:" << endl;
        cout << "\t1 - Quadrado;\n";
        cout << "\t2 - Retângulo;\n";
        cout << "\t3 - Triângulo;\n";
        cout << "\t4 - Círculo;\n";
        cout << "\t5 - Cubo;\n";
        cout << "\t6 - Paralelepípedo;\n";
        cout << "\t7 - Cilindro;\n";
        cout << "\t8 - Cone;\n";
        cout << "\t9 - Esfera;\n";
        cout << "\t0 - Finalizar e salvar o arquivo.\n";
        cout << "\tEscolha a opção: ";
        cin >> opcao; // Seleciona a opção e assim seguirá para o seu 'if' correspondente.
        
        // Entrada de dados para cada uma das figuras.
        
        if (opcao == 1) {
            cout << "\n\tInforme o lado: ";
            cin >> v1;
            arquivoSaida << "quadrado " << v1 << "\n";
        } else if (opcao == 2) {
            cout << "\n\tInforme a base e altura: ";
            cin >> v1 >> v2;
            arquivoSaida << "retangulo " << v1 << " " << v2 << "\n";
        } else if (opcao == 3) {
            cout << "\n\tInforme a base e altura: ";
            cin >> v1 >> v2;
            arquivoSaida << "triangulo " << v1 << " " << v2 << "\n";
        } else if (opcao == 4) {
            cout << "\n\tInforme o raio: ";
            cin >> v1;
            arquivoSaida << "circulo " << v1 << "\n";
        } else if (opcao == 5) {
            cout << "\n\tInforme o lado: ";
            cin >> v1;
            arquivoSaida << "cubo " << v1 << "\n";
        } else if (opcao == 6) {
            cout << "\n\tInforme a largura, altura e profundidade: ";
            cin >> v1 >> v2 >> v3;
            arquivoSaida << "paralelepipedo " << v1 << " " << v2 << " " << v3 << "\n";
        } else if (opcao == 7) {
            cout << "\n\tInforme o raio e altura: ";
            cin >> v1 >> v2;
            arquivoSaida << "cilindro " << v1 << " " << v2 << "\n";
        } else if (opcao == 8) {
            cout << "\n\tInforme o raio e altura: ";
            cin >> v1 >> v2;
            arquivoSaida << "cone " << v1 << " " << v2 << "\n";
        } else if (opcao == 9) {
            cout << "\n\tInforme o raio: ";
            cin >> v1;
            arquivoSaida << "esfera " << v1 << "\n";
        } else if (opcao == 0) {
            arquivoSaida << "fim\n";
            continuar = 0; // 'continuar' passa a ser 0 e assim o 'while' não irá continuar rodando.
        } else {
            cout << "\n\tOpção inválida!\n"; // Caso coloque uma opção fora das apresentadas.
        }
        arquivoSaida << endl;
    }

    arquivoSaida.close();
    cout << "\n\tO arquivo foi salvo como 'cenagrafica.txt'.\n\n"; // Apresenta ao usuário que o arquivo foi salvo.

    return 0;
}
