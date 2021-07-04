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
		///char aux[20];
		TNode *new = malloc(sizeof(*new));
		new->refArr = refArrCreate();
		new->left = new->right = NULL;
		//new->termin = strcpy( malloc( strlen( termin ) + 1 ), termin );
		///new->termin = aux;
		//new->termin = *termin;
		strcpy(new->termin, termin);
		*rootPtr = new;
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
   /**int c =  1;             //Deve contar o Node passado
   if (r ==NULL){
       return 0;
   }
   else{
       c += treeElemCount(r->left);
       c += treeElemCount(r->right);
       return c;
   }**/
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
		printf("Term não encontrada");
	}
	
	int cmp = strcmp(termin, root->termin);
	if(cmp == 0){
		return root->refArr;
	}
	else if(cmp < 0){
		tSearch(root->left, termin);
	}
	else{
		tSearch(root->right, termin);
	}
	return NULL;
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
