#include <stdio.h>
#include <stdlib.h>

#include "p2.h"

Nodo *lista(char c, Nodo *cola) {
  Nodo *nodo= malloc(sizeof(Nodo));
  if (nodo==NULL) {
    fprintf(stderr,
            "Se acabo la memoria.  Parace que Ud. no libera los nodos\n");
    exit(1);
  }
  nodo->c= c;
  nodo->prox= cola;
  return nodo;
}

int iguales(Nodo *lis1, Nodo *lis2) {
  if (lis1==NULL)
    return lis2==NULL;
  if (lis2==NULL)
    return 0;
  return lis1->c==lis2->c && iguales(lis1->prox, lis2->prox);
}

void mostrar(Nodo *lis) {
  while (lis!=NULL) {
    printf("%c ", lis->c);
    lis= lis->prox;
  }
  printf("\n");
}

void liberar(Nodo *lis) {
  Nodo *prox;
  while (lis!=NULL) {
    prox= lis->prox;
    free(lis);
    lis= prox;
  }
}

int verboso= 1;

void test(Nodo *lis, Nodo *ref) {
  if (verboso) {
    printf("Probando con: ");
    mostrar(lis);
  }
  mediaLista(&lis);
  if (!iguales(lis, ref)) {
    printf("Resultado incorrecto:");
    mostrar(lis);
    exit(1);
  }
  liberar(lis);
  liberar(ref);
}

int main() {
  test(NULL, NULL);
  test(lista('a', NULL), NULL);
  test(lista('a', lista('b', NULL)), lista('b', NULL));
  test(lista('1', lista('2', lista('3', NULL))), lista('2', NULL));

  // Test del enunciado
  Nodo *h= lista('g', lista('f', lista('x', lista('b', lista('r', NULL)))));
  Nodo *ref= lista('f', lista('b', NULL));
  test(h, ref);

  // Ahora sin r
  h= lista('g', lista('f', lista('x', lista('b', NULL))));
  ref= lista('f', lista('b', NULL));
  test(h, ref);

  // Listas de n= 0, 1, 2, ..., max_n elementos
  // ¡No se debe acabar la memoria!
  verboso= 0;
  int max_n= 1000;
  printf("Apareceran ~ %d puntos\n", max_n/100);
  for (int n=1; n<=max_n; n++) {
    char c='a';
    Nodo *lis= NULL;
    Nodo *ref= NULL;
    for (int i= n-1; i>=0; i--) {
      lis= lista(c, lis);
      if ( (i&1) == 1 )
        ref= lista(c, ref);
      c= c=='z' ? 'a' : c+1;
    }
    test(lis, ref);
    if (n%100==0) {
      putchar('.');
      fflush(stdout);
    }
  }

  printf("\nFelicitaciones: paso todos los tests\n");
  return 0;
}
