#include "binTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static TNode *treeToSortedList( TNode *r, TNode *link ){ 
	TNode * p; 
		if( r == NULL ) return link; 
		p = treeToSortedList( r->left, r ); 
		r->left = NULL; 
		r->right = treeToSortedList( r->right, link ); 
	return p; 
} 

TNode *sortedListToBalancedTree(TNode **listRoot, int n) { 
	if( n == 0 ) 
		return NULL; 
	TNode *leftChild = sortedListToBalancedTree(listRoot, n/2); 
	TNode *parent = *listRoot; 
	parent->left = leftChild; 
	*listRoot = (*listRoot)->right; 
	parent->right = sortedListToBalancedTree(listRoot, n-(n/2 + 1) ); 
	return parent; 
} 

void tAdd(TNode **rootPtr, char *termin, FileInfo *ref){
	
	if(*rootPtr == NULL){
		
		TNode *new = malloc(sizeof (*new));
		new->left = new->right = NULL;
		strcpy(new->termin, termin);
		*rootPtr = new;
		new->refArr = refArrCreate();
		refArrAdd((*rootPtr)->refArr, ref );

		return;
	}

	int cmp = strcmp(termin, (*rootPtr)->termin);
	if( cmp == 0){
		refArrAdd((*rootPtr)->refArr, ref );
	}
	else if(cmp < 0){
		tAdd(&(*rootPtr)->left, termin, ref);
	}
	else{
		tAdd(&(*rootPtr)->right, termin, ref);
	}
}

//funçao auxiliar para contar elementos numa arvore
int treeElemCount(TNode *r){

   	if( r == NULL )
		return 0;
	return 1 + treeElemCount( r->left ) + treeElemCount( r->right );
}

void tBalance( TNode **rootPtr ){
	*rootPtr = treeToSortedList( *rootPtr, NULL );
	*rootPtr = sortedListToBalancedTree(rootPtr, treeElemCount(*rootPtr));
}

RefArray *tSearch( TNode *root, char *termin){
	if(root == NULL){
		printf("Term não encontrada\n");
		return NULL;
	}
	
	int cmp = strcmp(termin, root->termin);
	if(cmp == 0){
		return root->refArr;
	}
	if(cmp < 0){
		return tSearch(root->left, termin);
	}
	
	return tSearch(root->right, termin);
}

void tFree( TNode *root ){
	if (root != NULL) {
		tFree(root->left);
		free(root->termin);
		refArrDelete(root->refArr);
		tFree(root->right);
		free(root);
	}
}
