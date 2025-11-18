#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            tabuleiro[i][j] = AGUA;
}

void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[2][4 + i] = NAVIO;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[5 + i][7] = NAVIO;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[0 + i][0 + i] = NAVIO;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[0 + i][9 - i] = NAVIO;
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], const char* titulo) {
    printf("\n%s\n\n", titulo);
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para aplicar habilidade Cone
void aplicarCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int origem_linha, int origem_coluna) {
    // A forma do cone é um triângulo invertido com vértice no topo da matriz (linha 0, coluna 2)
    // A base se expande lateralmente até a linha 2, formando 9 células afetadas
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Verifica se a célula está dentro da área triangular
            if (j >= 2 - i && j <= 2 + i && i < 3) {
                int linha = origem_linha + i;
                int coluna = origem_coluna + j - 2;
                // Aplica a habilidade se estiver dentro dos limites e não for navio
                if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
                    coluna >= 0 && coluna < TAMANHO_TABULEIRO &&
                    tabuleiro[linha][coluna] != NAVIO) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para aplicar habilidade Cruz
void aplicarCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int origem_linha, int origem_coluna) {
    // A cruz é formada por uma linha vertical e uma horizontal cruzando o centro da matriz (2,2)
    // São afetadas as células da linha e coluna centrais, exceto o centro que é marcado separadamente
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Verifica se está na linha ou coluna central, mas não no centro
            if ((i == 2 || j == 2) && !(i == 2 && j == 2)) {
                int linha = origem_linha + i - 2;
                int coluna = origem_coluna + j - 2;
                // Aplica a habilidade se estiver dentro dos limites e não for navio
                if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
                    coluna >= 0 && coluna < TAMANHO_TABULEIRO &&
                    tabuleiro[linha][coluna] != NAVIO) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
    // Marca o centro da cruz
    if (tabuleiro[origem_linha][origem_coluna] != NAVIO)
        tabuleiro[origem_linha][origem_coluna] = HABILIDADE;
}

// Função para aplicar habilidade Octaedro
void aplicarOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int origem_linha, int origem_coluna) {
    // O octaedro é representado como um losango simétrico (vista frontal)
    // A lógica usa a soma das distâncias absolutas até o centro (2,2) da matriz
    // São afetadas células com distância <= 1 ou distância 2 nas linhas ou colunas centrais
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int distancia = abs(2 - i) + abs(2 - j);
            if (distancia <= 1 || (distancia == 2 && (i == 2 || j == 2))) {
                int linha = origem_linha + i - 2;
                int coluna = origem_coluna + j - 2;
                // Aplica a habilidade se estiver dentro dos limites e não for navio
                if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
                    coluna >= 0 && coluna < TAMANHO_TABULEIRO &&
                    tabuleiro[linha][coluna] != NAVIO) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Cone
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    aplicarCone(tabuleiro, 3, 4);
    exibirTabuleiro(tabuleiro, "Área de efeito: Cone");

    // Cruz
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    aplicarCruz(tabuleiro, 6, 2);
    exibirTabuleiro(tabuleiro, "Área de efeito: Cruz");

    // Octaedro
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    aplicarOctaedro(tabuleiro, 5, 5);
    exibirTabuleiro(tabuleiro, "Área de efeito: Octaedro");

    return 0;
}