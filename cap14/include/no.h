#pragma once
#include <stdlib.h>

typedef struct cel
{
    int valor;
    struct cel* e;
    struct cel* d;
} arvore;

typedef struct cel* no;

void no_append(no node, no e, no d);
void no_malloc_child(no node);
void no_append_child_null(no node);