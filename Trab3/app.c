#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aref.h"
#include "strCol.h"
#include "scanTree.h"
#include "binTree.h"
#include "hash.h"

void showMenu() {
	printf("Menu:\n");
	printf("o - Displays the file list as originally found.\n");
	printf("n - Display the file list sorted by alphabetical ordering\n");
    printf("t <word> - Displays the file list sorted by specified file extension.\n");
	printf("s <word> - Display the file list with the specified name\n");
	printf("q - Exits program\n");
}

void cmpWordS(FileInfo *fi, void *param) {
   
	char token[12];
	memset(token, '\0', sizeof(token));
	char* aux = strcpy( malloc( strlen( fi->name ) + 1 ), fi->name );
	strncpy(token, aux, fi->term);
	if(!strcmp(token, param)){
		printf("\n");
		printf("path %s\n", fi->path);
		printf("name %s\n", fi->name);
		printf("term: %d\n", fi->term);
	}	
}

void cmpWordT(FileInfo *fi, void *param) {
    
	if(!strcmp(&fi->name[(fi->term)+1], param)){
		printf("\n");
		printf("path %s\n", fi->path);
		printf("name %s\n", fi->name);
		printf("term: %d\n", fi->term);
	}
}

void printRef(FileInfo *fi, void *param){
	
	printf("\n");
	printf("name: %s\n", fi->name);
	printf("path: %s\n", fi->path);
	printf("term: %d\n", fi->term);
}

void treeAux(FileInfo *fi, void *param){
	
	char *terms[] = {"c", "h", "o"};
	for (int i = 0; i < 3; i++){
		if(!strcmp(&fi->name[(fi->term)+1], terms[i])){
			tAdd(param, terms[i], fi);
		}
	}	
}



void hashAux(FileInfo *fi, void *param){
	
	/*char token[12];
	memset(token, '\0', sizeof(token));
	char* aux = strcpy( malloc( strlen( fi->name ) + 1 ), fi->name );
	strncpy(token, aux, fi->term);
	*/
	char* token;

	token = strtok(fi->name, ".");
	printf("%s\n", token);
	hAdd(param, token, fi);
	//hPrintDebug( param );
	

	//free(token);
	printf("here post aux\n");
}

void setCommand(char *cmdLine, RefArray *original, RefArray *sorted, TNode *rootPtr, HTable *ht) {
	char c = cmdLine[0];
	char word[256]; ///----------------
	switch(c) {
		case 'o':
		case 'O':
			for(int i=0;i<original->count;i++){
                printf("\n");
                printf("path %s\n", original->data[i]->path);
                printf("name %s\n", original->data[i]->name);
                printf("term: %d\n", original->data[i]->term);
                if(strlen(original->data[i]->name)==original->data[i]->term){
					printf("term not found\n");
				}
				else{printf("term found\n");}
				printf("\n");
            }
			break;
        case 'n':
		case 'N':
			for(int i=0;i<sorted->count;i++){
				printf("\n");
                printf("path %s\n", sorted->data[i]->path);
                printf("name %s\n", sorted->data[i]->name);
                printf("term: %d\n", sorted->data[i]->term);
                if(strlen(sorted->data[i]->name)==sorted->data[i]->term){
					printf("term not found\n");
				}
				else{printf("term found\n");}
				printf("\n");
            }
			break;
		case 't':
		case 'T':
			if(sscanf(cmdLine + 1, "%s", word) == 1){ ///----------------
				
				RefArray *found = tSearch(rootPtr, word);
				//printf("sfalkndflkn:  %d\n", found->count);
				if (found){
					//printf("dsdsdsdsd: %s\n", found->data[0]->name);
					refArrScan(found, printRef, NULL);
				}
				
			}
			else
				printf("Please provide a word\n");
			break;
		case 's':
		case 'S':
			if(sscanf(cmdLine + 1, "%s", word) == 1){
				RefArray *aux = hSearch(ht, word);
				printf("sfalkndflkn:  %d\n", aux->count);
				if (aux){
					//printf("dsdsdsdsd: %s\n", found->data[0]->name);
					refArrScan(aux, printRef, NULL);
				}
				//refArrScan(sorted,cmpWordS, rootPtr);
			}
			else
				printf("Please provide a word\n");
			break;
		case 'q':
		case 'Q':
			printf("C Ya!\n");
			
			break;
		default:
			printf("Invalid operation!\n");
	}
}

int main(int argc, char *argv[]){
	
    StrShare *share = strShareCreate();
    RefArray *original = refArrCreate();
    RefArray *sortRef = refArrCreate();
    char *path = ".";

    
    scanDirTree(path,share,original,sortRef);
    
    printf("hellomain\n");
    refArrSort(sortRef);
    
    TNode *root = NULL; // iniciar árvore vazia
    HTable *hashTable = hCreate( 100 );
    
    refArrScan(sortRef, treeAux, &root);
    refArrScan(sortRef, hashAux, hashTable);
    
    tBalance(&root);
    
    char cmd[256];
    
    int toExit = 0;
    do {
		showMenu();
		
		fgets(cmd, 256, stdin);
		char c = cmd[0];
		if(c == 'q' || c == 'Q') toExit = 1;
		setCommand(cmd, original, sortRef, root, hashTable);
		printf("\n");
	} while(!toExit);

    refArrDelete(original);
    refArrDelete(sortRef);
    strShareDelete(share);
    return 0;
}
