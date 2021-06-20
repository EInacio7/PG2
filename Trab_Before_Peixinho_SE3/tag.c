#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tag.h"

static MP3Tag_t *tagCreate(void);

MP3Tag_t *tagRead(char *filename, int *resPtr, StrSet_t *sSet) {
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		if(resPtr != NULL) *resPtr = 1;
		return NULL;
	}
	MP3Tag_t *tag = tagCreate();
	tag->fileName = malloc(strlen(filename) + 1);
	if(tag == NULL || tag->fileName == NULL) {
		fprintf(stderr, "Error creating new MP3Tag_t @ tagRead\n");
		fclose(fp);
		return NULL;
	}
	strcpy(tag->fileName, filename);
	
	fseek(fp, -125, SEEK_END);
	
	fread(tag->title, MAX_TIT, 1, fp);
	tag->title[MAX_TIT] = 0;
	char artist[MAX_ART + 1], album[MAX_ALB + 1];
	fread(artist, MAX_ART, 1, fp);
	artist[MAX_ART] = 0;
	tag->artist = strSetSearchAdd(sSet, artist);
	fread(album, MAX_ALB, 1, fp);
	album[MAX_ALB] = 0;
	tag->album = strSetSearchAdd(sSet, album);
	char aux[5];
	fread(aux, 1, 4, fp);
	aux[4] = 0;
	tag->year = (short) atoi(aux);
	fread(tag->comment, MAX_COM, 1, fp);
	tag->comment[MAX_COM] = 0;
	fseek(fp, -1, SEEK_CUR);
	fread(&tag->track, 1, 1, fp);
	fread(&tag->genre, 1, 1, fp);
	
	fclose(fp);
	
	return tag;
}

void tagDelete(MP3Tag_t *tag) {
	free(tag->fileName);
	free(tag);
}

static MP3Tag_t *tagCreate(void) {
	MP3Tag_t *tag = malloc(sizeof(MP3Tag_t));
	if(tag == NULL) {
		fprintf(stderr, "Error allocating new MP3Tag_t @ tagCreate\n");
		return NULL;
	}
	return tag;
}