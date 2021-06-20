#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    int space; // quantidade de elementos alojados para o array data
    int count; // quantidade de elementos preenchidos
    char **data; // array de ponteiros para as strings existentes
} StrShare;

typedef struct {
   char *path; // string partilhada - localização do ficheiro
   char *name; // string alojada dinamicamente - nome completo
   int term; // posição da terminação no nome
} FileInfo;

typedef struct {
    int space; // quantidade de elementos alojados para o array data
    int count; // quantidade de elementos preenchidos
    FileInfo **data; // array de ponteiros
} RefArray;

/******** Na função abaixo falta verificar o numItems (para ver a quantidade de elementos alojados para o array data) *********/
StrShare *strShareCreate(void){
    StrShare *ss = malloc(sizeof(StrShare));
    if(ss == NULL){
        fprintf(stderr, "Error allocating new StrShare @ strShareCreate\n");
        return NULL;
    }
    ss->space = numItems;// Confirmar o valor/variavel a colocar aqui
    ss->count = 0;
    ss->data = realloc(sizeof(char*)*numItems);
    if(ss == NULL){
        fprintf(stderr, "Error allocating new StrShare data field @ strShareCreate\n");
        free(ss);
        return NULL;
    }
    return ss;
}

void strShareDelete(StrShare *share){
    // libertar espaço das strings
    for(int i=0; i < share->count; i++){
        free(share->data[i]) // not sure que é assim que se faz!!!
    }
    // libertar espaço alojado dinamicamente
    free(share->data);
    free(share->space);
    free(share->count);
}

char *strSharedAdd( StrShare *share, char *str){
    if(share->count >= share->space){
        share->space += numItems;
        share->data = realloc(share->data, sizeof(char *) * share->space);
        if(share->data == NULL) {
			fprintf(stderr, "Error reallocating StrShare data field @ strShareAdd\n");
			exit(EXIT_FAILURE);
		}
    }
    share->data[share->count++] = str;
    return share->data[share->count];
}