# 🛩 Problema do Caixeiro Viajante
Trabalho avaliativo para a disciplina de Algoritmos e Estruturas de Dados III do curso de Ciência da Computação da Universidade Federal de Pelotas - RS.

## 📖 Sobre
O Problema do Caixeiro Viajante (PCV), também conhecido como Travelling Salesman Problem (TSP) é um problema de otimização combinatória clássico da computação e matemática. Seu é obter um ciclo hamiltoniano de custo total mínimo a partir de um ponto inicial.
Neste trabalho, o objetivo é trabalhar com um subcaso do TSP, chamado Caixeiro Viajante Métrico, no qual os custos das arestas satisfazem a desigualdade triangular, isto é, dado um grafo completo – há uma aresta para todo par de vértices – no qual cada aresta contém um custo associado, para quaisquer três vértices A, B e C, se existirem os caminhos A–B e A–B–C, o caminho de menor custo sempre será o mais direto, ou seja, A–B.
O objetivo deste trabalho é fazer um comparativo na aplicação dos algoritmos de força bruta e aproximativo no problema apresentado. 

## 🔎 Casos de Estudo
Foi disponibilizado cinco matrizes adjacentes para cinco grafos diferentes para serem utilizadas como casos de estudo, as quais possuem tamanhos e valores diferentes, com o custo da distância mínima sendo conhecido.
- Matriz 1 (tsp1): 11x11 - custo do caminho mínimo: 253
- Matriz 2 (tsp2): 6x6 - custo do caminho mínimo: 1.248
- Matriz 3 (tsp3): 15x15 - custo do caminho mínimo: 1.194
- Matriz 4 (tsp4): 44x44 - custo do caminho mínimo: 7.013
- Matriz 5 (tsp5): 29x29 - custo do caminho mínimo: 27.603

## ⌨ Códigos
### Força Bruta
Código de ![Junior Garcia](https://github.com/garciajunior/Trabalho-Final-COM111), baseado no ![Trabalho de Conclusão de Curso](https://docplayer.com.br/7645549-Problema-do-caixeiro-viajante-aplicado-ao-roteamento-de-veiculos-numa-malha-viaria-jose-luiz-machado-morais.html) de José Luiz Machado Morais.
- ```forca-bruta-original.c``` - código de Junior Garcia;
- ```forca-bruta.c``` - código adaptado;
- ```forca-bruta-tempo.c``` - código anterior com medicação de tempo;
- ```forca-bruta-simples.c``` - código sem persistência de dados (há diferença de tempos de execução deste para o forca-bruta.c).

### Aproximativo
Implementação baseada no código de ![Arthur Cerveira](https://github.com/arthurcerveira/Travelling-Salesman-Problem).

## 🗃 Organização do Diretório
```
├── README.md
├── tsp-aproximado
│   ├── tsp_aproximativo.ipynb
│   ├── tsp_aproximativo.py
│   └── tsp_data
│       ├── tsp1_253.txt
│       ├── tsp2_1248.txt
│       ├── tsp3_1194.txt
│       ├── tsp4_7013.txt
│       └── tsp5_27603.txt
└── tsp-força-bruta
    ├── forca-bruta-original.c
    ├── forca-bruta-simples.c
    ├── forca-bruta-tempo.c
    ├── forca-bruta.c
    └── tsp_data
        ├── tsp1_253.txt
        ├── tsp2_1248.txt
        ├── tsp3_1194.txt
        ├── tsp4_7013.txt
        └── tsp5_27603.txt
```

##
*Eduarda A. Carvalho e Júlia R. Junqueira, setembro/2022.<br>
Última alteração: setembro/2022.<br>
eduarda.carvalho@inf.ufpel.edu.br, juliar.junqueira@inf.ufpel.edu.br
*
