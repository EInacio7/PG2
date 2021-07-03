#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strCol.h"

char **termsGlob = NULL;
int numTermsGlob= 0;

void termSetupTypes( char *terms[], int numTerms ){
  /*for (int i = 0; i < numTerms; i++){
      termsGlob[i] = terms[i];
  }*/
  termsGlob=terms;
  numTermsGlob=numTerms;
}

int termFind ( char *str ){
  	char *ret;

   	for (int i = 0; i < numTermsGlob; i++){
		ret = strrchr(str, *termsGlob[i]);
		if (ret && (str[strlen(str)-strlen(termsGlob[i])] == *ret)){			//verificar se a ocurrencia encontrada corresponde ao ultimo char da string
			return strlen(str)-strlen(termsGlob[i])-1;							//retornar o comprimento do nome do ficheiro subtraindo o comprimento do term encontrado e o ponto
		}
	}
	return strlen(str);		
}
