#ifndef _TREES_H
#define _TREES_H

#include "lists.h"

typedef struct _tnode {
	char *word;
	LNode *data;
	struct _tnode *left, *right;
} TNode;

TNode *treeCreate(void);
void treeAdd(TNode *, MP3Tag_t *, char *word);
LNode *treeGet(TNode *, char *word);
void treeDelete(TNode *);
void treeBalance(TNode *root);

#endif