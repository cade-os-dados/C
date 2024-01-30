#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "include/whitespaces.h"

// 6.1.1
// Suponha que, diferentemente da convenção adotada no texto, a parte do vetor
// ocupada pela pilha é p[0..t]. Escreva o comando que remove um elemento da pilha.
// Escreva o comando que insere um objeto na pilha.

int insere(int p[], int y, int t, int n){
    if (t == n) {
        printf("A pilha esta cheia\n");
        return t;
    } else {
        p[t++] = y;
        return t;
    }
}

int pop(int p[], int *t){
    if (*t == 0) {
        printf("A pilha esta vazia\n");
    }
    else {
        *t = *t-1;
        return p[*t];
    }
}

void print_vetor(int v[], int len){
    printf("< ");
    for (int i = 0; i < len; i++){
        printf("%d ", v[i]);
    }
    printf(">\n");
}

// 6.1.2 INVERSÃO DE PALAVRAS
// Escreva uma função que inverta a ordem das letras de cada palavra de uma sentença,
// preservando a ordem das palavras. Suponha que as palavras da sentença são separadas
// por espaços. A aplicação da operação à sentença AMU MEGASNEM ATERCES, por exemplo, 
// deve produzir UMA MENSAGEM SECRETA.

// obs: não utilizei o conceito de pilha por ser mais vantajoso
// nesse caso fazer swap dos caracteres, mas poderia criar um vetor
// para cada palavra e dar pop no vetor, pegar o valor do pop
// e jogar em outra vetor que estaria ordenado de maneira invertida
// quando a pilha ficasse vazia

celula *inverter(char *mensagem){
    celula *primaria = tokenize(mensagem); // celula com cabeca
    celula *copia = primaria;
    while (copia -> seg != NULL) {
        copia = copia -> seg;
        char *valor = copia -> conteudo;
        // troca as posições i com i-1, até a metade do vetor
        int tamanho = strLen(valor);
        int limite = tamanho / 2;
        for (int i = 1; i <= limite; i++){
            char swap = valor[i-1]; // cache
            valor[i-1] = valor[tamanho-i];
            valor[tamanho-i] = swap;
        }
    }
    return primaria;
}

// 6.1.3 PERMUTAÇÕES PRODUZIDAS PELO DESEMPILHAR
// Suponha que os números inteiros 1, 2, 3, 4 são colocados
// nesta ordem, numa pilha inicialmente vazia. Depois de cada
// operação de empilhar, você pode retirar zero ou mais elementos
// da pilha. Cada número retido da pilha é impresso numa folha
// de papel. Por exemplo, a sequência de operações E, E, D, E, D, D, E, D
// onde E significa "empilhar o próximo número da sequência" e D significa
// "desempilhar", produz a impressão da sequência 2, 3, 1, 4. Quais das 24
// permutações de 1, 2, 3, 4 podem ser obtidas dessa maneira?

int desempilhar(int ordem[], int *resultado){
    int j = 1; int r = 0; int p[4]; int t = 0;
    for (int i = 0; i < 8; i++){
        if (ordem[i] == 1 & t < 5 & j < 5){
            t = insere(p, j, t, 4);
            j++;
        } else {
            if (t != 0) {
                resultado[r] = pop(p, &t);
                r++;
            }
        }
    }
}

void next(int array22[], int left, int right){
    int soma = array22[left] + array22[right];
    switch (soma){
        case 1:
            if (array22[right] == 1) array22[left] = 1; 
            else { array22[left] = 0; array22[right] = 1;}
            break;
        case 2:
            array22[left] = 0; array22[right] = 0;
            break;
        case 0:
            array22[left] = 1; //array22[0] = 0;
            break;
    }
}

void test_next(){
    int array1[2] = {0, 0};
    int array2[2] = {1, 0};
    int array3[2] = {0, 1};
    int array4[2] = {1, 1};

    next(array1, 0, 1); next(array2, 0 , 1); next(array3, 0, 1); next(array4, 0, 1);
    assert(array1[0] == 1); assert(array1[1] == 0);
    assert(array2[0] == 0); assert(array2[1] == 1);
    assert(array3[0] == 1); assert(array3[1] == 1);
    assert(array4[0] == 0); assert(array4[1] == 0);
}

void test2_next(){
    int array1[3] = {0, 0, 0};
    int array2[3] = {0, 1, 0};
    int array3[3] = {0, 0, 1};
    int array4[3] = {0, 1, 1};

    next(array1, 1, 2); next(array2, 1 , 2); next(array3, 1, 2); next(array4, 1, 2);
    assert(array1[1] == 1); assert(array1[2] == 0);
    assert(array2[1] == 0); assert(array2[2] == 1);
    assert(array3[1] == 1); assert(array3[2] == 1);
    assert(array4[1] == 0); assert(array4[2] == 0);
}

void print_permutacoes(int v[], int len, int k) {
    if (k > len - 1 - 2) {
        for (int i = 0; i < 4; i++){
            next(v, len - 2, len - 1);
            print_vetor(v, len); // inserir a logica do programa
        }
    } else {
        print_permutacoes(v, len, k+1);
        v[k] = v[k] ^ 1;
        print_permutacoes(v, len, k+1);
    }
}

// ultima parte: inserir as sequencias em um
// vetor na heap e adicionar um comando para checar se a sequencia
// ja foi inserida

typedef struct sequencia {
    int *ponteiro;
    struct sequencia *next;
} sequencia;

// se a sequencia já existe retorna 0
int verifica_sequencia(int *p, sequencia *primaria, int t, int len){
    sequencia *loop = primaria -> next; // lista com cabeça
    for(int i = 0; i < t; i++){
        int soma = 0;
        // compara todos os valores dos vetores
        for(int j = 0; j < len; j++){
            int valor = loop -> ponteiro[j];
            soma += (valor == p[j]);
        }
        if (soma == len)
            return 0;
        loop = loop -> next;
    }
    return 1;
}

// se ja existir algum vetor na lista ligada, cujos valores
// sejam iguais a p retorna 0, caso contrario insere p na lista e retorna 1
int inserir_sequencia(int *p, sequencia *primaria, int *t, int len){
    int prosseguir = verifica_sequencia(p, primaria, *t, len);
    if (prosseguir){
        sequencia *loop = primaria;
        for (int i = 0; i < *t; i++)
            loop = loop -> next;
        sequencia *nova = malloc(sizeof(sequencia));
        loop -> next = nova;
        nova -> ponteiro = p;
        nova -> next = NULL;
        *t = *t + 1;
        return 1;
    }
    return 0;
}

void print_sequencia(sequencia *primaria, int t, int len){
    printf("(");
    sequencia *loop = primaria -> next; // pular celula cabeça
    for (int i = 0; i < t; i++){
        if (i == 0) printf(" ");
        else printf("  ");
        for (int j = 0; j < len; j++){
            printf("%d ", loop -> ponteiro[j]);
        }
        if (i != t - 1)
        printf("\n");
        loop = loop -> next;
    }
    printf(")\n");
}

int test_sequencia(){
    sequencia *validacao = malloc(sizeof(sequencia));
    validacao -> ponteiro = NULL;
    validacao -> next = NULL;
    int t = 0;
    int vetor1[4] = {1, 2, 3, 4}; int vetor2[4] = {2, 2, 3, 4};
    int vetor3[4] = {3,4,2,1}; int vetor4[4] = {1, 2, 3, 4};

    inserir_sequencia(vetor1, validacao, &t, 4);
    inserir_sequencia(vetor2, validacao, &t, 4);
    inserir_sequencia(vetor3, validacao, &t, 4);
    inserir_sequencia(vetor4, validacao, &t, 4);

    assert(t == 3);
}

void teste_desempilhar(){
    int result[4]; 
    int ordem[8] = {1, 1, 0, 1, 0, 0, 1, 0};
    desempilhar(ordem, result);
    assert(result[0] == 2); assert(result[1] == 3);
    assert(result[2] == 1); assert(result[3] == 4);
}

int valida_sequencia(int sequencia[]){
    int valida = 0;
    for (int i = 0; i < 4; i++){
        if (sequencia[i] < 5 & sequencia[i] > 0)
            valida++;
    }
    if (valida == 4)
        return 1;
    return 0;
}

// nao esta funcionando provavelmente por conta dos vetores serem na stack
// neste caso terei que alocar na heap para que os vetores se perpetuem
void criar_permutacoes(sequencia *primaria, int ordem[], int len, int k, int *t) {
    if (k > len - 1 - 2) {
        for (int i = 0; i < 4; i++){
            next(ordem, len - 2, len - 1);
            int *sequencia = malloc(4 * sizeof(int));
            desempilhar(ordem, sequencia);
            if (valida_sequencia(sequencia))
                inserir_sequencia(sequencia, primaria, t, 4);
        }
    } else {
        criar_permutacoes(primaria, ordem, len, k+1, t);
        ordem[k] = ordem[k] ^ 1;
        criar_permutacoes(primaria, ordem, len, k+1, t);
    }
}

int main(){
    int n = 12; int p[n]; int t = 0;
    pop(p, &t);
    assert(t == 0);
    for (int i=0;i<13;i++) {
        printf("Inserindo: %d. t = %d\n", i % 5, t);
        t = insere(p, i % 5, t, n);
    }
    print_vetor(p, t);
    assert(t == 12);

    int ultimo_valor = pop(p, &t);
    printf("Ultimo valor: %d\n", ultimo_valor);
    assert(t == 11);

    char *m = strdup("AMU MEGASNEM ATERCES");
    celula *mensagem_invertida = inverter(m);
    print_celula(mensagem_invertida);

    test_next();
    test2_next();
    test_sequencia();
    teste_desempilhar();
    
    // inicializa o vetor de permutações
    int iterar[8] = {0, 0, 0, 0, 0, 0, 0, 0}; int t_ = 0;
    sequencia *permutacoes = malloc(sizeof(sequencia));
    criar_permutacoes(permutacoes, iterar, 8, 0, &t_);
    print_sequencia(permutacoes, t, 4);
}