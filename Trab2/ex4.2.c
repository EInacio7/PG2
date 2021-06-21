#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char *termsGlob[] = {};
int numTermsGlob= 0;

void termSetupTypes( char *terms[], int numTerms ){
  for (int i = 0; i < numTerms; i++){
      termsGlob[i] = terms[i];
  }
  numTermsGlob=numTerms;
}

int termFind ( char *str ){
  
}