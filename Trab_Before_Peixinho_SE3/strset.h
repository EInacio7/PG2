#ifndef _STRSET_H
#define _STRSET_H

#define MAX_SIZE 256

typedef struct _hnode {
	char *data;
	struct _hnode *next;
} HNode;

typedef struct _strset_t {
	int size;
	HNode **nodes;
} StrSet_t;

StrSet_t *strSetCreate(void);
char *strSetSearchAdd(StrSet_t *set, const char *str);
void strSetDelete(StrSet_t *set);

#endif