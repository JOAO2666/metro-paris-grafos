# Metrô de Paris em C

Trabalho prático da disciplina Algoritmos e Estrutura de Dados (AED), na UNIVASF, com a professora Ana Emília de Melo Queiroz. A entrega e a apresentação ficam para 23/11/2026.

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

Os cálculos seguem estas regras:

1. Velocidade média do trem de 30 km/h (0,5 km/min), então o tempo em minutos vale `distancia * 2`, calculado por `(km / 30.0) * 60.0`.
2. Cada baldeação acrescenta 4 minutos ao tempo total, inclusive na estação final se a linha escolhida para o destino for diferente da linha de chegada.
3. O custo real `g` soma os trechos percorridos na Tabela 2 e as baldeações.
4. A heurística `h` do A* usa as distâncias em linha reta da Tabela 1 convertidas para minutos.
5. O caso principal do roteiro sai de `E6` (Linha Azul) até `E13` (Linha Vermelha).

## O que já está pronto

Os arquivos do módulo do grafo (`grafo.h` e `grafo.c`), feitos por João Emanuel, já estão prontos na branch `main`.

Todos os outros arquivos (`astar.h`, `astar.c`, `dijkstra.h`, `dijkstra.c`, `busca_cega.h`, `busca_cega.c`, `interface.h`, `interface.c`, `main.c` e `Makefile`) estão vazios de propósito. Cada integrante precisa escrever o código da sua parte dentro dos próprios arquivos e enviar por branch separada.

## Divisão das tarefas

| Integrante | Branch | Arquivos | O que implementar |
| :--- | :--- | :--- | :--- |
| João Emanuel | `feat/grafo-joao` (código já na `main`) | `grafo.h`, `grafo.c` | Struct `Estado`, constantes, matrizes (`DIST_DIRETA`, `DIST_REAL`, `CONEXAO`, `LINHAS`), funções de tempo e baldeação e impressão do trajeto. |
| Nicollas | `nicollas` | `astar.h`, `astar.c` | Busca informada A* (`f = g + h`), exibição da ordem de expansão dos nós e execução do caso `E6` Azul para `E13` Vermelha. |
| Caio Alves | `caio-alves` | `dijkstra.h`, `dijkstra.c` | Algoritmo de Dijkstra considerando o custo acumulado `g`, +4 min por baldeação e reconstrução do menor caminho. |
| Marcos Felipe | `marcos-felipe` | `busca_cega.h`, `busca_cega.c` | Busca em Largura (BFS) e Busca em Profundidade (DFS) sobre `CONEXAO`, junto com o comparativo de nós expandidos e tempo entre os algoritmos. |
| Marcos Levi | `marcos-levi` | `interface.h`, `interface.c`, `main.c`, `Makefile` | Menu no terminal em `switch/case` apenas chamando funções, leitura validada de estações/linhas e `Makefile` do projeto. |

## O que usar de `grafo.h`

Os módulos de busca e interface devem dar `#include "grafo.h"` para compartilhar os dados e funções já implementados:

* Constantes: `NUM_ESTACOES` (14), `NUM_LINHAS` (5), `MAX_ESTADOS` (70), `VELOCIDADE_KMH` (30.0) e `TEMPO_BALDEACAO_MIN` (4.0).
* Struct `Estado`: campos `estacao`, `linha`, `g`, `h`, `f`, `pai_idx`, `aberto` e `fechado`.
* Tabelas: `DIST_DIRETA`, `DIST_REAL`, `CONEXAO` e `LINHAS`.
* Funções: `nome_linha`, `km_para_minutos`, `indice_estado`, `estacao_tem_linha`, `precisa_baldeacao`, `inicializar_estados` e `imprimir_caminho`.

As estações usam índices de `0` a `13` (`E1` a `E14`). As linhas vão de `1` a `4` (1 Azul, 2 Amarela, 3 Vermelha, 4 Verde), e `0` indica que qualquer linha serve no destino. Quem for implementar `astar.h`, `dijkstra.h` e `busca_cega.h` precisa combinar com o Marcos Levi os nomes das funções públicas que serão chamadas no menu do `main.c`.

## Critérios da disciplina

Para evitar desconto na nota da professora Ana Emília:

1. Manter protótipos e structs nos arquivos `.h` e as implementações nos arquivos `.c`.
2. Passar dados por parâmetros nas funções.
3. No `main.c`, deixar cada `case` do `switch` chamando uma função só, sem lógica solta dentro do `switch`.
4. Apagar qualquer código comentado antes de mandar a versão final.
5. Escrever em C99 padrão para compilar no GCC sem erros nem avisos (não usar `<conio.h>` nem funções do Turbo C).

## Como criar sua branch e enviar o código

Antes de mexer em qualquer arquivo, baixe a `main` atualizada e crie uma branch com o seu nome:

```bash
git clone https://github.com/JOAO2666/metro-paris-grafos.git
cd metro-paris-grafos
git checkout main
git pull origin main
git checkout -b seu-nome
```

Nomes sugeridos para cada pessoa:

```bash
git checkout -b nicollas
git checkout -b caio-alves
git checkout -b marcos-felipe
git checkout -b marcos-levi
```

Edite apenas os arquivos da sua parte, faça o commit, suba a branch e abra um Pull Request para a `main`:

```bash
git add seus-arquivos
git commit -m "Implementa modulo da minha parte"
git push -u origin seu-nome
```

## Compilação

Para testar só o módulo do grafo já pronto:

```bash
gcc -Wall -Wextra -std=c99 -pedantic -c grafo.c
```

Quando todos os arquivos estiverem preenchidos e integrados na `main`:

```bash
gcc -Wall -Wextra -std=c99 -pedantic -O2 main.c grafo.c astar.c dijkstra.c busca_cega.c interface.c -o metro
./metro
```
