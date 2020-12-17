#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "viajante.h"

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

double viajante_par(int z[], int n, double **m, int nperm, int p) {
    int pids[p];
    int infds1[p];
    int infds2[p];
    int perms=nperm/p;
    double minDist= DBL_MAX;

    for (int k=0; k<p;k++){
        int fds1[2];
        int fds2[2];
        pipe(fds1);
        pipe(fds2);
        if((pids[k]= fork())==0){
            close(fds1[0]);
            close(fds2[0]);
            int x[n+1];
            double res= viajante(x,n,m,perms);
            write(fds1[1],x,(n+1)*sizeof(int));
            write(fds2[1],&res,sizeof(double));
            exit(0);
        }
        else{
            close(fds1[1]);
            close(fds2[1]);
            infds1[k]=fds1[0];
            infds2[k]=fds2[0];
        }
    }

    for (int k=0; k<p;k++){
        int pipedz[n+1];
        double pipedd;
        leer(infds1[k],pipedz,(n+1)*sizeof(int));
        leer(infds2[k],&pipedd,sizeof(double));
        waitpid(pids[k],NULL,0);
        close(infds1[k]);
        close(infds2[k]);
        if (pipedd<minDist){
            minDist=pipedd;
            for(int i=0; i<=n;i++){
                z[i]=pipedz[i];
            }
        }
    }
    return minDist;
}
