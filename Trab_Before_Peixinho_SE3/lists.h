#ifndef _LISTS_H
#define _LISTS_H

#include "tagtype.h"

typedef struct _lnode {
	MP3Tag_t *data;
	struct _lnode *next;
} LNode;

LNode *listCreate(void);
void listAdd(LNode *, MP3Tag_t *);
void listDelete(LNode *);

#endif