#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // Declaração do tabuleiro 10x10 e inicialização com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Navio horizontal
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    if (coluna_horizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_horizontal][coluna_horizontal + i] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_horizontal][coluna_horizontal + i] = NAVIO;
            }
        } else {
            printf("Erro: navio horizontal sobreposto.\n");
            return 1;
        }
    } else {
        printf("Erro: navio horizontal fora dos limites.\n");
        return 1;
    }

    // Navio vertical
    int linha_vertical = 5;
    int coluna_vertical = 7;

    if (linha_vertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_vertical + i][coluna_vertical] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_vertical + i][coluna_vertical] = NAVIO;
            }
        } else {
            printf("Erro: navio vertical sobreposto.\n");
            return 1;
        }
    } else {
        printf("Erro: navio vertical fora dos limites.\n");
        return 1;
    }

    // Navio diagonal principal (↘)
    int linha_diag1 = 0;
    int coluna_diag1 = 0;

    if (linha_diag1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        coluna_diag1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_diag1 + i][coluna_diag1 + i] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_diag1 + i][coluna_diag1 + i] = NAVIO;
            }
        } else {
            printf("Erro: navio diagonal principal sobreposto.\n");
            return 1;
        }
    } else {
        printf("Erro: navio diagonal principal fora dos limites.\n");
        return 1;
    }

    // Navio diagonal secundária (↙)
    int linha_diag2 = 0;
    int coluna_diag2 = 9;

    if (linha_diag2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        coluna_diag2 - TAMANHO_NAVIO + 1 >= 0) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_diag2 + i][coluna_diag2 - i] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_diag2 + i][coluna_diag2 - i] = NAVIO;
            }
        } else {
            printf("Erro: navio diagonal secundária sobreposto.\n");
            return 1;
        }
    } else {
        printf("Erro: navio diagonal secundária fora dos limites.\n");
        return 1;
    }

    //EXIBIÇÃO DO TABULEIRO

    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}