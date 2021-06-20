#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strset.h"

//https://stackoverflow.com/questions/7666509/hash-function-for-string
static unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while((c = *str++)) 
      hash = ((hash << 5) + hash) + c;

    return hash % MAX_SIZE;
}

static HNode *newNode(const char *str) {
	HNode *node = malloc(sizeof(HNode));
	if(node == NULL) {
		fprintf(stderr, "Error allocating new HNode @ newNode\n");
		return NULL;
	}
	int len = strlen(str);
	node->data = malloc(len + 1);
	if(node->data == NULL) {
		fprintf(stderr, "Error allocating data @ newNode\n");
		free(node);
		return NULL;
	}
	strcpy(node->data, str);
	node->data[len] = 0;
	node->next = NULL;
	return node;
}

StrSet_t *strSetCreate(void) {
	StrSet_t *set = malloc(sizeof(StrSet_t));
	if(set == NULL) {
		fprintf(stderr, "Error allocating new StrSet_t @ strSetCreate\n");
		return NULL;
	}
	set->size = MAX_SIZE;
	set->nodes = malloc(MAX_SIZE * sizeof(HNode *));
	if(set->nodes == NULL) {
		fprintf(stderr, "Error allocating field nodes @ strSetCreate\n");
		free(set);
		return NULL;
	}
	return set;
}

static char *strSetSearch(StrSet_t *set, const char *str) {
	unsigned long pos = hash(str);
	HNode *node = set->nodes[pos];
	while(node) {
		if(strcmp(node->data, str) == 0)
			return node->data;
		node = node->next;
	}
	return NULL;
}

static char *strSetAdd(StrSet_t *set, const char *str) {
	unsigned long pos = hash(str);
	HNode *node = newNode(str);

	if(node == NULL) {
		fprintf(stderr, "Error allocating node @ strSetAdd\n");
		return NULL;
	}

	if(set->nodes[pos] == NULL) {
		set->nodes[pos] = node;
		return node->data;
	}

	HNode *it = set->nodes[pos];
	while(it->next) it = it->next;
	it->next = node;

	return node->data;
}

char *strSetSearchAdd(StrSet_t *set, const char *str) {
	char *word = strSetSearch(set, str);
	if(word != NULL) return word;
	return strSetAdd(set, str);
}

void strSetDelete(StrSet_t *set) {
	if(set == NULL) return;
	if(set->nodes != NULL) {
		for(int i = 0; i < MAX_SIZE; i++) {
			HNode *it = set->nodes[i], *aux;
			while(it) {
				free(it->data);
				aux = it;
				it = it->next;
				free(aux);
			}
		}
		free(set->nodes);
	}
	free(set);
}