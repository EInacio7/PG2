#include <string.h>
#include <stdlib.h>
#include "aref.h"

RefArray *refArrCreate( void ){
	
	RefArray *aRefStruct = (RefArray*) malloc( sizeof(*aRefStruct) );
	
	aRefStruct->count = 0;
	
	aRefStruct->space = 0;
	
	aRefStruct->data = malloc(sizeof(*aRefStruct->data)); //FileInfo*??
	
	return aRefStruct;

}

void refArrDelete( RefArray *ra){
	free(ra->data);
	free(ra);
}

void refArrAdd( RefArray *ra, FileInfo *ref ){
	if (ra->count == ra->space){
		ra->data = realloc(ra->data, (ra->space += 15) * sizeof(*ra->data));
	}
	ra->data[ra->count++] = ref;
}

int cmpFuncName(const void *p1, const void *p2){
    FileInfo** aa = (FileInfo**) p1;
    FileInfo** bb = (FileInfo**) p2;

	int aux = strcmp((*aa)->name, (*bb)->name);
	if(aux == 0){
		return strcmp((*aa)->path, (*bb)->path);
	}
	return aux;
}

void refArrSort( RefArray *ra ){
	qsort(ra->data, ra->count, sizeof(RefArray*), cmpFuncName);
}

void refArrScan( RefArray *ra, void (*act)(FileInfo *fi, void *param), void *actParam ){
	for (int i = 0; i < ra->count; i++){
		(*act)(ra->data[i], actParam);
	}
}
