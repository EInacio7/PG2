#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listfiles.h"
#include "setdata.h"

#define BUFF_SIZE 256

void showUsage();
void showMenu();

int main(int argc, char **argv) {
	if(argc != 2) {
		showUsage();
		exit(EXIT_SUCCESS);
	}
	
	TagSet_t *set = setCreate();
	StrSet_t *sSet = strSetCreate();
	char *listName = argv[1];
	listScan(listName, set, sSet);
	
	char cmd[BUFF_SIZE];
	int toExit = 0;
	do {
		showMenu();
		fgets(cmd, BUFF_SIZE, stdin);
		char c = cmd[0];
		if(c == 'q' || c == 'Q') toExit = 1;
		setCommand(set, cmd);
		printf("\n");
	} while(!toExit);

	setDelete(set);
	strSetDelete(sSet);
  
	return 0;
}

void showUsage() {
	printf("app <fileName>\n");
	printf("\t<fileName> - Text file with a list of MP3 file names\n\n");
}

void showMenu() {
	printf("Menu:\n");
	printf("a - Displays the song list sorted by artist name\n");
	printf("t - Displays the song list sorted by song title\n");
	printf("s <word> - Display the songs with the specified word\n");
	printf("q - Exits program\n");
	printf(">");
}