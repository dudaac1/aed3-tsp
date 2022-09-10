#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct tsp_data {
  char ** files;
  int count;
} FILES;

FILES * ListDirectoryContents(); //recupera o nome dos arquivos das matrizes de custo
void ChooseTSPFile(FILES * data);

int main() {
  printf("\nTRAVELLING SALESMANN PROBLEM - BEM-VINDO\n");
  printf("Listando arquivos das Matrizes de Custo:\n");
  FILES * tsp_data = ListDirectoryContents();
  ChooseTSPFile(tsp_data);
}

FILES * ListDirectoryContents() {
  FILES * tsp_data = (FILES*)malloc(sizeof(FILES));
  tsp_data->files = NULL;
  tsp_data->count = 0;

  int buffer_size = 1024;
  char * buffer = malloc(sizeof(char)*buffer_size);
  char * dir_name = "\\tsp-files\0";
  GetCurrentDirectory(buffer_size, buffer);
  strcat(buffer, dir_name);

  WIN32_FIND_DATA file;
  HANDLE handle = NULL;
  char sPath[2048];
  sprintf(sPath, "%s\\tsp*", buffer);  // Specify a file mask

  if ((handle = FindFirstFile(sPath, &file)) == INVALID_HANDLE_VALUE) {
    printf("Caminho nao encontrado: [%s]\n", buffer);
    exit(-1);
  }

  do {
    ++tsp_data->count;
    (tsp_data->files) = (char**)realloc(tsp_data->files, sizeof(char) * tsp_data->count);
    (tsp_data->files)[tsp_data->count] = (char*)malloc(sizeof(char)*strlen(file.cFileName));
    printf("\tArquivo [%d]: %s\n", tsp_data->count, file.cFileName);
  } while (FindNextFile(handle, &file)); // Find the next file

  FindClose(handle); 
  return tsp_data;
}

void ChooseTSPFile(FILES * data) {
  int number;
  do {
    printf("Escolha um dos arquivos para executar o codigo: ");
    scanf("%d", &number);
  } while (number < 0 && number > data->count);
  printf("Arquivo escolhido: %d %s", number, data->files[number]);
}