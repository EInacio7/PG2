#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aref.h"
#include "strCol.h"
#include "scanTree.h"


int main(int argc, char *argv[]){
    StrShare share = strShareCreate();
    RefArray original = refArrCreate();
    RefArray sorted = refArrCreate();
    char *path = agrv[1];
    scanDirTree(path,share,original,sorted);
    refArrSort(sorted);
    int toExit = 0;
    do {
		showMenu();
		fgets(cmd, BUFF_SIZE, stdin);
		char c = cmd[0];
		if(c == 'q' || c == 'Q') toExit = 1;
		setCommand(cmd, original, sorted);
		printf("\n");
	} while(!toExit);

    refArrDelete(original);
    refArrDelete(sorted);
    strShareDelete(share);
}

void showMenu() {
	printf("Menu:\n");
	printf("o - Displays the file list as originally found.\n");
	printf("n - Display the file list sorted by alphabetical ordering\n");
    printf("t <word> - Displays the file list sorted by specified file extension.\n");
	printf("s <word> - Display the file list with the specified name\n");
	printf("q - Exits program\n");
	printf(">");
}

void cmpword(FileInfo *fi, void *param) {
    char *separador = "->";
    if(fi->name==param){
        printf(strcat(fi->name, strcat(separador, fi->path)));
    }
    if(fi->term==param){
        printf(strcat(fi->name, strcat(separador, fi->path)));
    }
}

void setCommand(char *cmdLine, RefArray *original, RefArray *sorted) {
	char c = cmdLine[0];
	char word[256];
    char *separador="->";
	switch(c) {
		case 'o':
		case 'O':
			for(i=0;i<original->count;i++){
                char* pathPlusName= strcat(original->data[i]->path, strcat(separador, original->data[i]->name))
                if(original->data[i]->term!=NULL){
                    pathPlusName=strcat(pathPlusName, strcat(separador, original->data[i]->term))
                }
                printf(pathPlusName);
            }
			break;
        case 'n':
		case 'N':
			for(i=0;i<sorted->count;i++){
                char* pathPlusName= strcat(sorted->data[i]->path, strcat(separador, sorted->data[i]->name))
                if(sorted->data[i]->term!=NULL){
                    pathPlusName=strcat(pathPlusName, strcat(separador, sorted->data[i]->term))
                }
                printf(pathPlusName);
            }
			break;
		case 't':
		case 'T':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
				refArrScan(sorted,cmpword);// falta aplicar a função como deve ser
			else
				printf("Please provide a word\n");
			break;
		case 's':
		case 'S':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
				refArrScan(sorted,cmpword);// falta aplicar a função como deve ser
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