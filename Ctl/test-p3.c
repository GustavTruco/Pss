#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "p3.h"

int main() {
  char *const_s= "aaa11b*bbaaaa0";
  char *s= malloc(strlen(const_s)+1);
  strcpy(s, const_s);
  elimRep(s);
  if (strcmp(s, "a1b*ba0")!=0) {
    fprintf(stderr, "El resultado es \"%s\", debio ser \"a1b*ba0\"\n", s);
    exit(1);
  }
  free(s);
  printf("Felicitaciones: paso el test del enunciado\n");
  return 0;
}
  
