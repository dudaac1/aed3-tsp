#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define TAM_MAX_LINHA 1024

FILE * abrirArq(int * tam, FILE ** arq, char * nomeArq);
void lerArq(int ** mat, int tam, FILE * arq);
int ** alocaMatriz(int tam);
int * alocaVetor(int tam);
int calcCustoMin(int * ciclo, int ** m, int tam);
int * troca(int * ciclo, int i, int j);
void forcabruta(int * ciclo, int ** mat, int tam, int pos, int * custoMinimo);
void fechar(int *** m, int ** v, FILE ** arq, int tam);
double retornaTempo(struct timeval begin, struct timeval end);

int main(int argc, char * argv[]) {
  if (argc == 1) {
    printf("\nNecessario o nome do .txt da matriz de custo ao executar o .exe.\n");
    exit(1);
  }
  
  struct timeval begin, end;

  int ** matriz, * vet, tam, op;
  FILE * arq;
  int custoMinimo = 99999;

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
    gettimeofday(&begin, 0);
    forcabruta(vet, matriz, tam, 0, &custoMinimo);
	  gettimeofday(&end, 0);
		printf("\nMENOR CUSTO: %d\n", custoMinimo);
    printf("Tempo: %f segundos\n", retornaTempo(begin, end));
    break;
  case 2:
    fechar(&matriz, &vet, &arq, tam);
    printf("Encerrando o programa.\n");
    break;
  default:
    printf("Valor nao reconhecido.\n");
    break;
  }
  return 0;
}

double retornaTempo(struct timeval begin, struct timeval end) {
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	return seconds + microseconds * 1e-6;
}

FILE * abrirArq(int * tam, FILE ** arq, char * nomeArq) {
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

int calcCustoMin(int * ciclo, int ** m, int tam) {
  int j, custo = 0;
  for (j = 0; j < tam - 1; j++) { // calcula o custo de cada vertice
    custo += m[ciclo[j]][ciclo[j + 1]];
    // printf("(%d) -> ", ciclo[j]); //imprime cada nodo de cada calculo de custo
  }
  custo += m[ciclo[tam - 1]][ciclo[0]]; // calcula o ultimo o custo do ultimo vertice
  // printf("(%d)\n", ciclo[tam-1]); //imprime ultimo nodo de calculo de custo
  return custo; // retorna o custo calculado
}

int * troca(int * ciclo, int i, int j) {
  int aux = ciclo[i];
  ciclo[i] = ciclo[j];
  ciclo[j] = aux;
  return ciclo;
}

void forcabruta(int * ciclo, int ** mat, int tam, int pos, int * custoMinimo) {
  int custo = 0; // custo calculado para cada vertice do caminho
  int j;

  if (pos == tam - 1) {
    custo = calcCustoMin(ciclo, mat, tam);
    if (custo < *custoMinimo) {
      printf("\tNOVO VALOR :: custo minimo - anterior: %d; atual: %d\n", * custoMinimo, custo);
      *custoMinimo = custo;
    }
  }
  else {
    for (j = pos; j < tam; j++) {
      ciclo = troca(ciclo, pos, j); // responsavel por fazer a troca dos vertices de cidades (permutação)
      forcabruta(ciclo, mat, tam, pos + 1, custoMinimo); //
      ciclo = troca(ciclo, pos, j);
    }
  }
  return;
}

void fechar(int *** m, int ** v, FILE ** arq, int tam) {
  if (!(*arq))   {
    printf("Nao e possivel fechar arquivo pois nao esta aberto\n");
    exit(1);
  }
  fclose(*arq);

  free(*v);
  for (int i = 0; i < tam; i++)
    free((*m)[i]);
  free(*m);
}