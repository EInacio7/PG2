#include <stdio.h>
#include <limits.h>


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