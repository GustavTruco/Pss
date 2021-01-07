#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "p4.h"

// lee exactamente n bytes de un pipe
int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

int buscarLlavePar(Nodo *a, int valor, int *pk, int p) {
  pid_t pids[p];
  int infds[p];
  int result=0;
  if (a==NULL){
    return 0;
  }
  else if (a->v==valor) {
    if (*pk!=a->k){
    *pk= a->k;
    return 1;
    }
  }

  else if(p<=1){
    return 0;
  }
  else{
   
   for(int i=0;i<p;i++){
     int fds[2];
     pipe(fds);

     if((pids[i]=fork())==0){
      close(fds[0]);
      result= buscarLlavePar(a->der,valor, pk,p-(p/2));
      write(fds[1],&result,sizeof(result));
      exit(0);
     }
     else{
       close(fds[1]);
       infds[i]=fds[0];
      result= buscarLlavePar(a->izq,valor, pk,p/2);
     }
   }
    
    for (int i=0;i<p;i++){
      int resulthijo;
      leer(infds[i],&resulthijo,sizeof(resulthijo));
      if (resulthijo==1){
        result=1;
      }
      close(infds[i]);
      waitpid(pids[i],NULL,0);
    }
    return result;

  }

  return 0;

}
