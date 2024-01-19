// implementação circular
// quando não sabemos no inicio do programa qual será o tamanho da lista
# include<stdlib.h>
# include<stdio.h>

typedef struct cel {
    int valor;
    struct cel *seg;
} celula;

// implementação em lista sem cabeça
// dada pelo livro
int Remove (celula **es, celula **et){
    celula *p;
    int x;
    p = *es;
    x = p->valor;
    *es = p -> seg;
    free (p);
    if (*es == NULL) *et = NULL;
    return x;
}

void Insere (int y, celula **es, celula **et){
    celula *nova;
    nova = malloc(sizeof(celula));
    nova -> valor = y;
    nova -> seg = NULL;
    if (*et == NULL) *et = *es = nova;
    else {
        (*et) -> seg = nova;
        *et = nova;
    }
}

void printFila(celula *es, celula *et){
    celula *loop = es;
    printf("< ");
    while (loop != et->seg){
        printf("%d ", loop->valor);
        loop = loop -> seg;
    }
    printf(">");
}

// 5.4.1 Implemente uma fila em uma lista encadeada com célula-cabeça
celula *find_t(celula *fila){
    celula *x = fila;
    celula *loop = fila;
    while (loop -> seg != x && loop -> seg != NULL){
        loop = loop -> seg;
    }
    return loop;
}

void push(celula *fila, int y){
    celula *nova = malloc(sizeof(celula));
    celula *t = find_t(fila);
    t -> seg = nova;
    nova -> seg = fila;
    nova -> valor = y;
}

void pop(celula *fila){
    celula *s = fila -> seg;
    fila -> seg = s -> seg;
    free(s);
}

void printFilaSemCabeca(celula *fila){
    celula *loop = fila -> seg;
    printf("< ");
    while (loop != fila){
        printf("%d ", loop->valor);
        loop = loop -> seg;
    }
    printf(">");
}


int main() {
    celula *s, *t;
    s = t = NULL;
    Insere(5, &s, &t);
    Insere(15, &s, &t);
    Insere(10, &s, &t);
   
    printFila(s, t);
    // printf("%d\n", s->valor);
    // printf("%d\n", s->seg->valor);

    celula *fila = malloc(sizeof(celula));
    fila -> seg = NULL;
    push(fila, 12);
    push(fila, 15);
    printFilaSemCabeca(fila);
    pop(fila);
    printFilaSemCabeca(fila);
}