#include <stdio.h>

#ifndef FILEINFO_H
#define FILEINFO_H

typedef struct {
   char *path; // string partilhada - localização do ficheiro
   char *name; // string alojada dinamicamente - nome completo
   int term; // posição da terminação no nome
} FileInfo;

FileInfo *fileInfoNew( char *sharedPath, char *name );
void fileInfoDelete( FileInfo *info );
#endif
