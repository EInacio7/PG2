#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

// && str+1 == NULL

int findTerm( char *str, char *terms[], int numTerms ){
	char *token;
	char p = '.';
	char *aux = malloc(sizeof(char*));
	
	token = strtok(str, &p);
	strcpy(aux,token);
	token = strtok(NULL, "\0");
	
	for (int i = 0; i < numTerms; i++){

		if (token){
			if(strcmp(token, terms[i]) == 0){
				printf("token found\n");
				return strlen(aux);
			}
		}
	}
	printf("token not found\n");
	return strlen(str);
}

int main(void){
	
	char *fileName = malloc(sizeof(char*));
	const char src[10] = "faaf.fes.c";
	memcpy(fileName, src, sizeof(char)*100);
	
	char *term[] = {"c", "h", "k"};
	
	int res = findTerm(fileName, term, 3);
	
	printf("res:%d\n", res);
	
	return 0;
}

