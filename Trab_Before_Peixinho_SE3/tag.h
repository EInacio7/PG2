#ifndef _TAG_H
#define _TAG_H

#include "tagtype.h"
#include "strset.h"

MP3Tag_t *tagRead(char *, int *, StrSet_t *);
void tagDelete(MP3Tag_t *);

#endif