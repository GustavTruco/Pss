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
	char *r=st;
	char *y=st+1;
	int len=1;
	while(*p){
	    if(*p!=' ' || *t!=' '){
	        len++;
	    }
	    p++;
	    t++;
	}
	char*newstring=malloc(len*sizeof(char));
	char *w=newstring;
	while(*r!='\0'){
	    if(*r!=' ' || *y!=' '){
	        *w=*r;
	        w++;
	    }
	    r++;
	    y++;
	}
	*w='\0';
	return newstring;
}
