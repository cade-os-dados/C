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

/* Transformar uma array em uma árvore binária */
noComPai from_array(int v[], int n)
{
    int esquerda = 1; int idx = 0;
    int t = sizeof(arvoreComPai);
    noComPai arv = malloc(t);
    noComPai loop = arv;

    while(idx < n)
    {
        loop -> valor = v[idx];
        if(esquerda)
        {
            loop -> e = malloc(t);
            loop -> e -> pai = loop;
            loop = loop -> e;
            loop -> e = loop -> d = NULL;
            esquerda = 0;
        }
        else
        {
            loop = loop -> pai;
            loop -> d = malloc(t);
            loop -> d -> pai = loop;
            loop = loop -> d;
            loop -> e = loop -> d = NULL;
            esquerda = 1;
        }
        idx++;
    }
    if(esquerda)
        loop -> pai -> d = NULL;
    else
        loop -> pai -> e = NULL;

    arv -> pai = NULL;
    free(loop);
    return arv;
}

void print_arvore(noComPai arvore)
{
    if (arvore != NULL)
    {
        printf("%d ", arvore -> valor);
        print_arvore(arvore -> e);
        print_arvore(arvore -> d);
    }
}

void print_no(noComPai arv)
{
    printf("{ ");
    print_arvore(arv);
    printf("}\n");
}

noComPai newcp(int valor)
{
    noComPai node = malloc(sizeof(arvoreComPai));
    node->e = NULL;
    node->d=NULL;
    node->pai=NULL;
    node->valor=valor;
    return node;
}