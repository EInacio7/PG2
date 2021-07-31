#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <limits.h>
#include "hash.h"
#include "file.h"

HTable *hCreate( int size ){
	HTable *r = malloc( sizeof *r );
	r->size = size;
	r->table = calloc( size, sizeof(LNode *) ); //contém ponteiros NULL
	return r;
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
	n->name = strcpy( malloc( strlen( data ) + 1 ), data ); //strdup( data );
	
	n->refArr = refArrCreate();
	refArrAdd(n->refArr, ref);
	
	n->next = l;

	return n;

}

static void hLPrint( LNode *l ){
	for( LNode *p = l; p != NULL; p = p->next ){
		printf( "%s \n", p->name );
	}
	putchar( '\n' );
}

static int hash( HTable *ht, char *data ){
	unsigned s = 0;
	for( int i = 0; data[i] != 0; ++i )
		s += data[i] << ( i % (sizeof (int) * CHAR_BIT) );
	return s % ht->size;
}

RefArray *hSearch( HTable *ht, char * name){
	
	int i = hash( ht, name );

	if( hLSearch( ht->table[i], name )){

		return ht->table[i]->refArr;
	}
	else{
		printf("Ficheiro não encontrado\n");
		return NULL;
	}

}

static void hPrintDebug( HTable *ht ){
	for( int i = 0; i < ht->size; ++i ){
		if( ht->table[i] == NULL )
			continue;
		printf( "[%d] \n", i );
		hLPrint( ht->table[i] );
	}
}

void hAdd( HTable *ht, char *name, FileInfo *ref ){

	int i = hash( ht, name );
	
	char *found = hLSearch( ht->table[i], name );
	
	if( found == NULL ){
		ht->table[i] = hLAdd( ht->table[i], name , ref);
	}
	else{
		refArrAdd(ht->table[i]->refArr, ref);
	}
}

void hFree( HTable *ht ){
	
	LNode *in = malloc(sizeof *in);
	
	for( int i = 0; i < ht->size; ++i ){
		
		for( LNode *p = ht->table[i]; p != NULL;){
			
			in = p;
			
			 p = p->next;
			
			free(in);
			
		}
		
	}
	
	free(ht);
	
}
