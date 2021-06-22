#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "strCol.h"


FileInfo *fileInfoNew( char *sharedPath, char *name ){
	FileInfo *fi = malloc(sizeof(FileInfo));
	fi->path = sharedPath;
	fi->name = strdup( name );
	fi->term = termFind(sharedPath);
	return fi;
}

void fileInfoDelete( FileInfo *info ){
	free(info->path);
	free(info->name);
    free(info);
}
