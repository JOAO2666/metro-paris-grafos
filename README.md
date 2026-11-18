# Metrô de Paris em C

Trabalho de Algoritmos e Estrutura de Dados (AED) da UNIVASF, com a professora Ana Emília de Melo Queiroz. Entrega e apresentação em 23/11/2026.

## Grupo

* João Emanuel Almeida Ramos
* Nicollas
* Caio Alves
* Marcos Felipe
* Marcos Levi

## O problema

O programa calcula o menor tempo de trajeto entre duas estações do metrô de Paris (`E1` a `E14`), ligadas por quatro linhas:

* Linha 1 (Azul): E1, E2, E3, E4, E5, E6
* Linha 2 (Amarela): E10, E2, E9, E8, E5, E7
* Linha 3 (Vermelha): E11, E9, E3, E13
* Linha 4 (Verde): E12, E8, E4, E13, E14

O trem anda a 30 km/h (`tempo = (km / 30.0) * 60.0`), e cada baldeação soma 4 minutos ao percurso, inclusive na estação final se a linha de destino for diferente da linha de chegada. No A*, o custo real `g` soma os trechos da Tabela 2 com as trocas de linha, e a heurística `h` usa a distância em linha reta da Tabela 1. O teste pedido no roteiro vai de `E6` (Linha Azul) até `E13` (Linha Vermelha).

## Divisão das tarefas

| Integrante | Branch | Arquivos | Responsabilidade |
| :--- | :--- | :--- | :--- |
| João Emanuel | `feat/grafo-joao` | `grafo.h`, `grafo.c` | Struct `Estado`, matrizes de distância, conexões e linhas, funções auxiliares e impressão do caminho. |
| Nicollas | `nicollas` | `astar.h`, `astar.c` | Busca A* (`f = g + h`), ordem de expansão dos nós e caso `E6` Azul para `E13` Vermelha. |
| Caio Alves | `caio-alves` | `dijkstra.h`, `dijkstra.c` | Algoritmo de Dijkstra com tempo de baldeação e reconstrução do trajeto. |
| Marcos Felipe | `marcos-felipe` | `busca_cega.h`, `busca_cega.c` | Busca em largura (BFS), busca em profundidade (DFS) e comparativo entre os algoritmos. |
| Marcos Levi | `marcos-levi` | `interface.h`, `interface.c`, `main.c`, `Makefile` | Menu em `switch/case` (cada `case` chamando uma função), leitura das entradas e `Makefile`. |

## Base em `grafo.h`

Os outros arquivos devem dar `#include "grafo.h"` para usar a struct `Estado` (`estacao`, `linha`, `g`, `h`, `f`, `pai_idx`, `aberto`, `fechado`), as constantes (`NUM_ESTACOES`, `NUM_LINHAS`, `MAX_ESTADOS`, `VELOCIDADE_KMH`, `TEMPO_BALDEACAO_MIN`) e as tabelas `DIST_DIRETA`, `DIST_REAL`, `CONEXAO` e `LINHAS`.

O cabeçalho também declara `nome_linha`, `km_para_minutos`, `indice_estado`, `estacao_tem_linha`, `precisa_baldeacao`, `inicializar_estados` e `imprimir_caminho`. As estações usam índices de `0` a `13` (`E1` a `E14`), e as linhas vão de `1` a `4` (1 Azul, 2 Amarela, 3 Vermelha, 4 Verde), com `0` quando o destino aceitar qualquer linha. Quem implementar os algoritmos precisa alinhar com o Marcos Levi os nomes das funções chamadas no menu do `main.c`.

## Como enviar sua parte

Crie uma branch com o seu nome (`nicollas`, `caio-alves`, `marcos-felipe` ou `marcos-levi`) antes de mexer nos arquivos:

```bash
git clone https://github.com/JOAO2666/metro-paris-grafos.git
cd metro-paris-grafos
git checkout -b seu-nome
```

Edite só os arquivos do seu módulo, faça o commit, suba a branch e abra um Pull Request para a `main`:

```bash
git add seus-arquivos
git commit -m "Implementa minha parte"
git push -u origin seu-nome
```

## Compilação

Depois que todos os arquivos estiverem na `main`:

```bash
gcc -Wall -Wextra -std=c99 -pedantic -O2 main.c grafo.c astar.c dijkstra.c busca_cega.c interface.c -o metro
./metro
```
