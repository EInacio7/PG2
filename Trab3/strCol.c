#include <string.h>
#include <stdlib.h>
#include "strCol.h"

StrShare *strShareCreate(void){
    StrShare *ss = malloc(sizeof(StrShare));
    if(ss == NULL){
        fprintf(stderr, "Error allocating new StrShare @ strShareCreate\n");
        return NULL;
    }
    ss->space = 0;// 
    ss->count = 0;
    ss->data = malloc(sizeof(char*));
    return ss;
}

void strShareDelete(StrShare *share){

    free(share->data);
    free(share);
}

char *strSharedAdd( StrShare *share, char *str){
    if(share->count >= share->space){
        share->data = realloc(share->data, (share->space += 15) * sizeof(*share->data)); //sizeof porque aponta para primeiro elemento de data que é um char*
        if(share->data == NULL) {
			    fprintf(stderr, "Error reallocating StrShare data field @ strShareAdd\n");
		    	exit(EXIT_FAILURE);
        }
    }  

    share->data[share->count++] = str;
    return share->data[share->count-1];
}

