#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int n =atoi(argv[1]);
    int answer=1;
    for (int i=n;i>=1;i--){
        answer= answer*i;
    }
    printf("%d",n);
    printf("\n");
    printf("%d", answer);
    printf("\n");
    return 0;
}
