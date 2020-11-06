#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE * archivo;
    char buffer[20];
    char blank[20]="                   \n";
    if ( (archivo =fopen(argv[1],"r+"))==NULL){
        perror(argv[1]);
        exit(1);
    }
    int i=0,j=0;
    fseek(archivo,i*20,SEEK_SET);
    int count=fread(&buffer, sizeof(char), 20, archivo);
    buffer[20]=0;
    while (count!=0){
    if (strncmp(buffer,blank,19)!=0){
        fseek(archivo,20*j,SEEK_SET);
        fwrite(&buffer,sizeof(char),20,archivo);
        j++;
    }
    i++;
    fseek(archivo,i*20,SEEK_SET);
    count = fread(&buffer, sizeof(char), 20, archivo);
    buffer[20]=0;
    }
    while (i>j){
        fseek(archivo,20*j,SEEK_SET);
        fwrite(&blank,sizeof(char),20,archivo);
        j++;
    }
    fclose(archivo);
}