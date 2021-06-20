#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

static LNode *newNode(MP3Tag_t *tag) {
	LNode *node = malloc(sizeof(LNode));
	if(node == NULL) {
		fprintf(stderr, "Error allocating new LNode @ newNode\n");
		return NULL;
	}
	node->next = NULL;
	node->data = tag;
	return node;
}

LNode *listCreate(void) {
	LNode *list = malloc(sizeof(LNode));
	if(list == NULL) {
		fprintf(stderr, "Error allocating new LNode @ listCreate\n");
		return NULL;
	}
	list->next = NULL;
	list->data = NULL;
	return list;
}

void listAdd(LNode *list, MP3Tag_t *tag) {
	if(list == NULL) {
		fprintf(stderr, "NULL list @ listAdd\n");
		return;
	}
	if(list->data == NULL) {
		list->data = tag;
		return;
	}
	LNode *node = newNode(tag);
	if(node == NULL) {
		fprintf(stderr, "Error allocating LNode @ listAdd\n");
		return;
	}
	LNode *it = list;
	while(it->next != NULL)
		it = it->next;
	it->next = node;
}

void listDelete(LNode *list) {
	LNode *it = list;
	while(it) {
		LNode *next = it->next;
		free(it);
		it = next;
	}
}