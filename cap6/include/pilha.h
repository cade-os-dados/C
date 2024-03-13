#ifndef PILHA
#define PILHA

#include <stdlib.h>

typedef struct charList {
    char value;
    struct charList *anterior;
} stack;

stack *nova_pilha()
{
    stack *p = malloc(sizeof(stack));
    p -> anterior = NULL;
    p -> value = '\0';
    return p;
}

stack *empilhar(stack *p, char valor)
{
    stack *nova = nova_pilha();
    nova -> anterior = p;
    nova -> value = valor;
    return nova;
}

// esta função recebe uma referência ao ponteiro p
// para que possa modificá-lo
// e retorna o último valor da pilha, 
// liberarando seu ponteiro
char desempilhar(stack **p)
{
    stack *temp = *p;
    *p = temp -> anterior;
    char valor = temp -> value;
    free (temp);
    return valor;
}

int vazia(stack *p)
{
    return (p -> anterior == NULL) & (p -> value == '\0');
}

#endif