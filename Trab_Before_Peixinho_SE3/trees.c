#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trees.h"

static TNode *newNode(char *word, MP3Tag_t *tag) {
	TNode *node = malloc(sizeof(TNode));
	if(node == NULL) {
		fprintf(stderr, "Error allocating new TNode @ newNode\n");
		return NULL;
	}
	node->data = listCreate();
	if(node->data == NULL) {
		fprintf(stderr, "Error allocating TNode->data @ newNode\n");
		free(node);
		return NULL;
	}
	listAdd(node->data, tag);
	int len = strlen(word);
	node->word = malloc(len + 1);
	if(node->word == NULL) {
		fprintf(stderr, "Error allocating TNode->word @ newNode\n");
		free(node);
		return NULL;
	}
	strcpy(node->word, word);
	node->word[len] = 0;
	node->left = node->right = NULL;
	return node;
}

static void insertNode(TNode *root, TNode *node) {
	if(root->word == NULL) {
		root->word = node->word;
		root->data = node->data;
		free(node);
		return;
	}
	int cmp = strcmp(root->word, node->word);
	if(cmp < 0) {
		if(root->right == NULL)
		  root->right = node;
		else
		  insertNode(root->right, node);
	} else {
		if(root->left == NULL)
		  root->left = node;
		else
		  insertNode(root->left, node);
	}
}

TNode *treeCreate(void) {
	TNode *tree = malloc(sizeof(TNode));
	if(tree == NULL) {
		fprintf(stderr, "Error allocating new TNode @ treeCreate\n");
		return NULL;
	}
	tree->data = NULL;
	tree->word = NULL;
	tree->left = tree->right = NULL;
	return tree;
}

void treeAdd(TNode *root, MP3Tag_t *tag, char *word) {
  LNode *list = treeGet(root, word);
  if(list != NULL) {
    listAdd(list, tag);
    return;
  }
  TNode *node = newNode(word, tag);
  if(node == NULL) {
    fprintf(stderr, "Error allocating node @ treeAdd\n");
    return;
  }
  insertNode(root, node);
}

LNode *treeGet(TNode *root, char *word) {
	if(root == NULL || root->word == NULL)
		return NULL;
	int cmp = strcmp(root->word, word);
	if(cmp == 0)
		return root->data;
	if(cmp < 0)
		return treeGet(root->right, word);
	return treeGet(root->left, word);
}

void treeDelete(TNode *root) {
	if(root == NULL) return;
	if(root->word != NULL) {
		listDelete(root->data);
		free(root->word);
		treeDelete(root->left);
		treeDelete(root->right);
	}
	free(root);
}

static TNode *treeToSortedList(TNode *r, TNode *link) {
	TNode *p;
	if(r == NULL) return link;
	p = treeToSortedList(r->left, r);
	r->left = NULL;
	r->right = treeToSortedList(r->right, link);
	return p;
}

static TNode* sortedListToBalancedTree(TNode **listRoot, int n) {
	if(n == 0) return NULL;
	TNode *leftChild = sortedListToBalancedTree(listRoot, n/2);
	TNode *parent = *listRoot;
	parent->left = leftChild;
	*listRoot = (*listRoot)->right;
	parent->right = sortedListToBalancedTree(listRoot, n-(n/2 + 1));
	return parent;
}

void treeBalance(TNode *root) {

}
