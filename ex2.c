#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

//abcd.c

int findTerm( char *str, char *terms[], int numTerms ){
	char *token;
	
	for (int i = 0; i < numTerms; i++){
		token = strtok(str, terms[i]);
		printf("teste\n");
		if (token != NULL &&  str+1 == NULL){
			return strlen(token);
		}
	}
	return strlen(str);
}

int main(void){
	
	char *fileName = "file.c";
	
	char *term[] = {".h", ".c", ".out"};
	
	int res = findTerm(fileName, term, 3);
	
	printf("res: %d\n", res);
	
	return 0;
}
