#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "p3.h"

#define NTHREAD 100
#define NITER 1000
#define NTESTS 10

#ifdef SANITIZE
#define NOCUPAR 100
#else
#define NOCUPAR 1000
#endif

static int ocupado= 0;
static int ultima_cat= 0;
static int alt_cnt= 0;

static void *alt_fun(void *ptr) {
  int cat= *(int*)ptr;

  ocupar(cat);

    if (ocupado) {
      fprintf(stderr, "No se respeto exclusion mutua al ocupar el recurso\n");
      exit(1);
    }
    ocupado= 1;
    alt_cnt++;
    if (ultima_cat==cat) {
      fprintf(stderr, "No se entrego alternadamente el recurso (%d)\n",
              alt_cnt);
      exit(1);
    }
    for (int j= 0; j<NITER; j++)
      ;
    ultima_cat= cat;
    ocupado= 0;

  desocupar();

  return NULL;
}

static void *excl_fun(void *ptr) {
  for (int i= 0; i<NOCUPAR; i++) {
    ocupar(0);
    if (ocupado) {
      fprintf(stderr, "No se respeto exclusion mutua al ocupar el recurso\n");
      exit(1);
    }
    ocupado= 1;
    for (int j= 0; j<NITER; j++)
      ;
    ocupado= 0;
    desocupar();
  }
  return NULL;
}

static pthread_t tasks[NTHREAD];
static int categorias[NTHREAD];

int main() {

  printf("Verificando alternancia entre categorias\n");
  for (int i= 1; i<=NTESTS; i++) {
    ocupar(0);

    for (int k=0; k<NTHREAD; k++) {
      categorias[k]= k&1;
      pthread_create(&tasks[k], NULL, alt_fun, &categorias[k]);
    }

    // Se espera un segundo para que todos los threads hayan invocado ocupar
    sleep(1);
    printf("Test numero %d\n", i);
    desocupar();

    for (int k=0; k<NTHREAD; k++) {
      pthread_join(tasks[k], NULL);
    }
  }

  ocupar(0);

  for (int k=0; k<NTHREAD; k++) {
    pthread_create(&tasks[k], NULL, excl_fun, NULL);
  }

  sleep(1);
  printf("Verificando exclusion mutua con threads de categoria 0\n");
  desocupar();

  for (int k=0; k<NTHREAD; k++) {
    pthread_join(tasks[k], NULL);
  }

  printf("Felicitaciones: su tarea funciona\n");
  return 0;
}
