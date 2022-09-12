# -*- coding: utf-8 -*-
"""tsp-aproximativo.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1z3x8ZTJ9CZtPrAMxjqlBpATTWbXdqkmn
"""

from time import time
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import minimum_spanning_tree
import matplotlib.pyplot as plt
import networkx as nx
import numpy as np

def read_matrix_file(file):
    with open(file) as matrix_file:
        matrix = [list(map(int, line.split())) for line in matrix_file]

    return matrix

def show_graph(matrix, draw_edges=False):
    G = nx.from_numpy_matrix(np.array(matrix))
    pos = nx.shell_layout(G)
    nx.draw(G, pos)

    if draw_edges:
        nx.draw_networkx_edge_labels(G, pos, label_pos=0.3)

    plt.show()

def path_to_matrix(path, matrix):
    # Cria uma matriz de adjacencia que representa os caminhos disponíveis
    nodes = range(len(matrix))
    path_matrix = np.zeros_like(matrix)

    for index in nodes:
        line = path[index]
        column = path[index + 1]

        edge_weight = matrix[line][column]
        path_matrix[line][column] = edge_weight
    
    return path_matrix

def calculate_path_cost(matrix, path):
    tsp_cost = 0
    nodes = range(len(matrix))

    for index in nodes:
        line = path[index]
        column = path[index + 1]

        edge_weight = matrix[line][column]

        tsp_cost += edge_weight

    return tsp_cost

def approximate_tsp(matrix, initial_node=0):
    #Converte a matriz de adjacência para uma árvore de extensão mínima
    MST = minimum_spanning_tree(matrix)
    MST = MST.toarray().astype(int)

    #Seta os nodos iniciais
    nodes = range(len(MST))

    path = list()
    path.append(initial_node)

    current_node = initial_node
    previous_node = -1

    #Cria um caminho até que todos os nodos estejam conectados
    while len(set(path)) != len(nodes):
        for connected_node in nodes:
            #Se não possui borda (limite),
            if MST[current_node, connected_node] == 0 and MST[connected_node, current_node] == 0:
                continue

            elif connected_node in path:
                continue
            
            else:
                path.append(connected_node)
                current_node = connected_node
                #Reseta o nodo anterior
                previous_node = -1
                break
        else:
            #Se não encontrou uma borda, volta para o nodo anterior
            current_node = path[previous_node]
            previous_node = previous_node - 1
            
    #O caminho termina no ponto inicial.
    path.append(initial_node)
    
    #Calcula o custo
    tsp_cost = calculate_path_cost(matrix, path)
    
    return tsp_cost, path

def evaluate_algorithm(matrix_file):
    matrix = read_matrix_file(matrix_file)

    #Algoritmo aproximado baseado no melhor custo
    costs = dict()

    for initial_node in range(len(matrix)):
        start_time = time()
        cost, approximate_path = approximate_tsp(matrix, initial_node=initial_node)
        approximate_time = time() - start_time

        costs[cost] = {"path": approximate_path,
                       "time": approximate_time}

    min_cost = min(costs.keys())
    min_path = costs[min_cost]["path"]
    min_time = costs[min_cost]["time"]

    #Pega o custo pelo nome do arquivo
    file_name = matrix_file.split('/').pop().upper()
    tsp, cost = file_name.split('_')
    cost = cost.split('.')[0]
    
    return tsp, min_cost, min_time

files = (("tsp1_253.txt", True),
         ("tsp2_1248.txt", True),
         ("tsp3_1194.txt", False),
         ("tsp4_7013.txt", False),
         ("tsp5_27603.txt", False))

print("TSP\t\tAA Cost\t\tAA Time")

    #Alterar o local para o path do arquivo
for tsp_file in files:
    tsp, brute_force = tsp_file
    tsp, ap_cost, ap_time = evaluate_algorithm(f"/content/drive/MyDrive/Colab Notebooks/tsp_data/{tsp}")

    print(f'{tsp}\t\t{ap_cost}\t\t{ap_time:.5f}')