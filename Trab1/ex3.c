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
#define MAX_ITEMS 30
#define NUM_TERMS 3

enum ItemType {T_FILE, T_DIRECTORY};

typedef struct{
	enum ItemType type;
	char filename[MAX_FILE_NAME];
	int term;
} Item;

char *terms[] = {"c", "h", "o"};											//array de terminações

int findTerm( char *str, char *terms[], int numTerms ){
	char *ret;

   	for (int i = 0; i < numTerms; i++){
		ret = strrchr(str, *terms[i]);
		if (ret && (str[strlen(str)-strlen(terms[i])] == *ret)){			//verificar se a ocurrencia encontrada corresponde ao ultimo char da string
			return strlen(str)-strlen(terms[i])-1;							//retornar o comprimento do nome do ficheiro subtraindo o comprimento do term encontrado e o ponto
		}
	}
	return strlen(str);														//retornar comprimento de string
}

int loadDirList( Item list[], size_t size, char *path ){
	
	Item *item = malloc(sizeof(Item));

	DIR* d = opendir(path);
	struct dirent * de;
	int i = 0;
	
	while(i<size && ( de = readdir( d ) ) != NULL ){						//preencher cada estrutura Item
		if(de->d_type == 4){
			item->type = T_DIRECTORY;
		}
		if(de->d_type == 8){
			item->type = T_FILE;
		}
		strcpy(item->filename, de->d_name);
		item->term = findTerm(de->d_name, terms, NUM_TERMS);
		list[i] = *item;
		item = malloc(sizeof(Item));										//alocar espaço para a proxima estrutura
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

    int aux = strcmp( (*aa)->filename+(*aa)->term, (*bb)->filename+(*bb)->term );		//comparar terminacoes	
    if (aux == 0){
		return strcmp((*aa)->filename, (*bb)->filename);								//comparar filename completo
	}
    return aux;
}

void sortList(Item list[], size_t num){
	qsort(list, num, sizeof(Item), cmpFunc);
}

void sortAuxList(Item *auxList[], size_t num){
	qsort(auxList, num, sizeof(Item*), cmpFuncAux);
}

int main(){
	int exit = 0;

	char option;	
	Item *list = malloc(sizeof(Item)*MAX_ITEMS);
	char *path = ".";														//procurar dentro da diretoria
	
	loadDirList(list, MAX_ITEMS, path);
	
	Item* auxList[MAX_ITEMS];

	for(int i = 0; i < MAX_ITEMS; ++i){										//preenchimento de auxList com ponteiros para Items
		auxList[i] = &list[i];
	}
	
	printf("\t\t\tCONJUNTO DE VALORES\n\n"
		   "Intervalo de valores válido: \t[0, 255]\n"
		   "Comando 'l'-list.\n"
		   "Comando 'f'-files. \n"
		   "Comando 'q'- quit.\n");
		do{
		scanf("%c", &option);
		switch(option){
			case 'l':
				sortList(list, MAX_ITEMS);
				for(int i = 0; i< MAX_ITEMS; ++i){
					if (list[i].term != 0){									//verificar existencia de Item preenchido
						printf("type: %d\n", list[i].type);
						printf("filename: %s\n", list[i].filename);
						printf("term: %d\n", list[i].term);
						printf("\n");		
					}
				}
				printf("\n");
				break;
			case 'f':
				sortAuxList(auxList,MAX_ITEMS);
				for(int i = 0; i< MAX_ITEMS; ++i){
					if (auxList[i]->term != 0){
						printf("filename: %s\n", auxList[i]->filename);
						printf("\n");		
					}
				}
				printf("\n");
				break;
			case 'q':
				exit = 1;
				printf("\nGoodBye!\n");
				break;				
			}
		
	} while (!exit);
	return 0;		   	
}
