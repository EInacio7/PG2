#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define SIZE (sizeof(unsigned long) * CHAR_BIT)        ///tamanho de cada segmento da palavra ( um long )
#define BITMAP_PARTS 256/SIZE                        ///256 bits (desejados)/ tamanho de cada palavra resulta na quantidade de "palavras" que vão constituir a nossa "palavra" principal

typedef unsigned long Set[BITMAP_PARTS];
unsigned long num = 1;


void setPlace (Set set, unsigned value) {
    if ((set[value/SIZE] & (num << (value%SIZE) )) != 0) printf("Já existe.\n"); ///Verefica se o indice value já está preenchido
    else {
        set[value/SIZE] |= (num << value%SIZE); ///OR bit-a-bit
        printf("Array_Indice: %lu | Long_bit: %lu\n", value/SIZE, value%SIZE);
        }
}

void setRemove (Set set, unsigned value) {
    if ((set[value/SIZE] & (num << (value%SIZE))) == 0) printf("Já estava apagado.\n");  ///Verefica se o indice value já está vazio
    else{ 
        set[value/SIZE] &= ~(num << value%SIZE); ///AND bit-a-bit com o complemento da máscara
        printf("Array_Indice: %lu | Long_bit: %lu\nAPAGADO\n", value/SIZE, value%SIZE);
        } 
}

void setUnion( Set set1, Set set2 ){
    for(int i = 0; i < BITMAP_PARTS; i++ ){
      set1[i] |= set2[i];
    }
}

void setIntersect( Set set1, Set set2 ){
    for(int i = 0; i < BITMAP_PARTS; i++ ){
      set1[i] &= set2[i];
    }
}

void setShow(Set set) {
	printf("Conjunto de valores = {");
	for (int i = 0; i <= BITMAP_PARTS-1; ++i) {	
		for (int j = 0; j <= SIZE-1; ++j) {	
			int tmp = j + SIZE * i;	
			if (((set[tmp/SIZE]) & (num << tmp%SIZE)) != 0) printf(" %d", tmp);
		}
	}
	printf(" }\n");
}

int main(){
	Set A = {0};
	Set B = {0};	
	char buffer[256];
	int exit = 0;
	char* set = malloc(sizeof(char*));
	char option;
	long value;
	printf("\t\t\tCONJUNTO DE VALORES\n\n"
		   "Intervalo de valores válido: \t[0, 255]\n"
		   "Comando 'p set val'-place.\n"
		   "Comando 'r set val'-remove. \n"
		   "Comando 'u' - union.\n"
		   "Comando 'i'- intersection.\n"
		   "Comando 's'- show.\n"
		   "Comando 'q'- quit.\n");
		   
		do{
		scanf("%c", &option);
		fgets(buffer, sizeof buffer, stdin);
		switch(option){
			case 'p':
				value = -1;
				sscanf(buffer, "%s %lu",set, &value);
				if (strcmp ("a", set) == 0){
					setPlace(A, value);
				}
				if (strcmp ("b", set) == 0){
					setPlace(B, value);
				}
				printf("\n");
				break;
			case 'r':
				sscanf(buffer, "%s %lu",set, &value);
				if (strcmp ("a", set) == 0){
					setRemove(A, value);
				}
				if (strcmp ("b", set) == 0){
					setRemove(B, value);
				}
				printf("\n");
				break;
			case 'u':
				setUnion(A,B);
				printf("\n");
				break;
			case 'i':
				setIntersect(A,B);
				printf("\n");
				break;
			case 's':
				printf("Valores de A:\n");
				setShow(A);
				printf("Valores de B:\n");
				setShow(B);
				break;	
			case 'q':
				exit = 1;
				printf("\nGoodBye!\n");
				break;				
			}
		
	} while (!exit);
	return 0;
}
