#include <stdio.h>
#ifndef STRSHARE_H
#define STRSHARE_H
#ifndef FILEINFO_H
#define FILEINFO_H
#ifndef REFARRAY_H
#define REFARRAY_H

typedef struct{
    int space; // quantidade de elementos alojados para o array data
    int count; // quantidade de elementos preenchidos
    char **data; // array de ponteiros para as strings existentes
} StrShare;

typedef struct {
   char *path; // string partilhada - localização do ficheiro
   char *name; // string alojada dinamicamente - nome completo
   int term; // posição da terminação no nome
} FileInfo;

typedef struct {
    int space; // quantidade de elementos alojados para o array data
    int count; // quantidade de elementos preenchidos
    FileInfo **data; // array de ponteiros
} RefArray;

StrShare *strShareCreate(void);
void strShareDelete(StrShare *share);
char *strSharedAdd( StrShare *share, char *str);

#endif