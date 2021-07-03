#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aref.h"
#include "strCol.h"
#include "scanTree.h"


void showMenu() {
	printf("Menu:\n");
	printf("o - Displays the file list as originally found.\n");
	printf("n - Display the file list sorted by alphabetical ordering\n");
    printf("t <word> - Displays the file list sorted by specified file extension.\n");
	printf("s <word> - Display the file list with the specified name\n");
	printf("q - Exits program\n");
}

void cmpword(FileInfo *fi, void *param) {
    if(fi->name==param){
        //printf(strcat(fi->name, strcat(separador, fi->path)));
        printf("Name: %s Path: %s\n",fi->name, fi->path);
    }
    /*if(fi->term==param){
        printf("Name: %s Path: %s",fi->name, fi->path);
    }*/
}

void setCommand(char *cmdLine, RefArray *original, RefArray *sorted) {
	char c = cmdLine[0];
	char word[256];
    //char *separador="->";
	switch(c) {
		case 'o':
		case 'O':
			for(int i=0;i<original->count;i++){
                //char* pathPlusName= strcat(original->data[i]->path, strcat(separador, original->data[i]->name));
                /*if(original->data[i]->term!=0){
                    pathPlusName=strcat(pathPlusName, strcat(separador, original->data[i]->term));
                }
                printf(pathPlusName);*/
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
                //char* pathPlusName= strcat(sorted->data[i]->path, strcat(separador, sorted->data[i]->name));
                /*if(sorted->data[i]->term!=NULL){
                    pathPlusName=strcat(pathPlusName, strcat(separador, sorted->data[i]->term));
                }
                printf(pathPlusName);*/
            }
			break;
		case 't':
		case 'T':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
			for(int i=0;i<sorted->count;i++){
				if(!strcmp(&sorted->data[i]->name[(sorted->data[i]->term)+1], word)){
					printf("\n");
					printf("path %s\n", sorted->data[i]->path);
					printf("name %s\n", sorted->data[i]->name);
					printf("term: %d\n", sorted->data[i]->term);
				}
				//refArrScan(sorted,cmpword, word);// falta aplicar a função como deve ser
			}
			else
				printf("Please provide a word\n");
			break;
		case 's':
		case 'S':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
			for(int i=0;i<sorted->count;i++){
				char* token;
				char* aux = strcpy( malloc( strlen( sorted->data[i]->name ) + 1 ), sorted->data[i]->name );
				token = strtok(aux, ".");
				if(!strcmp(token, word)){
					printf("\n");
					printf("path %s\n", sorted->data[i]->path);
					printf("name %s\n", sorted->data[i]->name);
					printf("term: %d\n", sorted->data[i]->term);
				}
			}
				//refArrScan(sorted,cmpword, word);// falta aplicar a função como deve ser
			else
				printf("Please provide a word\n");
			break;
		case 'q':
		case 'Q':
			printf("Exiting...\n");
			///toExit=1;
			break;
		default:
			printf("Invalid operation!\n");
	}
}

int main(int argc, char *argv[]){
	
    StrShare *share = strShareCreate();
    RefArray *original = refArrCreate();
    RefArray *sorted = refArrCreate();
    char *path = ".";
    
    //FileInfo *found;
    
    scanDirTree(path,share,original,sorted);
    //list_dir(path);
    printf("hello\n");
    refArrSort(sorted);
    char cmd[256];
    //char c;
    int toExit = 0;
    do {
		showMenu();
		//scanf("%c", &c);
		fgets(cmd, 256, stdin);
		char c = cmd[0];
		if(c == 'q' || c == 'Q') toExit = 1;
		setCommand(cmd, original, sorted);
		printf("\n");
	} while(!toExit);

    refArrDelete(original);
    refArrDelete(sorted);
    strShareDelete(share);
    return 0;
}
