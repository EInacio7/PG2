#ifndef _SETDATA_H
#define _SETDATA_H

#include "tagtype.h"
#include "trees.h"

typedef struct _tagset_t {
	int size;			// Quantidade de elementos alojados em data
	int count;			// Quantidade de elementos preenchidos em data
	MP3Tag_t **data;	// Indica array (dinâmico) com ponteiros para as tags
	MP3Tag_t **aux;		// Mesmo que data porém com ordem diferente
	TNode *tree;
} TagSet_t;

#define BASE_SIZE 16

TagSet_t *setCreate(void);
void setAdd(TagSet_t *, MP3Tag_t *);
void setReady(TagSet_t *);
void setCommand(TagSet_t *, char *);
void setDelete(TagSet_t *); 

#endif