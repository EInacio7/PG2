#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "strCol.h"
#include "file.h"
#include "aref.h"


void scanDirTree( char *path, StrShare *pathShare, RefArray *origRef, RefArray *sortRef ){

    DIR* d = opendir(path);
    struct dirent * de;
    int files = 0;
	strShareAdd(pathShare, path);
	char *barra = "/";
	while(( de = readdir( d ) ) != NULL ){
		if(de->d_type == 4){
			scanDirTree(strcat(strcat(path, barra), de->d_name), pathShare, origRef, sortRef);
		}
		if(de->d_type == 8){
			FileInfo *file = fileInfoNew(path, de->d_name);
			refArrAdd(origRef, file);
			refArrAdd(sortRef, file);			
		}
		
       
	}
	closedir(d);
}
