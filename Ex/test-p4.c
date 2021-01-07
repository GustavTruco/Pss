#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "p4.h"

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

static long long getUSecsOfDay() {
    struct timeval Timeval;
    gettimeofday(&Timeval, NULL);
    return (long long)Timeval.tv_sec*1000000+Timeval.tv_usec;
}

static int time0= 0;

static int getTime0() {
    return getUSecsOfDay()/1000;
}

static void resetTime() {
  time0= getTime0();
}

static int getTime() {
  return getTime0()-time0;
}

// ----------------------------------------------------
// Creacion de un arbol de n nodos
// Las llaves (k) van de 0 a n-1
// Los valores son aleatorios entre 0 y n-1

Nodo *nuevoArbol(int i, int j, int n) {
  if (i>j)
    return NULL;
  else {
    int k= (i+j+1)/2;
    Nodo *nodo= malloc(sizeof(Nodo));
    nodo->k= k;
    nodo->v= rand()%n;
    nodo->izq= nuevoArbol(i, k-1, n);
    nodo->der= nuevoArbol(k+1, j, n);
    return nodo;
  }
}

// ----------------------------------------------------
// Liberar el espacio ocupado por un arbol

void liberar(Nodo *a) {
  if (a==NULL)
    return;
  else {
    liberar(a->izq);
    liberar(a->der);
    free(a);
  }
}

// ----------------------------------------------------
// Busqueda exhaustiva sencuencial

int buscarLlaveSec(Nodo *a, int valor, int *pk) {
  if (a==NULL)
    return 0;
  else if (a->v==valor) {
    *pk= a->k;
    return 1;
  }
  else
    return buscarLlaveSec(a->izq, valor, pk) ||
           buscarLlaveSec(a->der, valor, pk);
}

int main() {
  printf("Probando busqueda en arbol vacio\n");
  if (buscarLlavePar(NULL, 0, NULL, 8)) {
    fprintf(stderr, "Buscar en un arbol vacio debe retornar 0\n");
    exit(1);
  }
  int k, k_ref;
  Nodo *a= nuevoArbol(0, 0, 1);
  printf("Probando busqueda exitosa en arbol 0 -> 0\n");
  if (!buscarLlavePar(a, 0, &k, 16) && k!=0) {
    fprintf(stderr, "Incorrecto: retorno falso\n");
    exit(1);
  }
  printf("Probando busqueda fallida en arbol 0 -> 0\n");
  if (buscarLlavePar(a, 1, &k, 16)) {
    fprintf(stderr, "Incorrecto: retorno verdadero con k=%d\n", k);
    exit(1);
  }
  liberar(a);
  int n= 10;
  printf("Probando busqueda exitosa en arbol de %d nodos\n", n);
  a= nuevoArbol(0, n-1, n);
  for (int i=0; i<n; i++) {
    int resp_ref= buscarLlaveSec(a, i, &k_ref);
    int resp= buscarLlavePar(a, i, &k, 8);
    if (resp!=resp_ref || (resp_ref && k!=k_ref)) {
      fprintf(stderr, "Incorrecto: valor retornado=%d y k=%d en vez de %d %d\n",
              resp, k, resp_ref, k_ref);
      exit(1);
    }
  }
  printf("Probando busqueda fallida en arbol de %d nodos\n", n);
  if (buscarLlavePar(a, 10, &k, 16)) {
    fprintf(stderr, "Incorrecto: retorno verdadero con k=%d\n", k);
    exit(1);
  }
  n= 10000000;
  printf("Probando busqueda exitosa en arbol de %d nodos\n", n);
  a= nuevoArbol(0, n-1, n);
  for (int i=0; i<100; i++) { // Solo 100 busquedas para que no demore tanto
    int resp_ref= buscarLlaveSec(a, i, &k_ref);
    int resp= buscarLlavePar(a, i, &k, 8);
    if (resp!=resp_ref || (resp_ref && k!=k_ref)) {
      fprintf(stderr, "Incorrecto: valor retornado=%d y k=%d en vez de %d %d\n",
              resp, k, resp_ref, k_ref);
      exit(1);
    }
  }
  printf("Probando busqueda fallida en arbol de %d nodos\n", n);
  if (buscarLlavePar(a, n, &k, 16)) {
    fprintf(stderr, "Incorrecto: retorno verdadero con k=%d\n", k);
    exit(1);
  }
  printf("Midiendo tiempo de busqueda en arbol de %d nodos\n", n);
  {
    resetTime();
    int resp_ref= buscarLlaveSec(a, 1000, &k_ref);
    int tiempo_sec= getTime();
    resetTime();
    int resp= buscarLlavePar(a, 1000, &k, 4);
    int tiempo_par= getTime();
    if (resp!=resp_ref) {
      fprintf(stderr, "Incorrecto: valor retornado=%d y k=%d en vez de %d %d\n",
              resp, k, resp_ref, k_ref);
      exit(1);
    }
    printf("Tiempo secuencial=%d\n", tiempo_sec);
    printf("Tiempo paralelo=%d\n", tiempo_par);
    if (tiempo_par>tiempo_sec) {
      printf("No se preocupe porque la version en paralelo es mas lenta\n");
      printf("que la version secuencial.  Este es un problema que se\n");
      printf("paraleliza mal con procesos pesados\n");
    }
  }
  liberar(a);
  printf("Felicitaciones: paso los tests\n");
  printf("Revise de todas formas que su solucion posea paralelismo\n");
  return 0;
}
