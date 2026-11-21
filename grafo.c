#include <stdio.h> 
#include <float.h> /* inclui as constanste de ponto flutuante  usados para acessar DBL_MAX*/
#include "grafo.h" /* aqui traz as constantes Num_Estacoes, Num_Linhas, Max_Estados, velocidade e temp */

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
/*E = estacao e os numeros sao km*/

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
};// 0.0 onde nao há ligação

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
}; /* 1 significa a ligaçãodireta se tem aresta e ligação, zero ausência*/

/* Cores das linhas do metro: 1 = Azul, 2 = Amarela, 3 = Vermelha, 4 = Verde */
const int LINHAS[NUM_ESTACOES][NUM_ESTACOES] = { //declara q é 14x14
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0}, /* Trecho E1–E2 opera na linha 1 (Azul)*/
    {1,0,1,0,0,0,0,0,2,2,0,0,0,0}, /*A partir de E2: E1 (linha 1), E3 (linha 1), E9 (linha 2), E10 (linha 2)*/
    {0,1,0,1,0,0,0,0,3,0,0,0,3,0}, /* A partir de E3: E2 (linha 1), E4 (linha 1), E9 (linha 3), E13 (linha 3). */
    {0,0,1,0,1,0,0,4,0,0,0,0,4,0}, /* A partir de E4: E3 (linha 1), E5 (linha 1), E8 (linha 4), E13 (linha 4). */
    {0,0,0,1,0,1,2,2,0,0,0,0,0,0}, /* A partir de E5: E4 (linha 1), E6 (linha 1), E7 (linha 2), E8 (linha 2). */
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0}, /* A partir de E6: E5 (linha 1 — Azul). */
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0}, /* A partir de E7: E5 (linha 2 — Amarela). */
    {0,0,0,4,2,0,0,0,2,0,0,4,0,0}, /* A partir de E8: E4 (linha 4), E5 (linha 2), E9 (linha 2), E12 (linha 4). */
    {0,2,3,0,0,0,0,2,0,0,3,0,0,0}, /* A partir de E9: E2 (linha 2), E3 (linha 3), E8 (linha 2), E11 (linha 3). */
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0}, /* A partir de E10: E2 (linha 2). */
    {0,0,0,0,0,0,0,0,3,0,0,0,0,0}, /* A partir de E11: E9 (linha 3). */
    {0,0,0,0,0,0,0,4,0,0,0,0,0,0}, /* A partir de E12: E8 (linha 4). */
    {0,0,3,4,0,0,0,0,0,0,0,0,0,4}, /* A partir de E13: E3 (linha 3 — Vermelha), E4 (linha 4), E14 (linha 4). */
    {0,0,0,0,0,0,0,0,0,0,0,0,4,0}  /* A partir de E14: E13 (linha 4). */
}; /* Fecha a inicialização da matriz LINHAS */
/*recebe o código numérico de uma linha cor e devolve uma string cosntate char com o nome dela*/
const char* nome_linha(int cor) {
    switch (cor) { /*se cor for == 1, retorna azul*/
        case 1:  return "Azul"; /*se cor for == 1, retorna azul*/
        case 2:  return "Amarela"; /*se cor for == 2, retorna amarela*/
        case 3:  return "Vermelha"; /*se cor for == 3, retorna vermelho*/
        case 4:  return "Verde"; /*se cor for == 4, retorna verde*/
        default: return "Nenhuma"; /*se cor for == 0, retorna nenhuma*/
    }
} /*Dé a maior constante do tipo doubleBL MAX possivel no computador*/

/* A 30 km/h, o trem percorre 0.5 km por minuto: tempo = km / 0.5 = km * 2 */
double km_para_minutos(double km) { /* defina a funcao que converte uma distancia km para minutos*/
    return (km / VELOCIDADE_KMH) * 60.0;
} /*baldeacao_Min é o tempo extra em minutos gasto ao trocar de linha na mesma estacao*/
/*double de dupla precisao de casas decimais*/
int indice_estado(int estacao, int linha) {
    return estacao * NUM_LINHAS + linha; /* calcula a posicao linear no vetor de estados mul estacao por 5 Num linhas e somando linhas*/
} /* const significa que ninguem pode alterar os valores dessas tabelas por acidente*/

bool estacao_tem_linha(int estacao, int linha) {
    for (int j = 0; j < NUM_ESTACOES; j++) { /* percora todas as colunas de j ( 0 a 13) da linha estacao na matriz*/
        if (LINHAS[estacao][j] == linha) { /*verifica se  existe algum trecho saindo de estacao que usa exatamente aquela */
            return true; /* se nenhuma ligação dessa linha partir da estacao, retorna false*/
        }
    }
    return false;
}

bool precisa_baldeacao(int linha_atual, int nova_linha) {
    return (linha_atual != 0 && nova_linha != 0 && linha_atual != nova_linha);
} // Define a função booleana que detecta se houve troca de linha (baldeação).
/*retorna true apenas se ambas as linhas forem diferentes de 0, válidas e direntes entre si, caso contrário retorna false*/
void inicializar_estados(Estado estados[MAX_ESTADOS]) {/*defina a funcao q prepara/reinicia todo o vetor de 70 estaods antes de rodar um algoritmo de busca*/
    for (int e = 0; e < NUM_ESTACOES; e++) { /*percorre todas as 14 esstaçoes de 0 a 13*/
        for (int l = 0; l < NUM_LINHAS; l++) { /*percorre todas as linhas de 0 a 4 */
            int idx = indice_estado(e, l);
            estados[idx].estacao = e; /* grava o nuémro da estacao no estado*/
            estados[idx].linha = l; /* grava o número da linha no estado*/
            estados[idx].g = DBL_MAX; /*inicializa o custo acumulado em g com infinito*/
            estados[idx].h = 0.0; /* inicializa a heurística h com 0.0*/
            estados[idx].f = DBL_MAX; /*inicializa o custo total em f com infinito*/
            estados[idx].pai_idx = -1; /* para indiciar que o estado ainda nao tem pai na arvore*/
            estados[idx].aberto = false; /* Marca que o estado ainda não foi fechado (expandido/visitado).*/
            estados[idx].fechado = false; /* marcadores de controle de busca true ou false*/
        } /*fazer o papel de "infinito" no começo da busca. Como ainda não calculamos o tempo de viagem até aquele estado, colocamos DBL_MAX para 
        garantir que qualquer caminho real encontrado seja menor que ele e seja aceito*/
    }/*g = tempo acumulad em minutos desde a origem*/
/*Max_Estad0s 14x5 = 70 total de combinações*/
/*h estimatica de tempo até o destino usando a distância em linha reta em minutos*/
/*f = soma g + h usada  em A* */
/*pai_idx indidica o e tado anterior de onde viemos -1 quado é início*/
/*index é indice( posicao 0 até 69)*/
/* l representa a variação de 0 a 4*/
/* descobertos que ainda serão avaliados ficam abertos (na fronteira). Quando escolhemos um estado, olhamos seus vizinhos
 e concluímos a análise dele, ele vira fechado (já expandido/visitado),*/
/* par é estação combinada com linha*/
}

void imprimir_caminho(const Estado estados[MAX_ESTADOS], int idx_objetivo,
                      int est_orig, int linha_orig, int est_dest, int linha_dest,/*Recebe a estação e a linha de origem, além da estação e da linha de destino*/
                      int nos_expandidos, const char *nome_algoritmo) {/* Recebe quantos nós foram expandidos e o nome do algoritmo (ex.: "A*"*/
   /*Declara a função que imprime o trajeto final; recebe o vetor de 70 estados (apenas leitura com const)
    e o índice do estado final encontrado (idx_objetivo).*/
                        if (idx_objetivo == -1) { /*significa que nenhum caminho até o destino foi encontrado.*/
        printf("\nNao ha caminho viavel entre E%d e E%d.\n", est_orig + 1, est_dest + 1);
        return;
    }

    int caminho[MAX_ESTADOS]; /*Cria um vetor para guardar os índices dos estados que compõem o caminho encontrado.*/
    int tam = 0; /* Guarda quantos estados há no caminho (0 inicialmente).*/
    for (int curr = idx_objetivo; curr != -1; curr = estados[curr].pai_idx) { /*Salva o estado atual curr no vetor caminho e aumenta tam em 1.*/
        caminho[tam++] = curr; /*Salva o estado atual curr no vetor caminho e aumenta tam em 1*/
    }

    printf("\n=== MELHOR TRAJETO (%s) ===\n", nome_algoritmo);
    printf("Origem : E%d (Linha %s)\n", est_orig + 1, nome_linha(linha_orig));
    if (linha_dest > 0) {
        printf("Destino: E%d (Linha %s)\n", est_dest + 1, nome_linha(linha_dest));
    } else {
        printf("Destino: E%d\n", est_dest + 1);
    }
    printf("Nos expandidos: %d\n\n", nos_expandidos);

    int total_baldeacoes = 0; /*Contador de quantas vezes o usuário trocou de linha.*/
    for (int i = tam - 1; i >= 0; i--) { /*Como caminho foi salvo do fim para o início, esse for lê de trás para frente 
        (tam - 1 até 0) para imprimir do início até o destino.*/
        Estado e = estados[caminho[i]]; /*Pega os dados do estado atual do passo i*/
        if (i == tam - 1) { /* Verifica se este é o primeiro passo do trajeto (o início fica no fim do vetor caminho). */
            printf("  [Inicio]  E%-2d | Linha %-8s | Custo acumulado: %5.2f min\n",
                   e.estacao + 1, nome_linha(e.linha), e.g); /* Imprime a estação inicial (E1 a E14), o nome da linha e o custo acumulado inicial. */
        } else { /* Caso contrário, trata os passos seguintes do trajeto. */
            Estado ant = estados[caminho[i + 1]]; /* Pega o estado do passo imediatamente anterior no trajeto. */
            bool trocou = precisa_baldeacao(ant.linha, e.linha); /* Verifica se houve mudança de linha entre o estado anterior e o atual. */
            if (ant.estacao == e.estacao) { /* Se permaneceu na mesma estação, esse passo representa uma baldeação de linha no local. */
                total_baldeacoes++; /* Incrementa o contador total de baldeações. */
                printf("  [Baldeacao em E%-2d] Linha %-8s -> Linha %-8s | Custo acumulado: %5.2f min (+%.2f min)\n",
                       e.estacao + 1, nome_linha(ant.linha), nome_linha(e.linha),
                       e.g, TEMPO_BALDEACAO_MIN); /* Imprime a troca de linha na mesma estação, o custo acumulado e o tempo adicional da baldeação. */
            } else { /* Caso tenha avançado para uma estação diferente (deslocamento entre estações). */
                printf("  -> E%-2d | Linha %-8s | Custo acumulado: %5.2f min",
                       e.estacao + 1, nome_linha(e.linha), e.g); /* Imprime a estação de destino do passo, a linha usada e o custo acumulado. */
                if (trocou) { /* Se houve troca de linha ao partir da estação anterior: */
                    total_baldeacoes++; /* Incrementa o contador total de baldeações. */
                    printf("  [Baldeacao em E%d: +%.2f min]", ant.estacao + 1, TEMPO_BALDEACAO_MIN); /* Imprime na mesma linha o aviso da baldeação na estação anterior e o tempo somado. */
                }
                printf("\n"); /* Finaliza a linha de saída deste passo. */
            }
        }
    }

    printf("\nTotal de baldeacoes: %d\n", total_baldeacoes);
    printf("Tempo total estimado: %.2f minutos\n", estados[idx_objetivo].g);
}
