#include <stdio.h>
#include <float.h>
#include "grafo.h"

/* Tabela 1: Distancias diretas em linha reta entre as estacoes (km) */
const double DIST_DIRETA[NUM_ESTACOES][NUM_ESTACOES] = {
    /* E1   E2    E3    E4    E5    E6    E7    E8    E9   E10   E11   E12   E13   E14 */
    { 0.0, 10.0, 18.5, 24.8, 36.4, 38.8, 35.8, 25.4, 17.6,  9.1, 16.7, 27.3, 27.6, 29.8}, /* E1  */
    {10.0,  0.0,  8.5, 14.8, 26.6, 29.1, 26.1, 17.3, 10.0,  3.5, 15.5, 20.9, 19.1, 21.8}, /* E2  */
    {18.5,  8.5,  0.0,  6.3, 18.2, 20.6, 17.6, 13.6,  9.4, 10.3, 19.5, 19.1, 12.1, 16.6}, /* E3  */
    {24.8, 14.8,  6.3,  0.0, 12.0, 14.4, 11.5, 12.4, 12.6, 16.7, 23.6, 18.6, 10.6, 15.4}, /* E4  */
    {36.4, 26.6, 18.2, 12.0,  0.0,  3.0,  2.4, 19.4, 23.3, 28.2, 34.2, 24.8, 14.5, 17.9}, /* E5  */
    {38.8, 29.1, 20.6, 14.4,  3.0,  0.0,  3.3, 22.3, 25.7, 30.3, 36.7, 27.6, 15.2, 18.2}, /* E6  */
    {35.8, 26.1, 17.6, 11.5,  2.4,  3.3,  0.0, 20.0, 23.0, 27.3, 34.2, 25.7, 12.4, 15.6}, /* E7  */
    {25.4, 17.3, 13.6, 12.4, 19.4, 22.3, 20.0,  0.0,  8.2, 20.3, 16.1,  6.4, 22.7, 27.6}, /* E8  */
    {17.6, 10.0,  9.4, 12.6, 23.3, 25.7, 23.0,  8.2,  0.0, 13.5, 11.2, 10.9, 21.2, 26.6}, /* E9  */
    { 9.1,  3.5, 10.3, 16.7, 28.2, 30.3, 27.3, 20.3, 13.5,  0.0, 17.6, 24.2, 18.7, 21.2}, /* E10 */
    {16.7, 15.5, 19.5, 23.6, 34.2, 36.7, 34.2, 16.1, 11.2, 17.6,  0.0, 14.2, 31.5, 35.5}, /* E11 */
    {27.3, 20.9, 19.1, 18.6, 24.8, 27.6, 25.7,  6.4, 10.9, 24.2, 14.2,  0.0, 28.8, 33.6}, /* E12 */
    {27.6, 19.1, 12.1, 10.6, 14.5, 15.2, 12.4, 22.7, 21.2, 18.7, 31.5, 28.8,  0.0,  5.1}, /* E13 */
    {29.8, 21.8, 16.6, 15.4, 17.9, 18.2, 15.6, 27.6, 26.6, 21.2, 35.5, 33.6,  5.1,  0.0}  /* E14 */
};

/* Tabela 2: Distancias reais entre estacoes com ligacao fisica direta (km) */
const double DIST_REAL[NUM_ESTACOES][NUM_ESTACOES] = {
    /* E1   E2    E3    E4    E5   E6   E7    E8    E9  E10   E11  E12   E13  E14 */
    { 0.0, 10.0,  0.0,  0.0,  0.0, 0.0, 0.0,  0.0,  0.0, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E1  */
    {10.0,  0.0,  8.5,  0.0,  0.0, 0.0, 0.0,  0.0, 10.0, 3.5,  0.0, 0.0,  0.0, 0.0}, /* E2  */
    { 0.0,  8.5,  0.0,  6.3,  0.0, 0.0, 0.0,  0.0,  9.4, 0.0,  0.0, 0.0, 18.7, 0.0}, /* E3  */
    { 0.0,  0.0,  6.3,  0.0, 13.0, 0.0, 0.0, 15.3,  0.0, 0.0,  0.0, 0.0, 12.8, 0.0}, /* E4  */
    { 0.0,  0.0,  0.0, 13.0,  0.0, 3.0, 2.4, 30.0,  0.0, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E5  */
    { 0.0,  0.0,  0.0,  0.0,  3.0, 0.0, 0.0,  0.0,  0.0, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E6  */
    { 0.0,  0.0,  0.0,  0.0,  2.4, 0.0, 0.0,  0.0,  0.0, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E7  */
    { 0.0,  0.0,  0.0, 15.3, 30.0, 0.0, 0.0,  0.0,  9.6, 0.0,  0.0, 6.4,  0.0, 0.0}, /* E8  */
    { 0.0, 10.0,  9.4,  0.0,  0.0, 0.0, 0.0,  9.6,  0.0, 0.0, 12.2, 0.0,  0.0, 0.0}, /* E9  */
    { 0.0,  3.5,  0.0,  0.0,  0.0, 0.0, 0.0,  0.0,  0.0, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E10 */
    { 0.0,  0.0,  0.0,  0.0,  0.0, 0.0, 0.0,  0.0, 12.2, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E11 */
    { 0.0,  0.0,  0.0,  0.0,  0.0, 0.0, 0.0,  6.4,  0.0, 0.0,  0.0, 0.0,  0.0, 0.0}, /* E12 */
    { 0.0,  0.0, 18.7, 12.8,  0.0, 0.0, 0.0,  0.0,  0.0, 0.0,  0.0, 0.0,  0.0, 5.1}, /* E13 */
    { 0.0,  0.0,  0.0,  0.0,  0.0, 0.0, 0.0,  0.0,  0.0, 0.0,  0.0, 0.0,  5.1, 0.0}  /* E14 */
};

/* Matriz de adjacencia binaria: 1 indica ligacao direta entre as estacoes */
const int CONEXAO[NUM_ESTACOES][NUM_ESTACOES] = {
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0}, /* E1  */
    {1,0,1,0,0,0,0,0,1,1,0,0,0,0}, /* E2  */
    {0,1,0,1,0,0,0,0,1,0,0,0,1,0}, /* E3  */
    {0,0,1,0,1,0,0,1,0,0,0,0,1,0}, /* E4  */
    {0,0,0,1,0,1,1,1,0,0,0,0,0,0}, /* E5  */
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0}, /* E6  */
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0}, /* E7  */
    {0,0,0,1,1,0,0,0,1,0,0,1,0,0}, /* E8  */
    {0,1,1,0,0,0,0,1,0,0,1,0,0,0}, /* E9  */
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0}, /* E10 */
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0}, /* E11 */
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0}, /* E12 */
    {0,0,1,1,0,0,0,0,0,0,0,0,0,1}, /* E13 */
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0}  /* E14 */
};

/* Cores das linhas do metro: 1 = Azul, 2 = Amarela, 3 = Vermelha, 4 = Verde */
const int LINHAS[NUM_ESTACOES][NUM_ESTACOES] = {
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,0,0,0,0,0,2,2,0,0,0,0},
    {0,1,0,1,0,0,0,0,3,0,0,0,3,0},
    {0,0,1,0,1,0,0,4,0,0,0,0,4,0},
    {0,0,0,1,0,1,2,2,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0},
    {0,0,0,4,2,0,0,0,2,0,0,4,0,0},
    {0,2,3,0,0,0,0,2,0,0,3,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,3,0,0,0,0,0},
    {0,0,0,0,0,0,0,4,0,0,0,0,0,0},
    {0,0,3,4,0,0,0,0,0,0,0,0,0,4},
    {0,0,0,0,0,0,0,0,0,0,0,0,4,0}
};

const char* nome_linha(int cor) {
    switch (cor) {
        case 1:  return "Azul";
        case 2:  return "Amarela";
        case 3:  return "Vermelha";
        case 4:  return "Verde";
        default: return "Nenhuma";
    }
}

/* A 30 km/h, o trem percorre 0.5 km por minuto: tempo = km / 0.5 = km * 2 */
double km_para_minutos(double km) {
    return (km / VELOCIDADE_KMH) * 60.0;
}

int indice_estado(int estacao, int linha) {
    return estacao * NUM_LINHAS + linha;
}

bool estacao_tem_linha(int estacao, int linha) {
    for (int j = 0; j < NUM_ESTACOES; j++) {
        if (LINHAS[estacao][j] == linha) {
            return true;
        }
    }
    return false;
}

bool precisa_baldeacao(int linha_atual, int nova_linha) {
    return (linha_atual != 0 && nova_linha != 0 && linha_atual != nova_linha);
}

void inicializar_estados(Estado estados[MAX_ESTADOS]) {
    for (int e = 0; e < NUM_ESTACOES; e++) {
        for (int l = 0; l < NUM_LINHAS; l++) {
            int idx = indice_estado(e, l);
            estados[idx].estacao = e;
            estados[idx].linha = l;
            estados[idx].g = DBL_MAX;
            estados[idx].h = 0.0;
            estados[idx].f = DBL_MAX;
            estados[idx].pai_idx = -1;
            estados[idx].aberto = false;
            estados[idx].fechado = false;
        }
    }
}

void imprimir_caminho(const Estado estados[MAX_ESTADOS], int idx_objetivo,
                      int est_orig, int linha_orig, int est_dest, int linha_dest,
                      int nos_expandidos, const char *nome_algoritmo) {
    if (idx_objetivo == -1) {
        printf("\nNao ha caminho viavel entre E%d e E%d.\n", est_orig + 1, est_dest + 1);
        return;
    }

    int caminho[MAX_ESTADOS];
    int tam = 0;
    for (int curr = idx_objetivo; curr != -1; curr = estados[curr].pai_idx) {
        caminho[tam++] = curr;
    }

    printf("\n=== MELHOR TRAJETO (%s) ===\n", nome_algoritmo);
    printf("Origem : E%d (Linha %s)\n", est_orig + 1, nome_linha(linha_orig));
    if (linha_dest > 0) {
        printf("Destino: E%d (Linha %s)\n", est_dest + 1, nome_linha(linha_dest));
    } else {
        printf("Destino: E%d\n", est_dest + 1);
    }
    printf("Nos expandidos: %d\n\n", nos_expandidos);

    int total_baldeacoes = 0;
    for (int i = tam - 1; i >= 0; i--) {
        Estado e = estados[caminho[i]];
        if (i == tam - 1) {
            printf("  [Inicio]  E%-2d | Linha %-8s | Custo acumulado: %5.2f min\n",
                   e.estacao + 1, nome_linha(e.linha), e.g);
        } else {
            Estado ant = estados[caminho[i + 1]];
            bool trocou = precisa_baldeacao(ant.linha, e.linha);
            if (ant.estacao == e.estacao) {
                total_baldeacoes++;
                printf("  [Baldeacao em E%-2d] Linha %-8s -> Linha %-8s | Custo acumulado: %5.2f min (+%.2f min)\n",
                       e.estacao + 1, nome_linha(ant.linha), nome_linha(e.linha),
                       e.g, TEMPO_BALDEACAO_MIN);
            } else {
                printf("  -> E%-2d | Linha %-8s | Custo acumulado: %5.2f min",
                       e.estacao + 1, nome_linha(e.linha), e.g);
                if (trocou) {
                    total_baldeacoes++;
                    printf("  [Baldeacao em E%d: +%.2f min]", ant.estacao + 1, TEMPO_BALDEACAO_MIN);
                }
                printf("\n");
            }
        }
    }

    printf("\nTotal de baldeacoes: %d\n", total_baldeacoes);
    printf("Tempo total estimado: %.2f minutos\n", estados[idx_objetivo].g);
}
