#include <stdio.h>
#include <stdlib.h>

void factoresPrimos(int n){
    int p=2;
    while (n>=p*p){
        if (n%p==0){
            printf("%d  ", p);
            n=n/p;
        }
        else {
            p++;
        }
    }
    printf("%d",n);
    return;
}

int main(int argc, char *argv[]){
    int n =atoi(argv[1]);
    if (n==1){
        printf("1");
    }
    else{
        factoresPrimos(n);
    }
    printf("\n");
    return 0;
    }