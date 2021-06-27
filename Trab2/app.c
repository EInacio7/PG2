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

void setCommand(char *cmdLine, RefArray *original, RefArray *sorted) {
	char c = cmdLine[0];
	char word[256];
	switch(c) {
		case 'o':
		case 'O':
			for(i=0;i<original->count;i++){
                printf(original->data[i]);
            }
			break;
        case 'n':
		case 'N':
			//do something
			break;
		case 't':
		case 'T':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
				//do something
			else
				printf("Please provide a word\n");
			break;
		case 's':
		case 'S':
			if(sscanf(cmdLine + 1, "%s", word) == 1)
				//do something
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