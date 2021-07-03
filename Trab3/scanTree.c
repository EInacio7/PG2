#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "strCol.h"
#include "file.h"
#include "aref.h"

#ifndef DT_DIR
# define DT_UNKNOWN	0
# define DT_FIFO	1
# define DT_CHR		2
# define DT_DIR		4
# define DT_BLK		6
# define DT_REG		8
# define DT_LNK		10
# define DT_SOCK	12
# define DT_WHT		14
#endif
/**
void scanDirTree( char *path, StrShare *pathShare, RefArray *origRef, RefArray *sortRef ){
	
	//char p = ".";
	//FileInfo *fi = malloc(FileInfo);
    DIR* d = opendir(path);
    struct dirent * de;
    //int files = 0;
    printf("path: %s\n", path);
	strSharedAdd(pathShare, path);
	
	if (d == NULL) {
		printf("Failed to open directory.\n");
		return;
	}
	
	//char* fn = malloc(sizeof(char)*500);
	//char *barra = "/";
	while(( de = readdir( d ) ) != NULL ){
		if(de->d_type == DT_DIR){
			if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
				printf("name DIR %s\n", de->d_name);
				char *new_path = (char *)malloc(strlen(path) + strlen(de->d_name) + 1);
				sprintf(new_path, "%s/%s", path, de->d_name);
				scanDirTree(new_path, pathShare, origRef, sortRef);
				free(new_path);
			}
			else{
				printf("name FILE %s\n", de->d_name);
			}
			if (strcmp(path, ".")==0){
				strcat(fn, barra);
				//printf("aux: %s\n", fn);
				strcat(fn, de->d_name);
				//printf("aux: %s\n", fn);
				scanDirTree(fn, pathShare, origRef, sortRef);
				printf("helloTree\n");
			}
			
			strcpy(fn, path);
			//printf("aux: %s\n", fn);
			strcat(fn, barra);
			//printf("aux: %s\n", fn);
			strcat(fn, de->d_name);
			//printf("aux: %s\n", fn);
			scanDirTree(fn, pathShare, origRef, sortRef);
			printf("helloTree\n");
		}
		if(de->d_type == 8){
			printf("name FILE %s\n", de->d_name);
			FileInfo *file = fileInfoNew(path, de->d_name);
			refArrAdd(origRef, file);
			refArrAdd(sortRef, file);			
		}
	
	}
	closedir(d);
}**/

void scanDirTree( char *path, StrShare *pathShare, RefArray *origRef, RefArray *sortRef ){
	
    DIR* d;
    struct dirent *de;
    d = opendir(path);
    //printf("path: %s\n", path);
	strSharedAdd(pathShare, path);
	
	if (d == NULL) {
		printf("Failed to open directory.\n");
		return;
	}

	while(( de = readdir( d ) ) != NULL ){
		if(de->d_type == DT_DIR){
			if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
				//printf("name DIR %s\n", de->d_name);
				//printf("%s\n", de->d_name);
				char *new_path = (char *)malloc(strlen(path) + strlen(de->d_name) + 1);
				sprintf(new_path, "%s/%s", path, de->d_name);
				printf("new path %s\n", new_path);
				FileInfo *directory = fileInfoNew(path, de->d_name);
				refArrAdd(origRef, directory);
				refArrAdd(sortRef, directory);
				scanDirTree(new_path, pathShare, origRef, sortRef);
				//strSharedAdd(pathShare, new_path);
				free(new_path);
			}
		}
		else{
			//printf("name FILE %s\n", de->d_name);
			FileInfo *file = fileInfoNew(path, de->d_name);
			refArrAdd(origRef, file);
			refArrAdd(sortRef, file);
		}
	}
	closedir(d);
}

void list_dir(char *path) {
	printf("-------------------------------------\n");
  DIR *dir;
  struct dirent *entry;
  dir = opendir(path);
  
  if (dir == NULL) {
    printf("Failed to open directory.\n");
    return;
  }
   while ((entry = readdir(dir)) != NULL) {
    if(entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        //printf("%c%s\n", indent2, '-', entry->d_name);
        printf("DIR %s\n", entry->d_name);
        char *new_path = (char *)malloc(strlen(path) + strlen(entry->d_name) + 1);
        
        sprintf(new_path, "%s/%s", path, entry->d_name);
        printf("new path %s\n", new_path);
        list_dir(new_path);
		free(new_path);
      }
      } else {
        //printf("%c%s\n", indent2, '-', entry->d_name);
		printf("FILE %s\n", entry->d_name);
      }
    }
    closedir(dir);
}
