#include <stdio.h>
#include "file.h"
#include "aref.h"

#define MAX_TERM 20

#ifndef TNODE_H
#define TNODE_H

typedef struct tNode{
	struct tNode *left, *right; // ponteiros de ligação
	char termin[MAX_TERM]; // string - terminação representada
	RefArray *refArr; // referencias associadas
} TNode; 

void tAdd( TNode **rootPtr, char *termin, FileInfo *ref ); 
void tBalance( TNode **rootPtr ); 
RefArray *tSearch( TNode *root, char *termin); 
void tFree( TNode *root );

#endif
