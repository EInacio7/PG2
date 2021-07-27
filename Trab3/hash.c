#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <limits.h>
#include "hash.h"
#include "file.h"

static int hash( HTable *ht, char *data ){
	unsigned s = 0;
	for( int i = 0; data[i] != 0; ++i )
		s += data[i] << ( i % (sizeof (int) * CHAR_BIT) );
	return s % ht->size;
}

static char *hLSearch( LNode *l, char *data ){
	
	for( LNode *p = l; p != NULL; p = p->next ){
		if( strcmp( p->name, data ) == 0 )
			return p->name;
	}
	return NULL;
}

static LNode *hLAdd( LNode *l, char *data, FileInfo *ref  ){
	
	LNode *n = malloc( sizeof *n );
	
	n->refArr = refArrCreate();
	refArrAdd(n->refArr, ref);
	n->name = strcpy( malloc( strlen( data ) + 1 ), data ); //strdup( data );
	//n->name = strdup(data);
	
	n->next = l;
	
	printf("here post hLAdd\n");
	return n;
}

HTable *hCreate( int size ){
	HTable *r = malloc( sizeof *r );
	r->table = calloc( size, sizeof(LNode *) ); //contém ponteiros NULL
	r->size = size;
	return r;
}

void hAdd( HTable *ht, char *name, FileInfo *ref ){
	int i = hash( ht, name );
	printf("rebenta\n");
	//char *found = hLSearch( ht->table[i], name );
	
	char *found = malloc(sizeof(char*)*500);
	found = hLSearch( ht->table[i], name );
	
	if( found == NULL ){
		ht->table[i] = hLAdd( ht->table[i], name , ref);
	}
	
	printf("here post hAdd\n");
}

RefArray *hSearch( HTable *ht, char * name){
	int i = hash( ht, name );
	//return hLSearch( ht->table[i], name );
	
	
	if( hLSearch( ht->table[i], name ) != NULL ){
		return ht->table[i]->refArr;
	}
	return NULL;
	
	/**char *found = hLSearch( ht->table[i], name );
	
	if( found != NULL ){
		return ht->table[i]->refArr;
	}
	else{
		return NULL;
	}**/
}

static void freeList (LNode *head) {
	if (head != NULL) {
		freeList(head->next);
		free(head);
	}
}

void hFree( HTable *ht ){
	/*for(int i = 0; i < 256; i++) {
		freeList(ht->table[i]);
		free(ht->table);
	}*/

	
	if(ht == NULL) return;
	if(ht->table != NULL) {
		for(int i = 0; i < 256; i++) {
			LNode *it = ht->table[i], *aux;
			while(it) {
				free(it->name);
				aux = it;
				it = it->next;
				free(aux);
				refArrDelete(it->refArr);
			}
		}
		free(ht->table);
	}
	free(ht);
}
