#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TITLE 20

int findTerm( char *str, char *terms[], int numTerms ){
	char *ret;

   	for (int i = 0; i < numTerms; i++){
		ret = strrchr(str, *terms[i]);
		if (ret && (str[strlen(str)-strlen(terms[i])] == *ret)){			//VERIFICAR SE ULTIMA OCORRENCIA É O ULTIMO CHAR DA STRING 
			printf("token found\n");
			return strlen(str)-strlen(terms[i])-1;
		}
	}
	printf("token not found\n");
	return strlen(str);
}

int main(void){
	char *fileName = malloc(sizeof(char*)+1);
	const char src[MAX_TITLE] = "filecName.h";
	memcpy(fileName, src, sizeof(char)*(MAX_TITLE));
	
	char *term[] = {"c", "h", "out"};
	
	int res = findTerm(fileName, term, 3);
	
	printf("res:%d\n", res);
	
	return 0;
}

