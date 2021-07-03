#include <stdio.h>
#ifndef STRSHARE_H
#define STRSHARE_H

typedef struct{
    int space; // quantidade de elementos alojados para o array data
    int count; // quantidade de elementos preenchidos
    char **data; // array de ponteiros para as strings existentes
} StrShare;

StrShare *strShareCreate(void);
void strShareDelete(StrShare *share);
char *strSharedAdd( StrShare *share, char *str);
void termSetupTypes( char *terms[], int numTerms );
int termFind ( char *str );

#endif
