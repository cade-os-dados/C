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

void no_append_insere_compai(
    noComPai a, noComPai b, noComPai c,
    int v1, int v2
){
    a -> e = b;
    a -> d = c;
    if (b != NULL)
        b -> valor = v1;
    if (c != NULL)
        c -> valor = v2;
}

void no_inserenull_compai(noComPai a)
{
    no_append_insere_compai(a, NULL, NULL, 0, 0);
}

void no_swap(noComPai no1, noComPai no2)
{
    int valor = no1 -> valor;
    no1 -> valor = no2 -> valor;
    no2 -> valor = valor;
}