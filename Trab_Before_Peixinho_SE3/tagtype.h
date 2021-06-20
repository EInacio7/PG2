#ifndef _TAGTYPE_H
#define _TAGTYPE_H

#define MAX_TIT 30
#define MAX_ART 30
#define MAX_ALB 30
#define MAX_COM 30

typedef struct _mp3tag_t {
	char title[MAX_TIT + 1];
	char *artist;
	char *album;
	short year;
	char comment[MAX_COM + 1];
	char track, genre;
	char *fileName;	// String com o nome do ficheiro (dinâmica)
} MP3Tag_t;

#endif