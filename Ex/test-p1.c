#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "p1.h"

// Llama a elimRep(s) y verifica que el resultado sea ref.
// Ejecute con make test-p1-valgrind para verificar que no modifica
// mas alla de los limites de s.

void test(char *s, char *ref) {
  char *t= malloc(strlen(s)+1);
  strcpy(t, s);

  printf("Probando con \"%s\"\n", t);
  elimRep(t);

  // Verifica que el resultado sea ref
  if (strcmp(t, ref)!=0) {
    fprintf(stderr, "El resultado es \"%s\", debio ser \"%s\"\n", t, ref);
    exit(1);
  }

  free(t);
}


int main() {
  test("", "");
  test("a", "a");
  test("++", " +");
  test("----", "   -");
  test(" ", " ");
  test("     ", "     ");
  test("aaa11b*bbaaaa0", "       a1b*ba0");
  printf("Felicitaciones: paso todos los test\n");
  return 0;
}

