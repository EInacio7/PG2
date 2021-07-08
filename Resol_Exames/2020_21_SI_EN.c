// 2020_21_SI_EN
// EX1
//A) Comentar genericamente o funcionamento de F1


// B) 7 passam a -7 e acresenta 2 7 no fim
//2 -3 1 3 0 4 -7 8 6 -5 -7 1 8 9 5 -9 5 3 0 6 2 -1 9 4 7 7

//C 
int f2(void * e, size_t size_of_item) {
 return *e == ALG;
}
void f3(void * e, size_t size_of_item) { 
  *e = -ALG;
}

void * f1(void *a, size_t *size, size_t size_of_item, int (*fin)(void * e,size_t size_of_item ), void (*fac)(void * e,size_t size_of_item)) {

    size_t i = *size; void *b ;
    
    while(i--)
        if((*fin)(a+ i*size_of_item, size_of_item)){
          
          if((b = realloc(a, (*size + 1) * size_of_item)) == NULL) return b;
          memmove(b+((*size)++ * size_of_item), b+i*size_of_item, size_of_item);
          (*fac)(b+i*size_of_item,size_of_item);
        
        }
    return b;
}



// EX2
// A)
void fileSetAdd( FileSet *ns, FileEntry *fe, PathList *p ){
  ns->count++;
  fe->path = p;
  ns->entrys = realloc(ns->entrys,ns->count++ * sizeof(ns->entrys);
  ns->entrys[ns->count] = fe;
}

// B) 
void fileSetSort( FileSet *ns ){
  qsort(ns->entrys,ns->count,sizeof(FileSet *), comparefunc)
}
//cmp do trabalho - adaptar para o exercicio
int cmpFuncName(const void *p1, const void *p2){
    FileInfo** aa = (FileInfo**) p1;
    FileInfo** bb = (FileInfo**) p2;

	int aux = strcmp((*aa)->name, (*bb)->name);
	if(aux == 0){
		return strcmp((*aa)->path, (*bb)->path);
	}
	return aux;
}


// C) ???

// D) passar para aqui


// EX3

// A)
BstNode *bstAdd( BstNode *r, FileEntry *fe ){
  if(r==NULL){
    BstNode *new=malloc(sizeof(BstNode ));//BstNode *new=malloc(sizeof(* new));
    new->right=new->left = NULL;

    fileSetAdd( new->files, fe);
    return new;
  }
  int aux= strcmp(r->files.entrys[0].name, fe->name);
    if(aux==0) fileSetAdd( r->files, fe);
    else 
      if (aux<0) bstAdd( r->left, fe );
    else bstAdd(r->right, fe);
}

// B)
BstNode *bstBuild( PathList *list ){
PathListOrg(list)
for( PathList *p = list, p!= NULL, p =p->next){
BstNode * r = malloc(sizeof(*r));
r->left=r->right=NULL;
r->files=list->files;
}}

// C)
void bstSelectPrint( BstNode *r, char *name ){
  int aux= strcmp(r->files.entrys[0].name, name);
  if(aux==0){
    for(int i=0; i<r->files->count,i++){
        printf("%s", r-> files. entrys[i]. path. path)
    }
  };
  else if (aux<0) bstSelectPrint( &r->left, name );
  else bstSelectPrint( &r->right, name);
}


// EX4
// A)
/*
demo.o: T main
        U rStart
        U nItems
        U dAdd
        U rEnd
        U dSize
        U dGetIdx
        U print
*/

// B) A função split pode ser static uma vez que apresenta o simbolo t

// C)
/* 
#ifndef _READ_H_
#define _READ_H_
read.h: 
        void rStart(char *);
        Item * rItem();
        void rEnd(void);
        static void split ();
#endif

Quem vai incluir é o read.c e demo.c */

// D) Ver o do Trabalho

