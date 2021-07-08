//2019_20_EN_T1
//EX1
//a)
void * insert_elem(void * a, int n_elem, void * elem, size_t el_size) {

void * b = realloc(a,  (n_elem+1)*(1+el_size);

if (!b) return NULL; 

char * t = b*(n_elem*(el_size+1));

char * s = elem ;
 
*t++ = 1; // Marcação de que este elemento contém dados.

while (el_size--)

*t++ = *s++; //Cópia, byte a byte, do novo elemento para o novo espaço do array.

 return b ;

}


void invalidate_elem(void * a, int del_index, size_t el_size){
 (char)a[del_index(1+el_size)]=0; 
};

//b)
/*
print_array caso o "V" for True printa o elemento (data)

print_elem faz print dos campos i,c e s da estrutura Data apontada pelo ponteiro p fornecido
*/

/* 
0, 'A', "msg0"
1, 'B', "msg1"
2, 'C', "msg2"
3, 'D', "msg3"
4, 'E', "msg4"
---
1, 'B', "msg1"
---
3, 'D', "msg3"
---
*/

// C)
void *compress ()





// EX2
// A)
LnodeLoc *locInsert( LnodeLoc *h, int page ){
  LnodeLoc *n= malloc(sizeof *n);
  n->page=page;
  LnodeLoc *p,*a;
   if(*h == NULL)
         *h = n;
  for( p = *h; p != NULL && page > p->page; a = p, p = p->next);
   if(a->page==page) return h
    n->next = p;
      if( p == *h ) 
            *h = n;
            return h
      else
            a->next = n;
}
    






// B)

LnodeWord  *wordInsert( LnodeWord *h, const char * word, int page ){
  LnodeWord *n= malloc(sizeof *n);
  n->word=strdup(word);
  LnodeWord *p
   for( p = *h; p != NULL ;  p = p->next){
     if (strcmp(p->word,word)==0) {
       locInsert(p->locHead,page); return h;)}
   }
   locInsert(n->locHead,page)


}