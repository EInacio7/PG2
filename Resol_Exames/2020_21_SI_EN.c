// 2020_21_SI_EN
// EX1
//A) Comentar genericamente o funcionamento de F1


// B) 7 passam a -7 e acresenta 2 7 no fim
//2 -3 1 3 0 4 -7 8 6 -5 -7 1 8 9 5 -9 5 3 0 6 2 -1 9 4 7 7

//C ??????????

// EX2
// A)
void fileSetAdd( FileSet *ns, FileEntry *fe, PathList *p ){
  ns->count++;
  fe->path = p;
  ns->entrys = realloc(ns_>entrys,sizeof(fe)*count);
  ns->[count] = fe;
}

// B) 
void fileSetSort( FileSet *ns ){
  qsort(ns->entrys,ns->count,sizeof(FileSet *), )
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
#endif

Quem vai invluir é o read.c e demo.c */

// D) Ver o do Trabalho

