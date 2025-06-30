/* 
 * Projeto: Cena Gráfica - 02.
 * File:   main.cpp
 * Autor: Leticia Santos Alves.
 * RA: 2025.1.08.016
 * Local: Alfenas - MG.
 * Disciplina: AED’s I - Prática.
 * Data: 21 de abril de 2025.
 * Objetivo: Ler figuras de um arquivo, criado anteriormente no outro código, e calcular área total 
 (superfícies de figuras2D + superfícies de figuras 3D) e volume total (figuras 3D).
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
    
    // Definindo a informação de raiz quadrada que será usada para o cálculo da geratriz.
    float raizquadrada(float numero) {
    if(numero <= 0) return 0;
    float resultado = numero / 2;
    for(int i = 0; i < 5; i++) {
        resultado = (resultado + numero/resultado) / 2;
    }
    
    return resultado;
}

int main(int argc, char** argv) {

    // Definição das variáveis que serão usadas.
    ifstream arquivoEntrada("C:\\Users\\letic\\Documents\\NetBeansProjects\\Projeto1 - Cenagrafica\\cenagrafica.txt"); // Leitura do arquivo da cena gráfica no computador do usuário, logo, ele ficará de maneira diferente em cada computador.
    string figura;
    float v1, v2, v3, areaTot, volumeTot, PI;
    areaTot = 0.0;
    volumeTot = 0.0;
    PI = 3.1415926535;
    
    if (!arquivoEntrada.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl; // Caso dê erro ao abrir o arquivo.
        return 1;
    }

    while (arquivoEntrada >> figura && figura != "fim") {

        // Cálculos das áreas/volumes de cada figura presente no arquivo .txt.
        if (figura == "quadrado") {
            arquivoEntrada >> v1;
            areaTot += v1 * v1;
        } else if (figura == "retangulo") {
            arquivoEntrada >> v1 >> v2;
            areaTot += v1 * v2;
        } else if (figura == "triangulo") {
            arquivoEntrada >> v1 >> v2;
            areaTot += (v1 * v2) / 2;
        } else if (figura == "circulo") {
            arquivoEntrada >> v1;
            areaTot += PI * v1 * v1;
        } else if (figura == "cubo") {
            arquivoEntrada >> v1;
            areaTot += 6 * (v1 * v1);
            volumeTot += (v1 * v1 * v1);
        } else if (figura == "paralelepipedo") {
            arquivoEntrada >> v1 >> v2 >> v3;
            areaTot += 2 * (v1*v2 + v1*v3 + v2*v3); 
            volumeTot += v1 * v2 * v3;
        } else if (figura == "cilindro") {
            arquivoEntrada >> v1 >> v2;
            areaTot += 2 * PI * v1 * (v1 + v2);
            volumeTot += PI * v1 * v1 * v2;
        } else if (figura == "cone") {
            arquivoEntrada >> v1 >> v2;
            float geratriz = raizquadrada(v1 * v1 + v2 * v2);
            areaTot += PI * v1 * (v1 + geratriz);  
            volumeTot += (PI * v1 * v1 * v2) / 3;
        } else if (figura == "esfera") {
            arquivoEntrada >> v1;
            volumeTot += (4.0 / 3.0) * PI * (v1 * v1 * v1);
        } else {
            // Caso a figura não seja conhecida.
            cout << "Figura desconhecida: " << figura << "\n";
        }
    }

    arquivoEntrada.close();

    // Apresentação de resultados.
    cout << "\n\t==============Resultados Finais==============" << endl;
    cout << "\n\tÁrea total das figuras: " << areaTot << " unidades²" << endl;
    cout << "\n\tVolume total das figuras 3D: " << volumeTot << " unidades³" << endl;
    cout << "\n\t=====================FIM.=====================" << endl;

    return 0;
}
