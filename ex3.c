#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

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

#define MAX_FILE_NAME 255
#define MAX_ITEMS 20 //65535??

enum ItemType {T_FILE, T_DIRECTORY};

typedef struct{
	enum ItemType type;
	char filename[MAX_FILE_NAME];
	int term;
} Item;

char *terms[] = {"c", "h", "o"};

int findTerm( char *str, char *terms[], int numTerms ){
	char *ret;

   	for (int i = 0; i < numTerms; i++){
		ret = strrchr(str, *terms[i]);
		if (ret && (str[strlen(str)-1] == *ret)){			//VERIFICAR SE ULTIMA OCORRENCIA É O ULTIMO CHAR DA STRING MAS BEM FEITO?
			//printf("token found\n");
			return strlen(str)-strlen(terms[i])-1;
		}
	}
	//printf("token not found\n");
	return strlen(str);
}

int loadDirList( Item list[], size_t size, char *path ){
	
	Item *item = malloc(sizeof(Item));

	DIR* d = opendir(path);
	struct dirent * de;
	int i = 0;
	
	while(i<size && ( de = readdir( d ) ) != NULL ){
		printf("%d\n", de->d_type);
		//item->type = de->d_type;
		//printf("%d\n", item->type);
		if(de->d_type == 4){
			item->type = T_DIRECTORY;
		}
		if(de->d_type == 8){
			item->type = T_FILE;
		}
		strcpy(item->filename, de->d_name);
		item->term = findTerm(de->d_name, terms, 3);
		list[i] = *item;
		item = malloc(sizeof(Item));
		i++;			
	}
	
	return i;
	
}

int cmpFunc(const void *p1, const void *p2){
    Item* aa = (Item*) p1;
    Item* bb = (Item*) p2;

	int aux = aa->type - bb->type;
	if(aux == 0){
		return strcmp(aa->filename, bb->filename);
	}
	return aux;
}

int cmpFuncAux(const void *p1, const void *p2){
    Item** aa = (Item**) p1;
    Item** bb = (Item**) p2;
    
    
}

void sortList(Item list[], size_t num){
	qsort(list, num, sizeof(Item), cmpFunc);
}

void sortAuxList(Item *auxList[], size_t num){
	qsort(list, num, sizeof(Item*), cmpFuncAux);
}

int main(){
	
	Item *item = malloc(sizeof(Item)*500);

	/*
	char *path = malloc(sizeof(char*)+1);
	const char src[20] = "ex.c";
	memcpy(path, src, sizeof(char)*(20));
	*/
	
	char *path = ".";
	
	loadDirList(item, MAX_ITEMS, path);
	sortList(item, 9);
	for(int i = 0; i< 9; ++i){
		printf("type: %d\n", item[i].type);
		printf("filename: %s\n", item[i].filename);
		printf("term: %d\n", item[i].term);
		printf("\n");		
	}	
	return 0;
}
