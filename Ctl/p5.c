#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "p5.h"

#define P 8

typedef struct{
  int n_dados;
  int suma;
  int repeticiones;
  int favorables;
} Datos;

/*Pasa los test*/
void * thread_function(void *param){
  Datos *data=(Datos *)param;
  int n=data->n_dados;
  int s=data->suma;
  int r=data->repeticiones;
  data->favorables=favorables(n,s,r);
  return NULL;
}
int favorables_par(int n, int sum, int rep) {
  pthread_t t[8];
  Datos data[8];
  for (int i =0;i<8;i++){
    data[i].n_dados=n;
    data[i].suma=sum;
    data[i].repeticiones=rep/8;
    pthread_create(&t[i],NULL,thread_function,&data[i]);
  }

  int result=0;
  for (int i=0;i<8;i++){
    pthread_join(t[i],NULL);
    result+=data[i].favorables;
    }
  return result;
}

