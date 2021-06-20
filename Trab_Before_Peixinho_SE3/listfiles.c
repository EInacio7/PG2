#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listfiles.h"

#define BUFF_SIZE 256

int listScan(char *listName, TagSet_t *data, StrSet_t *sSet) {
	FILE *fp = fopen(listName, "r");
	if(fp == NULL) {
		fprintf(stderr, "Error opening file '%s' for reading @ listScan\n", listName);
		return -1;
	}
	
	char line[BUFF_SIZE];
	
	while(fscanf(fp, "%s", line) != EOF) {
		MP3Tag_t *tag = tagRead(line, NULL, sSet);
		if(tag == NULL) 
			fprintf(stderr, "Error reading tag from file '%s'\n", line);
		else setAdd(data, tag);
	}
	setReady(data);
	fclose(fp);
	return 0;
}