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
    celula *loop = fila;
    while (loop -> seg != NULL){
        loop = loop -> seg;
    }
    return loop;
}

void push(celula *fila, int y){
    celula *nova = malloc(sizeof(celula));
    celula *t = find_t(fila);
    t -> seg = nova;
    nova -> seg = NULL;
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
    while (loop != NULL){
        printf("%d ", loop->valor);
        loop = loop -> seg;
    }
    printf(">");
}

// 5.4.2 Implemente uma fila em uma lista encadeada circular
// com célula-cabeça. O primeiro elemento da fila ficará na segunda célula
// e o último elemento ficará na célula anterior à cabeça
// Para manipular a fila basta conhecer o endereço ff da célula-cabeça
celula *find_t_circular(celula *fila){
    celula *loop = fila;
    while (loop -> seg != fila && loop -> seg != NULL){
        loop = loop -> seg;
    }
    return loop;
}

void push_circular(celula *fila, int y){
    celula *nova = malloc(sizeof(celula));
    celula *t = find_t_circular(fila);
    t -> seg = nova;
    nova -> seg = fila;
    nova -> valor = y;
}

void pop_circular(celula *fila){
    celula *s = fila -> seg;
    fila -> seg = s -> seg;
    free(s);
}

void printFilaSemCabecaCircular(celula *fila){
    celula *loop = fila -> seg;
    printf("< ");
    while (loop != fila){
        printf("%d ", loop->valor);
        loop = loop -> seg;
    }
    printf(">");
}

// 5.4.3 Implemente uma fila em uma lista duplamente encadeada
// sem célula cabeça. Mantenha um ponteiro para a primeira célula
// e um ponteiro para última.
typedef struct celula_duplamente_encadeada {
    int valor;
    struct celula_duplamente_encadeada *next;
    struct celula_duplamente_encadeada *previous;
} dupla;

// primeira <- -> ultima
// caso 0 primeira = ultima
// primeira -> previous = NULL
// add := ultima = ultima + 1

// cria uma fila
dupla *init(int y){
    dupla *primeira = malloc(sizeof(dupla));
    primeira -> next = NULL;
    primeira -> previous = NULL;
    primeira -> valor = y;
    return primeira;
}

dupla *add(dupla *ultima, int y){
    dupla *nova = malloc(sizeof(dupla));
    nova -> valor = y;
    nova -> previous = ultima;
    ultima -> next = nova;
    nova -> next = NULL;
    return nova;
}

dupla *remover(dupla *primeira){
    dupla *proxima = primeira -> next;
    if (proxima != NULL) 
        proxima -> previous = NULL;
    free (primeira);
    return proxima;
}

void print_dupla(dupla *primeira){
    dupla *loop = primeira;
    printf("< ");
    while (loop != NULL){
        printf("%d ", loop->valor);
        loop = loop -> next;
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

    celula *fila_circular = malloc(sizeof(celula));
    fila_circular -> seg = NULL;
    push_circular(fila_circular, 12);
    push_circular(fila_circular, 15);
    printFilaSemCabecaCircular(fila_circular);
    pop_circular(fila_circular);
    printFilaSemCabecaCircular(fila_circular);

    dupla *primeira = init(5);
    dupla *ultima = add(primeira, 12);
    ultima = add(ultima, 15);
    print_dupla(primeira);
    primeira = remover(primeira);
    print_dupla(primeira);
}