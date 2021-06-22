#include <stdio.h>
#include "file.h"
#ifndef REFARRAY_H
#define REFARRAY_H


typedef struct {
    int space; // quantidade de elementos alojados para o array data
    int count; // quantidade de elementos preenchidos
    FileInfo **data; // array de ponteiros
} RefArray;

#endif
