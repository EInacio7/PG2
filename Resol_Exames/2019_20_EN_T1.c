//2019_20_EN_T1
//EX1
//a)
void * insert_elem(void * a, int n_elem, void * elem, size_t el_size) {

void * b = realloc(a, sizeof(a) + 1 + el_size);
//ou realloc(a, sizeof(a) * sizeof(elem));

if (!b) return NULL; 

char * t = ??????;

char * s = elem ;
 
*t++ = 1; // Marcação de que este elemento contém dados.

while (el_size--)

*t++ = *s++; //Cópia, byte a byte, do novo elemento para o novo espaço do array.

 return b ;

}


void invalidate_elem(void * a, int del_index, size_t el_size){
 (char)a[del_index(1+el_size)]=0; // BUT WHYYYYY
} 

//b)
/*
print_array caso o "V" for True printa o elemento (data)

print_elem faz print dos campos i,c e s da estrutura Data apontada pelo ponteiro p fornecido
*/

/* C)
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