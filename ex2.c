#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

/**int findTerm( char *str, char *terms[], int numTerms ){
	char *token;
	char p = '.';
	char *aux = malloc(sizeof(char*));
	char* copy = malloc(sizeof(char*));
	strcpy(copy, str);
	
	int count = 0;

	for (int i = 0; i < strlen(str); i++){
		token = strtok(str, &p);
		if (token != NULL){
			count++;
		}
	}
	printf("count: %d\n", count);
///	
	token = strtok(str, &p);
	strcpy(aux,token);
	token = strtok(NULL, "\0");
///
	for (int i = 0; i < numTerms; i++){

		if (token){
			if(strcmp(token, terms[i]) == 0){
				printf("token found\n");
				return strlen(aux);
			}
		}
	}
	printf("token not found\n");
	return strlen(copy);
}**/

/**int findTerm( char *str, char *terms[], int numTerms ){
	char p = '.';
	char *ret;

   ret = strrchr(str, p);

   	for (int i = 0; i < numTerms; i++){
		//ret = strrchr(str, *terms[i]);
		//printf("res: %s\n", ret);
		if (ret){
			if(strcmp(ret, terms[i]) == 0){
				printf("token found\n");
				return strlen(str)-strlen(ret);
			}
		}
	}
	printf("token not found\n");
	return strlen(str);
}**/

int findTerm( char *str, char *terms[], int numTerms ){
	char *ret;

   	for (int i = 0; i < numTerms; i++){
		ret = strrchr(str, *terms[i]);
		printf("ret: %s\n", ret);
		printf("str:%s\n", &str[strlen(str)]-1);
		//if (ret && (ret[strlen(ret)-1] == '\0')){			//VERIFICAR SE ULTIMA OCORRENCIA É O ULTIMO CHAR DA STRING MAS ESTA MAL FEITO
		if (ret && (str[strlen(str)-1] == *ret)){			//VERIFICAR SE ULTIMA OCORRENCIA É O ULTIMO CHAR DA STRING MAS BEM FEITO?
			printf("ret:%s\n", ret);
			printf("token found\n");
			return strlen(str)-strlen(terms[i])-1;
		}
	}
	printf("token not found\n");
	return strlen(str);
}

int main(void){
	//PERGUNTAR SE +1 NECESSARIO EM MALLOC
	char *fileName = malloc(sizeof(char*)+1);
	const char src[SIZE] = "fileName.c";
	memcpy(fileName, src, sizeof(char)*(SIZE));
	
	char *term[] = {"c", "h", "o"};
	
	int res = findTerm(fileName, term, 3);
	
	printf("res:%d\n", res);
	
	return 0;
}

