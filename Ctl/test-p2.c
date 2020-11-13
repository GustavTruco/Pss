#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "p2.h"

// ----------------------------------------------------
// Funcion que muestra un abb con indentacion

void mostrar(Nodo *a, int lvl) {
  int i;
  for (i= 0; i<lvl; i++)
    putchar(' ');

  if (a==NULL) {
    printf("NULL\n");
  }
  else {
    printf("%d\n", a->x);
    mostrar(a->izq, lvl+2);
    mostrar(a->der, lvl+2);
  }
}

// ----------------------------------------------------
// Funcion que construye un arbol binario a partir de otros 2

static Nodo *abb(int x, Nodo *izq, Nodo *der) {
  Nodo *a= malloc(sizeof(*a));
  a->x= x;
  a->izq= izq;
  a->der= der;
  return a;
}

// ----------------------------------------------------
// Funcion que construye un arbol consistente en una sola hoja

static Nodo *hoja(int x) {
  return abb(x, NULL, NULL);
}

// ----------------------------------------------------
// Funcion que verifica que 2 arboles binarios son iguales

static void comparar(Nodo *a, Nodo *b) {
  if (a==NULL) {
    if (b==NULL)
      return;
    fprintf(stderr, "Arboles distintos: a es NULL, b tiene etiqueta %d\n",
                    b->x);
    exit(1);
  }
  else if (b==NULL) {
    fprintf(stderr, "Arboles distintos: b es NULL, a tiene etiqueta %d\n",
                    a->x);
    exit(1);
  }
  else {
    if (a->x!=b->x) {
      fprintf(stderr, "Etiquetas de arboles son distintas: %d != %d\n",
                      a->x, b->x);
      exit(1);
    }
    comparar(a->izq, b->izq);
    comparar(a->der, b->der);
  }
}

// ----------------------------------------------------
// Libera un arbol binario

static void liberar(Nodo *a) {
  if (a!=NULL) {
    liberar(a->izq);
    liberar(a->der);
    free(a);
  }
}

// ----------------------------------------------------
// Crea una copia de un arbol binario

#if 0
static Nodo *copia(Nodo *a) {
  if (a==NULL)
    return NULL;

  Nodo *an= malloc(sizeof(Nodo));
  an->x= a->x;
  an->izq= copia(a->izq);
  an->der= copia(a->der);
  return an;
}
#endif

int main() {
  Nodo *v= NULL;
  podarHojas(&v);
  if (v!=NULL) {
    fprintf(stderr, "No funciona caso i: podar hojas del arbol vacio\n");
    exit(1);
  }
  Nodo *s= hoja(5);
  podarHojas(&s);
  if (s!=NULL) {
    fprintf(stderr,
            "No funciona caso ii: podar hojas de arbol con solo una hoja\n");
    exit(1);
  }
  Nodo *t= abb(5, abb(2, hoja(1), abb(4, hoja(3), NULL)),
                  abb(7, hoja(6), NULL));
  printf("Arbol t antes de podar sus hojas\n");
  mostrar(t, 0);
  podarHojas(&t);
  printf("Arbol t despues de podar sus hojas\n");
  mostrar(t, 0);
  Nodo *ref= abb(5, abb(2, NULL, hoja(4)), hoja(7));
  comparar(t, ref);
  liberar(t);
  liberar(ref);
  printf("Felicitaciones: paso los tests del enunciado\n");
  return 0;
}
