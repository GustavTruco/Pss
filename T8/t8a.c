#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

volatile int checker=0;

void ring(){
    checker=1;
}

double viajante(int z[], int n, double **m, int nperm) {
  double min= DBL_MAX; // la distancia mas corta hasta el momento
  for (int i= 1; i<=nperm; i++) {
    signal(SIGINT,ring);
    if (checker==0){
      int x[n+1];          // almacenara una ruta aleatoria
      gen_ruta_alea(x, n); // genera ruta x[0]=0, x[1], x[2], ..., x[n], x[0]=0
      // calcula la distancia al recorrer 0, x[1], ..., x[n], 0
      double d= dist(x, n, m);
        if (d<min) {    // si distancia es menor a la mas corta hasta el momento
          min= d;       // d es la nueva distancia mas corta
          for (int j= 0; j<=n; j++)
            z[j]= x[j]; // guarda ruta mas corta en parametro z
      }
    }
    else{
      break;
    }
  }
  checker=0;
  return min;
}
