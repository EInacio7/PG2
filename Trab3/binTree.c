#include "binTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tAdd(TNode **rootPtr, char *termin, FileInfo *ref){
	if(*rootPtr == NULL){
		TNode *new = malloc(sizeof(*new));
		new->refArr = refArrCreate();
		new->left = new->right = NULL;
		//new->termin = strcpy( malloc( strlen( termin ) + 1 ), termin );
		
		*rootPtr = new;
		
		return;
	}
	
	int cmp = strcmp(namWord, (*rootPtr)->word);
	if( cmp == 0){
		lAdd(&((*rootPtr)->head), ref);
	}
	else if(cmp < 0){
		tAdd(&(*rootPtr)->left, namWord, ref);
	}
	else{
		tAdd(&(*rootPtr)->right, namWord, ref);
	}
}
