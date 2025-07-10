/*
 * Projeto: Processamento de Imagens em Tons de Cinza.
 * File:   editor.cpp
 * Autor: Leticia Santos Alves e Luiz Gustavo Custódio Leite.
 * RA: 2025.1.08.016 e 2025.1.08.031.
 * Local: Alfenas - MG.
 * Disciplina: AED’s I - Prática.
 * Data: 02 de julho de 2025.
 * Objetivo: Desenvolver um editor de imagens PGM (P2) para manipulação de pixels utilizando aritmética de ponteiros, 
 * permitindo operações como ajuste de brilho, binarização, negativo, rotação, espelhamento e iconização.
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

// Definições para alocação estática e limites máximos da imagem.
const int MAX_ALT = 1024;
const int MAX_LARG = 1024;
const int MAX_PIXELS = MAX_ALT * MAX_LARG;

// Arrays estáticos para os dados da imagem.
int imagemDados[MAX_PIXELS];
int imagemTempDados[MAX_PIXELS];

// Variáveis globais para a imagem.
char g_tipo[3] = "P2";
int g_colunas = 0;
int g_linhas = 0;
int g_maxCinza = 0;

bool lerImg(const char* nomeArq);
void escreverImg(const char* nomeArq, const int* imgPtr, int colunas, int linhas, int maxCinza);
void clarear(int* imgPtr, int colunas, int linhas, int maxCinza, int fator);
void escurecer(int* imgPtr, int colunas, int linhas, int maxCinza, int fator);
void negativa(int* imgPtr, int colunas, int linhas, int maxCinza);
void binarizar(int* imgPtr, int colunas, int linhas, int maxCinza, int limiar);
void rotacionarEsquerda();
void rotacionarDireita();
void espelhamentoHorizontal();
void espelhamentoVertical();
void iconizar(const char* nomeArqSaida);

// Lê imaem PGM de arquivo para o array global 'imagemDados'.
bool lerImg(const char* nomeArq) {
    FILE *arq = fopen(nomeArq, "r");
    if (!arq) {
        cerr << "Não foi possível abrir o arquivo '" << nomeArq << "' para leitura." << endl;
        g_colunas = 0; g_linhas = 0;
        return false;
    }

    char buffer[256];
    
    // Lê o tipo da imagem (P2) e verifica.
    if (fscanf(arq, "%s", g_tipo) != 1 || strcmp(g_tipo, "P2") != 0) {
        cerr << "Formato de imagem invalido. Apenas P2 é suportado." << endl;
        fclose(arq); g_colunas = 0; g_linhas = 0; return false;
    }
    char c;
    while ((c = fgetc(arq)) != EOF && c != '\n');
    while (fgets(buffer, sizeof(buffer), arq)) {
        char* trimmedBuffer = buffer;
        while (*trimmedBuffer == ' ' || *trimmedBuffer == '\t' || *trimmedBuffer == '\n' || *trimmedBuffer == '\r') trimmedBuffer++;
        if (strlen(trimmedBuffer) == 0 || trimmedBuffer[0] == '#') continue;
        if (sscanf(buffer, "%d %d", &g_colunas, &g_linhas) == 2) break;
    }

    // Verifica se as dimensões são válidas e se a imagem excede o limite estático.
    if (g_colunas <= 0 || g_linhas <= 0 || (long long)g_colunas * g_linhas > MAX_PIXELS) {
        cerr << "Dimensões da imagem inválidas ou excede limite estático." << endl;
        fclose(arq); g_colunas = 0; g_linhas = 0; return false;
    }

    while (fgets(buffer, sizeof(buffer), arq)) {    // Ignora comentários antes do valor máximo de cinza.
        char* trimmedBuffer = buffer;
        while (*trimmedBuffer == ' ' || *trimmedBuffer == '\t' || *trimmedBuffer == '\n' || *trimmedBuffer == '\r') trimmedBuffer++;
        if (strlen(trimmedBuffer) == 0 || trimmedBuffer[0] == '#') continue;
        if (sscanf(buffer, "%d", &g_maxCinza) == 1) break;
    }
    // Verifica se o valor máximo de cinza é válido.
    if (g_maxCinza <= 0) {
        cerr << "Valor máximo de tom de cinza inválido ou não encontrado." << endl;
        fclose(arq); g_colunas = 0; g_linhas = 0; return false;
    }

    // Leitura pixels usando aritmética de ponteiros.
    int *ptrPxLeitura = imagemDados;
    int totalPxs = g_colunas * g_linhas;
    for (int k = 0; k < totalPxs; ++k) {
        if (fscanf(arq, "%d", ptrPxLeitura++) != 1) {
            cerr << "Falha ao ler pixel " << k << endl;
            fclose(arq); g_colunas = 0; g_linhas = 0; return false;
        }
    }
    fclose(arq);
    return true;
}

// Escreve os dados de um array de pixels em um arquivo PGM.
void escreverImg(const char* nomeArq, const int* imgPtr, int colunas, int linhas, int maxCinza) {
    if (!imgPtr || colunas == 0 || linhas == 0) return;

    FILE *arq = fopen(nomeArq, "w");
    if (!arq) { cerr << "Não foi possivel abrir o arquivo '" << nomeArq << "' para escrita." << endl; return; }

    fprintf(arq, "%s\n", g_tipo);
    fprintf(arq, "%d %d\n", colunas, linhas);
    fprintf(arq, "%d\n", maxCinza);

    const int *ptrPxEscrita = imgPtr;
    int totalPxs = colunas * linhas;
    for (int k = 0; k < totalPxs; ++k) {
        fprintf(arq, "%d ", *ptrPxEscrita++);
        if ((k + 1) % 20 == 0) fprintf(arq, "\n");
    }
    fprintf(arq, "\n");
    fclose(arq);
}

void clarear(int* imgPtr, int colunas, int linhas, int maxCinza, int fator) {   // Aumenta o brilho da imagem.
    int *ptrPx = imgPtr;
    int totalPxs = colunas * linhas;
    for (int k = 0; k < totalPxs; ++k) {
        *ptrPx += fator;
        if (*ptrPx > maxCinza) *ptrPx = maxCinza;
        ptrPx++;
    }
}

void escurecer(int* imgPtr, int colunas, int linhas, int maxCinza, int fator) {     // Diminui o brilho da imagem.
    int *ptrPx = imgPtr;
    int totalPxs = colunas * linhas;
    for (int k = 0; k < totalPxs; ++k) {
        *ptrPx -= fator;
        if (*ptrPx < 0) *ptrPx = 0;
        ptrPx++;
    }
}

void negativa(int* imgPtr, int colunas, int linhas, int maxCinza) {     // Inverte os tons de cinza da imagem.
    int *ptrPx = imgPtr;
    int totalPxs = colunas * linhas;
    for (int k = 0; k < totalPxs; ++k) {
        *ptrPx = maxCinza - *ptrPx;
        ptrPx++;
    }
}

void binarizar(int* imgPtr, int colunas, int linhas, int maxCinza, int limiar) {    // Binariza a imagem com base em um limiar.
    int *ptrPx = imgPtr;
    int totalPxs = colunas * linhas;
    for (int k = 0; k < totalPxs; ++k) {
        *ptrPx = (*ptrPx < limiar) ? 0 : maxCinza;
        ptrPx++;
    }
}

void rotacionarEsquerda() {     // Rotaciona a imagem para a esquerda.
    if (g_colunas == 0 || g_linhas == 0) return;

    int novaColunas = g_linhas;
    int novaLinhas = g_colunas;

    if ((long long)novaColunas * novaLinhas > MAX_PIXELS) {
        cerr << "Imagem rotacionada (" << novaColunas << "x" << novaLinhas << ") excede os limites estáticos." << endl;
        g_colunas = 0; g_linhas = 0;
        return;
    }
    for (int cOrig = 0; cOrig < g_colunas; ++cOrig) {    // Preenche 'imagemTempDados' com a imagem rotacionada.
        for (int lOrig = g_linhas - 1; lOrig >= 0; --lOrig) {
            int offsetOrig = (lOrig * g_colunas) + cOrig;
            int offsetNova = (cOrig * novaColunas) + (g_linhas - 1 - lOrig);
            *(imagemTempDados + offsetNova) = *(imagemDados + offsetOrig);
        }
    }
    // Atualiza dimensões globais e copia de volta para 'imagemDados'.
    g_colunas = novaColunas;
    g_linhas = novaLinhas;
    memcpy(imagemDados, imagemTempDados, g_colunas * g_linhas * sizeof(int));
}

void rotacionarDireita() {  // Rotaciona a imagem para a direita.
    if (g_colunas == 0 || g_linhas == 0) return;

    int novaColunas = g_linhas;
    int novaLinhas = g_colunas;

    if ((long long)novaColunas * novaLinhas > MAX_PIXELS) {
        cerr << "Imagem rotacionada (" << novaColunas << "x" << novaLinhas << ") excede os limites estaticos." << endl;
        g_colunas = 0; g_linhas = 0;
        return;
    }
    for (int cOrig = g_colunas - 1; cOrig >= 0; --cOrig) {    // Preenche 'imagemTempDados' com a imagem rotacionada.
        for (int lOrig = 0; lOrig < g_linhas; ++lOrig) {
            int offsetOrig = (lOrig * g_colunas) + cOrig;
            int offsetNova = (cOrig * novaColunas) + lOrig;
            *(imagemTempDados + offsetNova) = *(imagemDados + offsetOrig);
        }
    }
    // Atualiza dimensões globais e copia de volta para 'imagemDados'.
    g_colunas = novaColunas;
    g_linhas = novaLinhas;
    memcpy(imagemDados, imagemTempDados, g_colunas * g_linhas * sizeof(int));
}

void espelhamentoHorizontal() {     // Espelha a imagem horizontalmente.
    if (g_colunas == 0 || g_linhas == 0) return;
    for (int l = 0; l < g_linhas; ++l) {    // Preenche 'imagemTempDados' com a imagem espelhada.
        for (int c = 0; c < g_colunas; ++c) {
            int offsetOrig = (l * g_colunas) + c;
            int offsetNova = (l * g_colunas) + (g_colunas - 1 - c);
            *(imagemTempDados + offsetNova) = *(imagemDados + offsetOrig);
        }
    }
    // Copia de volta para 'imagemDados'.
    memcpy(imagemDados, imagemTempDados, g_colunas * g_linhas * sizeof(int));
}

void espelhamentoVertical() {   // Espelha a imagem verticalmente.
    if (g_colunas == 0 || g_linhas == 0) return;
    for (int l = 0; l < g_linhas; ++l) {    // Preenche 'imagemTempDados' com a imagem espelhada.
        for (int c = 0; c < g_colunas; ++c) {
            int offsetOrig = (l * g_colunas) + c;
            int offsetNova = ((g_linhas - 1 - l) * g_colunas) + c;
            *(imagemTempDados + offsetNova) = *(imagemDados + offsetOrig);
        }
    }
    memcpy(imagemDados, imagemTempDados, g_colunas * g_linhas * sizeof(int));
}

// Cria uma versão iconizada (64x64) da imagem.
void iconizar(const char* nomeArqSaida) {
    if (g_colunas == 0 || g_linhas == 0) { cerr << "Nenhuma imagem carregada para iconizar." << endl; return; }

    const int NOVA_LARG_ICONE = 64;
    const int NOVA_ALT_ICONE = 64;

    if ((long long)NOVA_LARG_ICONE * NOVA_ALT_ICONE > MAX_PIXELS) {
        cerr << "Dimensões do ícone excedem os limites estáticos." << endl; return;
    }

    double fatorX = (double)g_colunas / NOVA_LARG_ICONE;
    double fatorY = (double)g_linhas / NOVA_ALT_ICONE;

    int *ptrNova = imagemTempDados;
    for (int lNova = 0; lNova < NOVA_ALT_ICONE; ++lNova) {
        for (int cNova = 0; cNova < NOVA_LARG_ICONE; ++cNova) {
            int cOrigMap = (int)(cNova * fatorX);
            int lOrigMap = (int)(lNova * fatorY);
            if (cOrigMap >= g_colunas) cOrigMap = g_colunas - 1;
            if (lOrigMap >= g_linhas) lOrigMap = g_linhas - 1;

            int offsetOrig = (lOrigMap * g_colunas) + cOrigMap;
            *ptrNova = *(imagemDados + offsetOrig);
            ptrNova++;
        }
    }
    // Salva a imagem iconizada do buffer temporário.
    escreverImg(nomeArqSaida, imagemTempDados, NOVA_LARG_ICONE, NOVA_ALT_ICONE, g_maxCinza);
    cout << "Imagem iconizada (64x64) salva como '" << nomeArqSaida << "'." << endl;
}

int main() {
    const char* nomeArqEnt = "projeto.pgm";
    bool imgCarregada = lerImg(nomeArqEnt);

    if (!imgCarregada) {
        cerr << "Falha ao carregar a imagem 'projeto.pgm'. Encerrando o programa." << endl;
        return 1;
    }
    cout << "Imagem '" << nomeArqEnt << "' carregada com sucesso! (" << g_colunas << "x" << g_linhas << ", valor máximo: " << g_maxCinza << ")" << endl;

    cout << "\nSeja bem vindo ao editor de\nimagens da Luthor Tech!" << endl;

    int opMenu;
    do {
        cout << "\n=====Menu Principal=====" << endl;
        cout << "1 - Clarear imagem;" << endl;
        cout << "2 - Escurecer imagem;" << endl;
        cout << "3 - Imagem negativa;" << endl;
        cout << "4 - Binarizar imagem;" << endl;
        cout << "5 - Transformações (Rotação e Espelhamento);" << endl;
        cout << "6 - Iconizar imagem (64x64);" << endl;
        cout << "0 - Sair." << endl;
        cout << "Escolha uma opcão: ";
        cin >> opMenu;

        if (opMenu != 0 && (g_colunas == 0 || g_linhas == 0)) {
            cout << "Nenhuma imagem válida carregada. Não é possivel realizar esta operação." << endl;
            continue;
        }

        char nomeArqSaida[100];
        switch (opMenu) {
            case 1: {
                int fator; cout << "Digite o fator de clareamento: "; cin >> fator;
                clarear(imagemDados, g_colunas, g_linhas, g_maxCinza, fator);
                sprintf(nomeArqSaida, "imgClareada_%s", nomeArqEnt);
                escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                cout << "Imagem clareada salva como '" << nomeArqSaida << "'." << endl;
                break;
            }
            case 2: {
                int fator; cout << "Digite o fator de escurecimento: "; cin >> fator;
                escurecer(imagemDados, g_colunas, g_linhas, g_maxCinza, fator);
                sprintf(nomeArqSaida, "imgEscurecida_%s", nomeArqEnt);
                escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                cout << "Imagem escurecida salva como '" << nomeArqSaida << "'." << endl;
                break;
            }
            case 3: {
                negativa(imagemDados, g_colunas, g_linhas, g_maxCinza);
                sprintf(nomeArqSaida, "imgNegativa_%s", nomeArqEnt);
                escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                cout << "Imagem negativa salva como '" << nomeArqSaida << "'." << endl;
                break;
            }
            case 4: {
                int limiar; cout << "Digite o limiar para binarização (0 a " << g_maxCinza << "): "; cin >> limiar;
                if (limiar < 0 || limiar > g_maxCinza) { cout << "Limiar inválido." << endl; break; }
                binarizar(imagemDados, g_colunas, g_linhas, g_maxCinza, limiar);
                sprintf(nomeArqSaida, "imgBinarizada_%s", nomeArqEnt);
                escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                cout << "Imagem binarizada salva como '" << nomeArqSaida << "'." << endl;
                break;
            }
            case 5: { // Sub-menu de Transformações.
                int opSub;
                do {
                    cout << "\n=====Submenu de Transformações=====" << endl;
                    cout << "1 - Rotação para a Esquerda;" << endl;
                    cout << "2 - Rotação para a Direita;" << endl;
                    cout << "3 - Espelhamento Horizontal;" << endl;
                    cout << "4 - Espelhamento Vertical;" << endl;
                    cout << "0 - Voltar ao Menu Principal." << endl;
                    cout << "Escolha uma opcao: ";
                    cin >> opSub;

                    switch (opSub) {
                        case 1:
                            rotacionarEsquerda();
                            if (g_colunas != 0) {
                                sprintf(nomeArqSaida, "imgRotEsquerda_%s", nomeArqEnt);
                                escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                                cout << "Imagem rotacionada para a esquerda salva como '" << nomeArqSaida << "'." << endl;
                            } else {
                                cerr << "Erro ao rotacionar imagem." << endl;
                            }
                            break;
                        case 2:
                            rotacionarDireita();
                            if (g_colunas != 0) {
                                sprintf(nomeArqSaida, "imgRotDireita_%s", nomeArqEnt);
                                escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                                cout << "Imagem rotacionada para a direita salva como '" << nomeArqSaida << "'." << endl;
                            } else {
                                cerr << "Erro ao rotacionar imagem." << endl;
                            }
                            break;
                        case 3:
                            espelhamentoHorizontal();
                            sprintf(nomeArqSaida, "imgEspHorizontal_%s", nomeArqEnt);
                            escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                            cout << "Imagem espelhada horizontalmente salva como '" << nomeArqSaida << "'." << endl;
                            break;
                        case 4:
                            espelhamentoVertical();
                            sprintf(nomeArqSaida, "imgEspVertical_%s", nomeArqEnt);
                            escreverImg(nomeArqSaida, imagemDados, g_colunas, g_linhas, g_maxCinza);
                            cout << "Imagem espelhada verticalmente salva como '" << nomeArqSaida << "'." << endl;
                            break;
                        case 0:
                            cout << "Retornando ao Menu Principal..." << endl;
                            break;
                        default:
                            cout << "Opcao invalida. Tente novamente." << endl;
                            break;
                    }
                } while (opSub != 0);
                break;
            }
            case 6: {
                sprintf(nomeArqSaida, "imgIconizada_%s", nomeArqEnt);
                iconizar(nomeArqSaida);
                break;
            }
            case 0: cout << "Finalizando o programa... A Luthor Tech agradece <3." << endl; break;
            default: cout << "Opção inválida. Por favor, tente novamente." << endl; break;
        }
    } while (opMenu != 0);

    return 0;
}