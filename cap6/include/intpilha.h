#ifndef PILHA_INT
#define PILHA_INT

#include <stdlib.h>

typedef struct intList {
    int value;
    struct intList *anterior;
} intPilha;

intPilha *nova_pilha()
{
    intPilha *p = malloc(sizeof(intPilha));
    p -> anterior = NULL;
    p -> value = 0;
    return p;
}

intPilha *empilhar(intPilha *p, int valor)
{
    intPilha *nova = nova_pilha();
    nova -> anterior = p;
    nova -> value = valor;
    return nova;
}

int desempilhar(intPilha **p)
{
    intPilha *temp = *p;
    *p = temp -> anterior;
    int valor = temp -> value;
    free (temp);
    return valor;
}

int vazia(intPilha *p)
{
    return (p -> anterior == NULL) & (p -> value == 0);
}

#endif