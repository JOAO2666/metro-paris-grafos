# Metrô de Paris — Algoritmos em Grafos (C)

Projeto da disciplina **Algoritmos e Estrutura de Dados (AED)** — UNIVASF (Profa. Ana Emília de Melo Queiroz).  
**Entrega / Apresentação:** 23/11/2026

## Sobre o Projeto
Sistema em C para encontrar o trajeto mais rápido entre duas estações do Metrô de Paris (`E1` a `E14`, distribuídas em 4 linhas), considerando velocidade média do trem de **30 km/h** e tempo de **4 minutos** por baldeação. O programa compara os algoritmos:
- **Busca Cega** (BFS/DFS)
- **Busca Informada A\*** (`f = g + h`, usando a tabela de distâncias em linha reta)
- **Algoritmo de Dijkstra**

## Divisão da Equipe (5 Integrantes)

| Integrante | Arquivos / Módulo | Responsabilidade |
| :--- | :--- | :--- |
| **João Emanuel** *(ou ajustar conforme escolha)* | `grafo.h` / `grafo.c` | Struct do grafo, matrizes de distâncias e linhas (`1`–`4`), cálculo de tempo e baldeação |
| **Integrante 2** | `dijkstra.h` / `dijkstra.c` | Algoritmo de Dijkstra considerando troca de linha e reconstrução do trajeto |
| **Integrante 3** | `astar.h` / `astar.c` | Algoritmo A\* (`f = g + h`) e registro da árvore/ordem de busca |
| **Integrante 4** | `busca_cega.h` / `busca_cega.c` | Busca Cega (BFS/DFS), comparativo entre os 3 algoritmos e testes |
| **Integrante 5** | `main.c`, `interface.h/.c`, `Makefile` | Menu interativo, painel visual do mapa no terminal e compilação |

## Fluxo de Trabalho no GitHub
1. Aceite o convite de colaborador no repositório.
2. Clone o projeto e crie a sua branch com seu módulo e nome:
   ```bash
   git checkout -b feat/sua-parte-seu-nome
