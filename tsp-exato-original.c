#include <stdio.h>

int cost_matrix[10][10], completed[10], n, cost = 0;

int least(int c);

void loadMatrix() {
  int i, j;

  printf("Enter the number of villages: ");
  scanf("%d", &n);

  printf("\nEnter the Cost Matrix\n");

  for (i = 0; i < n; i++)   {
    printf("\nEnter Elements of Row: %d\n", i + 1);

    for (j = 0; j < n; j++)
      scanf("%d", &cost_matrix[i][j]);

    completed[i] = 0;
  }

  printf("\n\nThe cost list is:");
  for (i = 0; i < n; i++)   {
    printf("\n");
    for (j = 0; j < n; j++)
      printf("\t%d", cost_matrix[i][j]);
  }
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

  for (i = 0; i < n; i++)   {
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

int main() {
  loadMatrix();
  printf("\n\nThe Path is:\n");
  mincost(0); // passing 0 because starting vertex
  printf("\n\nMinimum cost is %d\n ", cost);
  return 0;
}