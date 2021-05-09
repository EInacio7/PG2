#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef DT_DIR
# define DT_UNKNOWN	0
# define DT_FIFO	1
# define DT_CHR		2
# define DT_DIR		4
# define DT_BLK		6
# define DT_REG		8
# define DT_LNK		10
# define DT_SOCK	12
# define DT_WHT		14
#endif

int main(){
	DIR* d = opendir(".");
	struct dirent * de;
	while( ( de = readdir( d ) ) != NULL ){
		char *str;
		switch( de->d_type ){
		case DT_FIFO:
			str = "Named pipe (FIFO)";
			break;
		case DT_CHR:
			str = "Character device";
			break;
		case DT_DIR:
			str = "Directory";
			break;
		case DT_BLK:
			str = "Block device";
			break;
		case DT_REG:
			str = "Regular file";
			break;
		case DT_LNK:
			str = "Symbolic link";
			break;
		case DT_SOCK:
			str = "UNIX domain socket";
			break;
		default:
			str = "Unknown type";
		}
		printf( "%s\t[%s]\n", de->d_name, str );
	}
	closedir( d ); 
	return 0;
}
