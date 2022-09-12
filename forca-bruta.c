#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_LINHA 1024
#define ARQ_DETALHES "detalhes.txt"
#define LINHAS_DETALHES 4

FILE * abrirArq(int * tam, FILE ** arq, char * nomeArq);
void lerArq(int ** mat, int tam, FILE * arq);
int ** alocaMatriz(int tam);
int * alocaVetor(int tam);
int calcCustoMin(int * ciclo, int ** m, int tam, int ** caminho);
int * troca(int * ciclo, int i, int j);
void forcabruta(int * ciclo, int ** mat, int tam, int pos, int * custoMinimo, int ** caminho);
void mostrarValores(int tam, int custoMinimo, int * caminho);
void fechar(int *** m, int ** v, int ** c, FILE ** arq, int tam);

int main(int argc, char * argv[]) {
  if (argc == 1) {
    printf("\nNecessario o nome do .txt da matriz de custo ao executar o .exe.\n");
    exit(1);
  }

  int ** matriz, * vet, tam, op, * caminho;
  FILE * arq;
  int custoMinimo = 19999;

  printf("\n********************\n");
  printf("*  MENU PRINCIPAL  *\n");
  printf("* 1. Calcular      *\n");
  printf("* 2. Sair          *\n");
  printf("********************\n");
  scanf(" %d", &op);
  switch (op) {
  case 1:
    abrirArq(&tam, &arq, argv[1]);
    vet = alocaVetor(tam);
    matriz = alocaMatriz(tam);
    lerArq(matriz, tam, arq);
    caminho = (int *)malloc(sizeof(int) * tam);
    forcabruta(vet, matriz, tam, 0, &custoMinimo, &caminho);
    mostrarValores(tam, custoMinimo, caminho);
    break;
  case 2:
    fechar(&matriz, &vet, &caminho, &arq, tam);
    printf("Encerrando o programa.\n");
    break;
  default:
    printf("Valor nao reconhecido.\n");
    break;
  }
  return 0;
}

FILE * abrirArq(int * tam, FILE ** arq, char * nomeArq) {
  /* *arq = fopen(ARQ_DETALHES, "r");
  if (*arq == NULL) { 
    printf("Nao foi possivel abrir arquivo de detalhes das matrizes\n");
    exit(1); 
  }
  char linha[TAM_MAX_LINHA];
  int i;
  while (!feof(*arq)) {
    for (i = 0; i < LINHAS_DETALHES; i++) {
      fgets(linha, TAM_MAX_LINHA, *arq);
      printf("%s", linha);
    }
    printf("\n");
  }
  int escolha;
  do {
    printf("\n\nDigite o numero do arquivo que deseja abrir: ");
    scanf("%d", &escolha);
  } while (escolha < 0 || escolha > i);

  rewind(*arq);
  char nomeArq[TAM_MAX_LINHA];
  // char aux[TAM_MAX_LINHA];
  for (i = 1; i < escolha; i++) {
    for (int j = 0; j < LINHAS_DETALHES; j++)
      fgets(linha, TAM_MAX_LINHA, *arq);
  }
  fgets(linha, TAM_MAX_LINHA, *arq);
  fgets(nomeArq, TAM_MAX_LINHA, *arq);
  // fgets(aux, TAM_MAX_LINHA, *arq);
  fclose(*arq); */

  printf("Arquivo %s", nomeArq);
  *arq = fopen(nomeArq, "r");
  if (!(*arq)) {
    printf("Nao foi possivel abrir arquivo com a matriz de custo\n");
    exit(1); 
  }
  *tam = 0;   //a cada linha lida do arquivo, soma 1 ao tamanho
  char linha[TAM_MAX_LINHA];
  while (!feof(*arq)) {
    char * didItRead = fgets(linha, TAM_MAX_LINHA, *arq);
    if (didItRead) 
      (*tam)++;
  }
  rewind(*arq);
  printf("\nQuantidade de nodos do grafo: %d\n", *tam);
  // return arq;
}

void lerArq(int ** mat, int tam, FILE * arq) {
  int i, j;
  for (i = 0; i < tam; i++)   {
    for (j = 0; j < tam; j++)     {
      fscanf(arq, "%d", &mat[i][j]);
      // if (mat[i][j] == -1) // cidades não estão conectadas
        // mat[i][j] = 100000; // Assim são desconsideradas
    }
  }
}

int ** alocaMatriz(int tam) {
  int ** mat, i, j;
  mat = (int **)malloc(tam * sizeof(int *));
  if (!mat)   {
    printf("Nao foi possivel alocar matriz\n");
    exit(1);
  }
  for (i = 0; i < tam; i++)   {
    mat[i] = (int *)malloc(tam * sizeof(int));
    if (!mat[i]) {
      for (j = 0; j < i; j++)
        free(mat[j]);
      free(mat);
      printf("Nao foi possivel alocar matriz\n");
      exit(1);
    }
  }
  return mat;
}

int * alocaVetor(int tam) {
  int * vet, i;
  vet = (int *)malloc(tam * sizeof(int));
  if (!vet) {
    printf("Nao foi possivel alocar vetor.\n");
    exit(1);
  }
  for (i = 0; i < tam; i++)
    // Atribui as posições de cada cidade para permitir a permutação
    vet[i] = i;
  return vet;
}

int calcCustoMin(int * ciclo, int ** m, int tam, int ** caminho) {
  int j, custo = 0;
  for (j = 0; j < tam - 1; j++) { // calcula o custo de cada vertice
    custo += m[ciclo[j]][ciclo[j + 1]];
    (*caminho)[j] = ciclo[j];
    // printf("(%d) -> ", ciclo[j]); //imprime cada nodo de cada calculo de custo
  }
  custo += m[ciclo[tam - 1]][ciclo[0]]; // calcula o ultimo o custo do ultimo vertice
  (*caminho)[tam-1] = ciclo[tam-1];
  // printf("(%d)\n", ciclo[tam-1]); //imprime ultimo nodo de calculo de custo
  return custo; // retorna o custo calculado
}

int * troca(int * ciclo, int i, int j) {
  int aux = ciclo[i];
  ciclo[i] = ciclo[j];
  ciclo[j] = aux;
  return ciclo;
}

void forcabruta(int * ciclo, int ** mat, int tam, int pos, int * custoMinimo, int ** caminho) {
  int custo = 0; // custo calculado para cada vertice do caminho
  int j;
  int * caminho_local = (int*)malloc(sizeof(int) * tam);

  if (pos == tam - 1) {
    custo = calcCustoMin(ciclo, mat, tam, &caminho_local);
    // printf("\tcusto minimo %d; custo atual: %d\n", * custoMinimo, custo);
    if (custo < *custoMinimo) {
      printf("\tNOVO VALOR :: custo minimo - anterior: %d; atual: %d\n", * custoMinimo, custo);
      *custoMinimo = custo;
      for (int i = 0; i < tam; i++)
        (*caminho)[i] = caminho_local[i];
    }
  }
  else {
    for (j = pos; j < tam; j++) {
      ciclo = troca(ciclo, pos, j); // responsavel por fazer a troca dos vertices de cidades (permutação)
      forcabruta(ciclo, mat, tam, pos + 1, custoMinimo, caminho); //
      ciclo = troca(ciclo, pos, j);
    }
  }
  free(caminho_local);
  return;
}

void mostrarValores(int tam, int custoMinimo, int * caminho) {
  printf("\nMENOR CUSTO: %d\nCaminho encontrado: ", custoMinimo);
  for (int i = 0; i < tam - 1; i++)
    printf("(%d) -> ", caminho[i]);
  printf("(%d)\n\n", caminho[tam-1]);
}

void fechar(int *** m, int ** v, int ** c, FILE ** arq, int tam) {
  if (!(*arq))   {
    printf("Nao e possivel fechar arquivo pois nao esta aberto\n");
    exit(1);
  }
  fclose(*arq);

  free(*v);
  free(*c);
  for (int i = 0; i < tam; i++)
    free((*m)[i]);
  free(*m);
}