#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *abreArq (char *nomeArq, int *tam) {
	FILE *arq;
	arq = fopen(nomeArq, "r");
	if ( arq == NULL) {	
		printf("Nao foi possivel abrir arquivo\n");
		exit(1); // sai do console
	}
	fscanf( arq,"%d", tam);
	printf("A quantidade de cidade que sera visitada pelo Caixeiro Viajantes: %d\n",*tam );
	return arq;
}

void leituraArquivo( int **mat,  int tam, FILE *arq) {
	int i, j;	
	for (i = 0; i < tam; i++) {
		for( j = 0; j < tam; j++) {	
			fscanf(arq, "%d", &mat[i][j]);
			if (mat[i][j] == -1) {
				mat[i][j] = 100000; 
			}			
		}
	}
}

FILE *fechaArq (FILE *arq) {
	if ( arq  == NULL) 	{
		printf("Nao e possivel fechar arquivo pois nao esta aberto\n");
		exit(1);
	}	
	fclose (arq);
	return arq;
}

int **alocaMatriz(int tam) {
	int **mat, i, j;
	mat = (int**) malloc( tam * sizeof(int*));
	if ( !mat) 	{
		printf("Nao e possivel alocar matriz\n");
		exit(1);
	}
	for( i = 0; i < tam;  i++) 	{
		mat[i] = (int*)malloc(tam * sizeof(int));
		if (!mat[i]) {
			for (j = 0; j < i; j++) {
				free (mat[j]);
			}
			free(mat);
			printf("Nao e possivel alocar matriz\n");
			exit(1);
		}
	}
	return mat;
}

int  *alocaVetor(int tam) {
	int *vet, i;
	vet = (int *) malloc ( tam * sizeof(int));
	if ( !vet) 	{
		printf("Nao foi possivel alocar memoria.\n");
		exit(1);
	}
	for (i = 0; i < tam; i++) 	{
		vet[i] = i;
	}
	return vet;
}

int calcCustoMin(int *ciclo, int **m, int tam) {
	int custo = 0;
	int j;
	
	for (j = 0; j < tam-1; j++) {		
		custo += m[ciclo[j]][ciclo[j+1]];
	}	
	custo += m[ciclo[tam-1]][ciclo[0]];
	return custo; 
}

int *troca (int *ciclo, int i, int j) {
	int aux = ciclo[i];
	ciclo[i] = ciclo[j];
	ciclo[j] = aux;
	return ciclo;
}

void forcabruta (int *ciclo, int **mat, int tam, int pos, int *custoMinimo) {
	int custo = 0; 
	int j; 	
	if (pos == tam-1) {
		custo = calcCustoMin(ciclo, mat, tam);
		if (custo < *custoMinimo)	{
			*custoMinimo = custo;
		}
	}
	else {
		for (j = pos; j < tam; j++) {
			ciclo = troca (ciclo, pos, j);
			forcabruta (ciclo, mat, tam, pos+1, custoMinimo);
			ciclo = troca (ciclo, pos, j);
		}
	}
	return;
}

int main() {
	char nomeArq[124];
	int **mat , *vet , tam, op;
	FILE *arq;
	int custoMinimo = 19999;
	
	do {
		printf("********************\n");
		printf("*  MENU PRINCIPAL  *\n");
		printf("********************\n");
		printf("* 1 - Abrir arquivo*\n");
		printf("* 2 - sair         *\n");
		printf("********************\n");
		scanf (" %d", &op);
		switch (op){
			case 1:
				printf("Informe o nome do arquivo\n");
				scanf(" %s", nomeArq);
				arq = abreArq (nomeArq, &tam);
				vet = alocaVetor(tam);
				mat = alocaMatriz(tam);
				leituraArquivo(mat, tam, arq);
				forcabruta (vet, mat, tam, 0, &custoMinimo);
				printf(" O menor custo entre as cidades e %d\n", custoMinimo);
				break;
			case 2:
				printf ("Encerrando programa\n");
				break;
			default:
				printf("Entre com a opção correta\n");
				break;
		}
	} while (op != 2);
	return 0;
}