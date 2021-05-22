#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define NUM_TERMS 20

int findTerm( char *str, char *terms[], int numTerms ){
	char *ret;

   	for (int i = 0; i < numTerms; i++){
		ret = strrchr(str, *terms[i]);
		printf("ret: %s\n", ret);
		printf("str:%s\n", &str[strlen(str)]-1);
		if (ret && (str[strlen(str)-1] == *ret)){			//VERIFICAR SE ULTIMA OCORRENCIA É O ULTIMO CHAR DA STRING 
			printf("ret:%s\n", ret);
			printf("token found\n");
			return strlen(str)-strlen(terms[i])-1;
		}
	}
	printf("token not found\n");
	return strlen(str);
}

int main(void){

	char *fileName = malloc(sizeof(char*)+1);
	const char src[NUM_TERMS] = "fileName.c";
	memcpy(fileName, src, sizeof(char)*(NUM_TERMS));
	
	char *term[] = {"c", "h", "o"};
	
	int res = findTerm(fileName, term, 3);
	
	printf("res:%d\n", res);
	
	return 0;
}

