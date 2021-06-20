#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setdata.h"
#include "tag.h"

static void showTags(MP3Tag_t **, int);
static int cmpArtist(const void *, const void *);
static int cmpTitle(const void *, const void *);

TagSet_t *setCreate(void) {
	TagSet_t *set = malloc(sizeof(TagSet_t));
	if(set == NULL) {
		fprintf(stderr, "Error allocating new TagSet_t @ setCreate\n");
		return NULL;
	}
	set->size = BASE_SIZE;
	set->count = 0;
	set->data = malloc(sizeof(MP3Tag_t *) * BASE_SIZE);
	if(set->data == NULL) {
		fprintf(stderr, "Error allocating TagSet_t data field @ setCreate\n");
		free(set);
		return NULL;
	}
	set->tree = treeCreate();
	if(set->tree == NULL) {
		fprintf(stderr, "Error allocating TNode data field @ setCreate\n");
		free(set->data);
		free(set);
		return NULL;
	}
	set->aux = NULL;
	return set;
}

void setAdd(TagSet_t *set, MP3Tag_t *tag) {
	if(set->count >= set->size) {
		set->size += BASE_SIZE;
		set->data = realloc(set->data, sizeof(MP3Tag_t *) * set->size);
		if(set->data == NULL) {
			fprintf(stderr, "Error reallocating TagSet_t data field @ setAdd\n");
			exit(EXIT_FAILURE);
		}
	}
	
	set->data[set->count++] = tag;
}

static void buildTree(TNode *root, MP3Tag_t **tags, int count) {
  char sc[MAX_TIT];
  for(int i = 0; i < count; i++) {
    strcpy(sc, tags[i]->title);
    char *word = strtok(sc, " \t\n");
    while(word != NULL){
      treeAdd(root, tags[i], word);
      word = strtok(NULL, " \t\n");
    }
  }
  treeBalance(root);
}

void setReady(TagSet_t *set) {
	set->aux = malloc(sizeof(MP3Tag_t *) * set->count);
	if(set->aux == NULL) {
		fprintf(stderr, "Error allocating TagSet_t aux field @ setReady\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0; i < set->count; i++)
		set->aux[i] = set->data[i];
	qsort(set->data, set->count, sizeof(MP3Tag_t *), cmpTitle);
	qsort(set->aux, set->count, sizeof(MP3Tag_t *), cmpArtist);
	buildTree(set->tree, set->data, set->count);
}

static void showWord(char *word, TNode *tree) {
	LNode *list = treeGet(tree, word);
	if(list == NULL) {
		printf("No musics with that word\n");
		return;
	}
	int i = 1;
	do {
		printf("|%d\t|%s\t|%s\t|%s\t|%d\t|%s\t|%d\t|%d\t|%s\n",
			i++,
			list->data->title,
			list->data->artist,
			list->data->album,
			list->data->year,
			list->data->comment,
			list->data->track,
			list->data->genre,
			list->data->fileName
		);
		list = list->next;
	} while(list != NULL);
}

void setCommand(TagSet_t *set, char *cmdLine) {
	char c = cmdLine[0];
	char word[256];
	switch(c) {
		case 'a':
		case 'A':
			showTags(set->aux, set->count);
			break;
		case 't':
		case 'T':
			showTags(set->data, set->count);
			break;
		case 's':
		case 'S':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
				showWord(word, set->tree);
			else
				printf("Please provide a word\n");
			break;
		case 'q':
		case 'Q':
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid operation!\n");
	}
}

void setDelete(TagSet_t *set) {
	for(int i = 0; i < set->count; i++) {
		tagDelete(set->data[i]);
	}
	treeDelete(set->tree);
	free(set->data);
	free(set->aux);
	free(set);
}

static int cmpArtist(const void *a, const void *b) {
	MP3Tag_t *m1 = *((MP3Tag_t **) a);
	MP3Tag_t *m2 = *((MP3Tag_t **) b);
	int cmp = strcmp(m1->artist, m2->artist);
	if(cmp == 0) {
		cmp = strcmp(m1->album, m2->album);
		if(cmp == 0) return strcmp(m1->title, m2->title);
	}
	return cmp;
} 

static int cmpTitle(const void *a, const void *b) {
	MP3Tag_t *m1 = *((MP3Tag_t **) a);
	MP3Tag_t *m2 = *((MP3Tag_t **) b);
	int cmp = strcmp(m1->title, m2->title);
	if(cmp == 0) {
		cmp = strcmp(m1->artist, m2->artist);
		if(cmp == 0) return strcmp(m1->album, m2->album);
	}
	return cmp;
}

static void showTags(MP3Tag_t **tags, int count) {
	printf("|Faixa\t|Title\t|Artist\t|Album\t|Year\t|Comment\t|Track\t|Genre\t|FileName\n");
	for(int i = 0; i < count; i++)
		printf("|%d\t|%s\t|%s\t|%s\t|%d\t|%s\t|%d\t|%d\t|%s\n",
			i+1,
			tags[i]->title,
			tags[i]->artist,
			tags[i]->album,
			tags[i]->year,
			tags[i]->comment,
			tags[i]->track,
			tags[i]->genre,
			tags[i]->fileName
		);
}
