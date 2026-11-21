#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

#define NUM_ESTACOES 14
#define NUM_LINHAS   5   /* 0: sem linha / 1: Azul, 2: Amarela, 3: Vermelha, 4: Verde */
#define MAX_ESTADOS  (NUM_ESTACOES * NUM_LINHAS) /*defina o total maximoestados que o grafo tera de  14 x 5 = 70*/

#define VELOCIDADE_KMH      30.0 /*km*/
#define TEMPO_BALDEACAO_MIN 4.0 /* tempo extra de troca de linha*/

/* Estrutura que representa o estado de uma busca no grafo */
typedef struct { /*defina as variaveis que o estado tera de armazeanr, ex:*/
    int estacao;   /* Indice de 0 a 13 (E1 a E14) */
    int linha;     /* Linha atual (1 a 4) */
    double g;      /* Custo acumulado em minutos */
    double h;      /* Heuristica estimada ate o destino em minutos */
    double f;      /* f = g + h */
    int pai_idx;   /* Indice do estado predecessor na arvore de busca (-1 se raiz) */
    bool aberto;   /* Presente na fronteira de busca */
    bool fechado;  /* Ja expandido / visitado */
} Estado;

/* Tabelas oficiais do problema */ /*omentário agrupando as matrizes de dados do mapa.*/
extern const double DIST_DIRETA[NUM_ESTACOES][NUM_ESTACOES]; /*Declara (sem alocar aqui) a matriz 14x14 constante de distâncias em linha reta*/
extern const double DIST_REAL[NUM_ESTACOES][NUM_ESTACOES]; /*Declara a matriz 14x14 constante de distâncias reais dos trilhos (Tabela 2)*/
extern const int CONEXAO[NUM_ESTACOES][NUM_ESTACOES]; /*constante adjacente se há ligação direta  1 ou caso contráio 0*/
extern const int LINHAS[NUM_ESTACOES][NUM_ESTACOES];

/* Funcoes utilitarias */
const char* nome_linha(int cor); /*converter nome da linha em texto, azul,vermelho e verde e etc*/
double km_para_minutos(double km); /*converte distancia para minuto*/
int indice_estado(int estacao, int linha); /*converte ar estacao em índice único*/
bool estacao_tem_linha(int estacao, int linha);
bool precisa_baldeacao(int linha_atual, int nova_linha);/*verifica se há troca de linha*/

/* Inicializa o vetor de estados */
void inicializar_estados(Estado estados[MAX_ESTADOS]);/*reinicia todos os estados*/

/* Reconstrucao e impressao do trajeto */
void imprimir_caminho(const Estado estados[MAX_ESTADOS], int idx_objetivo,
                      int est_orig, int linha_orig, int est_dest, int linha_dest,
                      int nos_expandidos, const char *nome_algoritmo);

#endif /* encerra o bloco iniciado por #infnedef GRAFO_H no topo do arquivo*/
