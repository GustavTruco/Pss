#include <stdio.h>
#include <stdlib.h>

#include "t1.h"

unsigned long long dupMasLargo(unsigned long long x){
    unsigned long long tam = 0;
    unsigned int cadena = 0;
    for (unsigned int i=1;i<=32;i++){
            unsigned int mask= (1ULL<<i)-1;
            unsigned int p_cadena= x & mask;
            if ((p_cadena ^ ((x >> i) & mask))==0){
                tam=i;
                cadena=p_cadena;
            }
    }
    unsigned long long result = (tam << 32)|cadena;
    return result;
}
