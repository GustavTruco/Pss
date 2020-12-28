#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

/* Esta metodologia puede dar incongruencias respecto a la distancia calculada
 y el arreglo z, ya que si el programa se corta antes de que termine de copiar
 nos quedaremos con los valores de la antigua iteracion*/

static jmp_buf ring;


void check(){
  longjmp(ring, 1);
}

/* Esta metodologia puede dar incongruencias respecto a la distancia calculada
 y el arreglo z, ya que si el programa se corta antes de que termine de copiar
 nos quedaremos con los valores de la antigua iteracion*/


double viajante(int z[], int n, double **m, int nperm) {
  double min= DBL_MAX; // la distancia mas corta hasta el momento
  void (*hdlr)();

  hdlr = signal(SIGINT, check);

  if (setjmp(ring) != 0) {
    signal(SIGINT, hdlr); /* si llegamos aqui es que ocurrio el timeout */
    return min;
  } 

  for (int i= 1; i<=nperm; i++) {
    int x[n+1];          // almacenara una ruta aleatoria
    gen_ruta_alea(x, n); // genera ruta x[0]=0, x[1], x[2], ..., x[n], x[0]=0
    // calcula la distancia al recorrer 0, x[1], ..., x[n], 0
    double d= dist(x, n, m);
    if (d<min) {    // si distancia es menor a la mas corta hasta el momento
      min= d;       // d es la nueva distancia mas corta
      for (int j= 0; j<=n; j++)
        z[j]= x[j]; // guarda ruta mas corta en parametro z
  } }

  signal(SIGINT, hdlr);
  return min;
}
