#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZELIN 20


/* Pasa el test de enunciado*/


int main(int argc, char *argv[]) {
  if (argc!=3) {
    fprintf(stderr, "Uso: %s <archivo> <n>\n", argv[0]);
    exit(1);
  }
  int n= atoi(argv[2]);

  FILE * archivo;
  char buffer[21];
  if ( (archivo =fopen(argv[1],"r+"))==NULL){
      perror(argv[1]);
      exit(1);
  }
  int i=0;
  fseek(archivo,i*20,SEEK_SET);
  int count=fread(&buffer, sizeof(char), 20, archivo);
  buffer[20]=0;
  while (count!=0){
    printf("%s",buffer);
    i=i+n;
    fseek(archivo,i*20,SEEK_SET);
    count = fread(&buffer, sizeof(char), 20, archivo);
    buffer[20]=0;
  }
  
  return 0;
  }
