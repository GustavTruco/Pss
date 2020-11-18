#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "maleta.h"

typedef struct{
  double * w;
  double * v;
  int * z;
  int n;
  double maxW;
  int k;
  double best;
} Maleta;

/*Pasa los test*/
void * thread_function(void *param){
    Maleta * maleta=(Maleta *)param;
    double* w= maleta->w;
    double* v= maleta->v;
    int* z=maleta->z;
    int n=maleta->n;
    double maxW=maleta->maxW;
    int k=maleta->k;
    maleta->best=llenarMaletaSec(w,v,z,n,maxW,k);
    return NULL;
}
double llenarMaletaPar(double w[], double v[], int z[], int n, double maxW, int k){
  pthread_t t[8];
  Maleta maleta[8];
  for (int i =0;i<8;i++){
    maleta[i].w=w;
    maleta[i].v=v;
    maleta[i].n=n;
    maleta[i].maxW=maxW;
    maleta[i].k=k/8;
    maleta[i].z=malloc(n*sizeof(int));
    pthread_create(&t[i],NULL,thread_function,&maleta[i]);
  }

  double best=0;
  for (int i=0;i<8;i++){
    pthread_join(t[i],NULL);
    if (maleta[i].best>best){
        best=maleta[i].best;
        for (int j=0;j<n;j++){
        z[j]=maleta[i].z[j];
        }
    }
    free(maleta[i].z);
    }
  return best;
}

