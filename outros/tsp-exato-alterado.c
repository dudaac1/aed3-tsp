#include <stdio.h>
#include <stdlib.h>

//provavelmente codigo errado ):

#define MAX_LINE_SIZE 1024
//#define FILE_NAME "./tsp-files/tsp1_253.txt"
//#define FILE_NAME "./tsp-files/tsp2_1248.txt"
//#define FILE_NAME "./tsp-files/tsp3_1194.txt"
//#define FILE_NAME "./tsp-files/tsp4_7013.txt"
#define FILE_NAME "./tsp-files/tsp5_27603.txt"
#define TSP_FILES_PATH "tsp-files/"

int ** cost_matrix, * completed, line_count = 0, cost = 0;

void loadMatrix(void);
int least(int c);
void mincost(int city);

int main() {
  loadMatrix();
  printf("\n\nThe Path is:\n");
  mincost(0); // passing 0 because starting vertex
  printf("\n\nMinimum cost is %d\n ", cost);
  free(cost_matrix);
  free(completed);
  return 0;
}

void loadMatrix() {
  int i, j;
  FILE * archive;
  if ((archive = fopen(FILE_NAME, "r")) == NULL) {
    printf("erro");
    exit(1);
  }
  char c;
  char line[MAX_LINE_SIZE];
  while (!feof(archive)) {
    char * didItRead = fgets(line, MAX_LINE_SIZE, archive);
    if (didItRead) 
      line_count++;
  }
  cost_matrix = (int **)malloc(sizeof(int) * line_count);
  completed = (int *)malloc(sizeof(int) * line_count);
  for (i = 0; i < line_count; i++)
    cost_matrix[i] = (int *)malloc(sizeof(int) * line_count);

  rewind(archive);
  while (!feof(archive)) 
    for (i = 0; i < line_count; i++) {
      for (j = 0; j < line_count; j++) 
        fscanf(archive, "%d", &cost_matrix[i][j]);
      completed[i] = 0;
    }

  printf("\n\nThe cost list is:");
  for (i = 0; i < line_count; i++)   {
    printf("\n");
    for (j = 0; j < line_count; j++)
      printf("\t%d", cost_matrix[i][j]);
  }

  fclose(archive);

}

void mincost(int city) {
  int i, ncity;
  completed[city] = 1;

  printf("%d--->", city + 1);
  ncity = least(city);

  if (ncity == 999)   {
    ncity = 0;
    printf("%d", ncity + 1);
    cost += cost_matrix[city][ncity];
    return;
  }

  mincost(ncity);
}

int least(int c) {
  int i, nc = 999;
  int min = 999, kmin;

  for (i = 0; i < line_count; i++)   {
    if ((cost_matrix[c][i] != 0) && (completed[i] == 0))
      if (cost_matrix[c][i] + cost_matrix[i][c] < min)       {
        min = cost_matrix[i][0] + cost_matrix[c][i];
        kmin = cost_matrix[c][i];
        nc = i;
      }
  }

  if (min != 999)
    cost += kmin;

  return nc;
}