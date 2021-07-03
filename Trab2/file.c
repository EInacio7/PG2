#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "strCol.h"
char *terms[] = {"c", "h", "o", "txt"};	

FileInfo *fileInfoNew( char *sharedPath, char *name ){
	FileInfo *fi = malloc(sizeof(FileInfo));
	fi->path = strcpy( malloc( strlen( sharedPath ) + 1 ), sharedPath );
	fi->name =  strcpy( malloc( strlen( name ) + 1 ), name );//strdup( name );
	termSetupTypes(terms, 4);
	fi->term = termFind(name);
	return fi;
}

void fileInfoDelete( FileInfo *info ){
	free(info->path);
	free(info->name);
    free(info);
}
