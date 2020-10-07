#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reducir(char *s){
    char *p=s;
	char *r=s;
	char *q=s+1;
	while (*p){
	    if (*r==' ' && *q==' '){
	        r++;
	        q++;
	        *p=*r;
	    }
	    else{
	       	*p=*r;
	        p++;
	        r++;
	        q++; 
	    }
	}
}

char *reduccion(char *st){
    char *p=st;
	char *t=st+1;
	int len=1;
	while(*p){
	    if(*p!=' ' || *t!=' '){
	        len++;
	    }
	    p++;
	    t++;
	}
	char *w=malloc(len*sizeof(char));
	char *r=st;
	char *y=st+1;
	while(*r){
	    if(*r!=' ' || *y!=' '){
	        *w=*r;
	    }
	    printf("%c",*w);
	    r++;
	    w++;
	    y++;
	}
	return w;
}
