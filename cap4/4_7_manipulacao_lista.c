#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

celula *nova (int init_conteudo, celula *next) {
    celula *new = malloc(sizeof(celula));
    new -> conteudo = init_conteudo;
    new -> seg = next;
    return new;
}

void print_vetor(int v[], int n){
    printf("[ ");
    for (int i=0;i<n;i++){
        printf("%d ", v[i]);
    }
    printf("]\n");
}

void print_celulas(celula *primaria){
    printf("[ ");
    celula *loop = primaria;
    while (loop != NULL) {
        printf("%d ", loop -> conteudo);
        loop = loop -> seg;
    }
    printf("]\n");
}

// 4.7.1 VETOR PARA LISTA
// Escreva uma função que copie um vetor 
// para uma lista encadeada
celula *from_vetor(int v[], int len){
    // primaria para retornar
    celula *primaria = malloc(sizeof(celula));
    primaria -> conteudo = v[0];
    primaria -> seg = malloc(sizeof(celula));

    // popular
    celula *anterior = primaria;
    for (int i=1; i < len; i++){
        anterior = anterior -> seg;
        anterior -> conteudo = v[i];
        celula *nova = malloc(sizeof(celula));
        anterior -> seg = nova;
    }
    anterior -> seg = NULL; // o ultimo elemento apontará para NULL
    return primaria;
}

// 4.7.2 LISTA PARA VETOR
// Escreva uma função que copie uma lista encadeada para um vetor
void to_vec(int v[], celula *primaria){
    celula *temp = primaria;
    int indice = 0;
    while (temp != NULL) {
        v[indice] = temp -> conteudo;
        temp = temp -> seg; indice++;
    }
}

void assert_vector_equal_celula(int vetor[], celula *primaria){
    celula *temp = primaria;
    int indice = 0;
    while(temp != NULL){
        assert (vetor[indice] == temp -> conteudo);
        temp = temp -> seg; indice++;
    }
}

// 4.7.3 COPIA escreva uma função que faça uma cópia 
// de uma lista dada
celula *copia(celula *primaria){
    celula *nova = malloc(sizeof(celula));
    celula *copia_original = primaria;
    celula *copia_nova = nova;
    while (copia_original != NULL){
        copia_nova -> conteudo = copia_original -> conteudo;
        copia_nova -> seg = copia_original -> seg;
        copia_original = copia_original -> seg;
        copia_nova = copia_nova -> seg;
    }
    return nova;
}

// 4.7.4 COMPARAÇÃO Escreva uma função que decida se duas
// listas dadas tem o mesmo conteúdo
void assert_celula_equal(celula *celula1, celula *celula2){
    celula *pointer1 = celula1;
    celula *pointer2 = celula2;
    while (pointer1 != NULL){
        assert (pointer1 -> conteudo == pointer2 -> conteudo);
        pointer1 = pointer1 -> seg;
        pointer2 = pointer2 -> seg;
    }
    assert(pointer2 == 0); // NULL
}

// 4.7.5 CONCATENACAO Escreva uma função que concatene
// duas listas encadeadas (isto é, "amarre" a segunda)
// no fim da primeira
void concatenacao(celula *celula1, celula *celula2){
    celula *temp = celula1;
    while (temp -> seg != NULL)
        temp = temp -> seg;
    temp -> seg = celula2; 
}

// 4.7.6 CONTAGEM Escreva uma função que conte o número
// de células de uma lista encadeada
int contagem(celula *primaria){
    celula *temp = primaria;
    int contagem = 1; // para listas com cabeça seria 0
    while (temp -> seg != NULL){
        temp = temp -> seg;
        contagem++;
    }
    return contagem;
}

// 4.7.7 PONTO MEDIO Escreva uma função que receba uma lista
// encadeada e devolva o endereço de uma célula que esteja
// o mais próximo possível do ponto médio da lista.
// Faça isso sem calcular explicitamente o número n 
// de celulas da lista e o quociente n/2
celula *pontoMedio(celula *primaria){
    celula *passa_um = primaria;
    celula *passa_dois = primaria;
    while (passa_dois != NULL && passa_dois -> seg != NULL){
        passa_um = passa_um -> seg;
        passa_dois = passa_dois -> seg -> seg;
    }
    return passa_um;
}

// 4.7.8 CONTAGEM E REMOÇÃO Escreva uma função
// que remova a k-ésima célula de uma lista encadeada
void removeByIndex(celula *primaria, int indice){
    int contagem = 0;
    celula *loop = primaria;
    while (contagem != indice-1){
        loop = loop -> seg;
        contagem++;
    }
    celula *remover = loop -> seg;
    loop -> seg = remover -> seg;
    free(remover);
}

// 4.7.9 CONTAGEM E INSERÇÃO Escreva uma função
// que insira uma nova célula com conteúdo x
// entre a k-ésima e a (k+1)-ésima células
// de uma lista encadeada

int main(){
    // vec to celula
    int v[8] = {1,2,3,4,5,6,7,8};
    celula *new = from_vetor(v, 8);
    assert_vector_equal_celula(v, new);

    // celula to vec
    int vetor[8];
    to_vec(vetor, new);
    assert_vector_equal_celula(vetor, new);

    // copia
    celula *copiada = copia(new);
    assert_celula_equal(new, copiada);

    // concatenacao
    int v1[5] = {1,2,3,4,5};
    int v2[3] = {6,7,8};
    celula *celula1 = from_vetor(v1, 5);
    celula *celula2 = from_vetor(v2, 3);
    concatenacao(celula1, celula2);

    // contagem
    celula *assertion_cel = from_vetor(v, 8);
    assert_celula_equal(celula1, assertion_cel);

    int len = contagem(celula1);
    assert(len == 8);

    // contagem apos concatenacao
    celula *celula3 = nova(9, NULL);
    concatenacao(celula1, celula3);
    len = contagem(celula1);
    assert(len == 9);

    // ponto medio
    celula *medio = pontoMedio(celula1);
    assert(medio -> conteudo == 5);

    // remocao por indice
    removeByIndex(celula1, 1);
    assert(celula1 -> seg -> conteudo == 3);

    // garantir que a lista diminuiu de tamanho
    len = contagem(celula1);
    assert(len == 8);

    // passou nos testes
    printf("OK");
}