#include "no.h"

void no_append(no node, no e, no d)
{
    node -> e = e;
    node -> d = d;
}

void no_malloc_child(no node)
{
    no e = malloc(sizeof(arvore));
    no d = malloc(sizeof(arvore));
    no_append(e, NULL, NULL);
    no_append(d, NULL, NULL);
    no_append(node, e, d);
}

void no_append_child_null(no node)
{
    no_append(node, NULL, NULL);
}