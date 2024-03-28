#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/* 7.8.1 OUTRA FORMULAÇÃO DA BUSCA BINÁRIA. Escreva uma versão
* da busca binária que receba um inteiro x e um vetor v[0..n-1]
* e devolva j tal que em v[j-1] <= x < v[j] (note a posição de "<=" e "<").
* Quais os possíveis valores de j? */

/* R: j E [0,n] */
int BuscaBinariaR(int x, int e, int d, int v[]){
    if (e == d-1) return d;
    else {
        int m = (e+d)/2;
        if (v[m] <= x)
            return BuscaBinariaR(x, m, d, v);
        else
            return BuscaBinariaR(x, e, m, v);
    }
}

int BuscaBinaria(int x, int n, int v[]){
    if (v[n-1] < x) return n;
    if (x <= v[0]) return 0;
    return BuscaBinariaR(x, 0, n-1, v);
}

/* 7.8.2 VETOR DECRESCENTE. Escreva uma versão da busca
* binária para resolver o seguinte problema: dado um 
* inteiro x e um vetor decrescente v[0..n-1], encontrar
* j tal que v[j-1] > x >= v[j] */
int BuscaBinariaDecrescente(int x, int n, int v[]){
    int e = 0, d = n-1;
    if (x > v[e]) return e;
    if (x < v[d]) return d;

    while (e < d-1){
        int m = (e+d)/2;
        if (x < v[m]) e = m;
        else d = m;
    }
    return d;
}

/* 7.8.3 BUSCA SIMPLIFICADA. Escreva uma função que
* resolva o problema formulado na introdução do capítulo:
* ao receber um inteiro x e um vetor crescente v[0..n-1],
* devolva um índice m tal que v[m] = x ou devolva -1 se 
* tal m não existe. Escreva duas versões: uma iterativa
* e uma recursiva. */

int BuscaBinariaEfetiva(int x, int n, int v[]){
    int e = 0, d = n-1;

    while (e < d-1){
        int m = (e+d)/2;
        int valor = v[m];
        if (x == valor) return m;
        else if (x > valor) e = m;
        else d = m; 
    }
    return -1;
}

/* 7.8.4 VETOR DE STRINGS. Suponha que cada elemento
* do vetor v[0..n-1] é uma string. Suponha também
* que o vetor está em ordem lexicográfica (veja Seção G.3).
* Escreva uma função que receba uma string x e devolva
* um índice j tal que x é igual a v[j]. Se tal j não existe,
* a função deve devolver -1 */

int busca_string(char find[], char **string, int n){
    int e = 0, d = n;
    while (e < d){
        int m = (e+d)/2;
        int comparacao = strcmp(find, string[m]);
        if (comparacao == 0)
            return m;
        else if (comparacao > 0)
            e = m;
        else
            d = m;
    }
    return -1;
}

/* 7.8.5 VETOR DE STRUCTS. Suponha que cada elemento do vetor v[0..n-1]
* é uma struct (veja Apêndice E) com dois campos: o nome de um aluno e
* o número do aluno. Suponha que o vetor está em ordem crescente de
* números. Escreva uma função de busca binária que receba o número
* de um aluno e devolva o seu nome. Se o número não estiver no vetor,
* a função deve devolver a string vazia. */

typedef struct aluno{
    char *nome;
    int numero;
} aluno;

aluno *new(int numero, char *string){
    aluno *novo = malloc(sizeof(aluno));
    novo -> numero = numero;
    novo -> nome = string;
    return novo;
}

char *null(){
    char *nulo = malloc(sizeof(char));
    nulo[0] = '\0';
    return nulo;
}

char *busca_aluno(int numero, aluno **vec_of_alunos, int n){
    int e = 0, d = n;
    while (e < d){
        int m = (e+d)/2;
        int comparacao = vec_of_alunos[m] -> numero;
        if (comparacao == numero)
            return vec_of_alunos[m] -> nome;
        else if (comparacao > numero)
            d = m;
        else
            e = m + (e == m); // solve round problem of infinity loop
    }
    return null();
}

/* 7.8.6 PROCURANDO POR v[i] = i. Escreva uma função que receba um vetor
* estritamente crescente v[0..n-1] de números inteiros e devolva um índice
* i entre 0 e n-1 tal que v[i] = i; se tal i não existe, a função deve
* devolver -1. O seu algoritmo não deve fazer mais que log2n comparações
* envolvendo elementos de v */

int indice(int v[], int n){
    int e = 0, d = n;
    while (e < d){
        int m = (e+d)/2;
        if (v[m] == m) return m;
        else if (v[m] > m) d = m;
        else e = m;
    }
    return -1;
}

/* 7.8.7 Escreva uma função eficiente que receba inteiros
* positivos k e n e calcule k^n. Quantas multiplicações
* sua função executa? (Compare com o exercício 2.3.10.) */

/* R: executa n multiplicações */
int power(int k, int n){
    if (n == 0) return 1;

    else {
        int m; int fator;
        m = n / 2;
        fator = power(k, m);
        // branchless (verificar complementos/fn.c)
        // tem a versao iterativa também em complementos/iter.c
        int i = ((n % 2) ^ 1);
        int conditional = k * (1 - i) + i;
        return fator * fator * conditional;

        // versao original
        // if (m+m == n) return fator * fator;
        // else return fator*fator * k;

        // versao ternaria
        // int condicional = (n % 2) ? k : 1;
        // return fator * fator * condicional;
    }
}

/* A seguinte função recursiva pretende encontrar
* o valor de um elemento máximo do vetor v[e..d]
* supondo e <= d. O vetor não está necessariamente
* ordenado. A função está correta? Ela é mais rápida
* que a correspondente iterativa? Qual a profundidade
* da recursão? */

/* R: A função está correta. Ela possui menos etapas
* que a funcao iterativa e a profundidade da recursao é... (calculemos)
* Suponhamos um vetor de tamanho 10, uma chamadada
* gera duas chamadas de vetores de tamanho 5, que por sua
* vez gera duas chamadas de vetores de tamanho 2, que por
* sua vez chama mais duas chamadas com vetores de tamanho 1
* neste caso temos 1 -> 2 -> 2 -> 2 = 7 chamadas de funções
* Se fosse 20, daria 2 (10) -> 2 (5) -> 2 (2) -> 2 (1) = 8 chamadas de função 
* Se fosse 100 -> 2 (50) -> 2 (25) -> 2 (12) -> 2 (6) -> 2 (3) -> 2 (1)
* 12 chamadas. Neste caso acredito que estamos falando de uma aproximação
* 2^n = 100 => n = 6 => n*2 = 12 chamadas. Neste caso n = log2(100),
* isto é dado k, então o número de chamadas (n) é proporcional a n = log2(k) */
int max(int e, int d, int v[]){
    if (e == d) return v[d];
    else {
        int m, maxe, maxd;
        m = (e+d) / 2;
        maxe = max(e, m, v);
        maxd = max(m+1, d, v);
        if (maxe >= maxd) return maxe;
        else return maxd;
    }
}

int main(){
    int vetor[6] = {1, 12, 36, 98, 112, 136};
    assert(BuscaBinaria(99, 6, vetor) == 4);
    assert(BuscaBinaria(140, 6, vetor) == 6);
    assert(BuscaBinaria(0, 6, vetor) == 0);

    // 7.8.2
    int vetor2[6] = {136, 112, 98, 36, 12, 1};
    assert(BuscaBinariaDecrescente(99, 6, vetor2) == 2);
    assert(BuscaBinariaDecrescente(140, 6, vetor2) == 0);
    assert(BuscaBinariaDecrescente(0, 6, vetor2) == 5);

    // 7.8.3
    assert(BuscaBinariaEfetiva(12, 6, vetor) == 1);
    assert(BuscaBinariaEfetiva(0, 6, vetor) == -1);
    assert(BuscaBinariaEfetiva(140, 6, vetor) == -1);
    assert(BuscaBinariaEfetiva(38, 6, vetor) == -1);
    assert(BuscaBinariaEfetiva(98, 6, vetor) == 3);

    // 7.8.4
    int tamanho = 2;
    char** vec_of_strings = (char**)malloc(sizeof(char*) * tamanho);
    vec_of_strings[0] = malloc(3 * sizeof(char));
    strcpy(vec_of_strings[0], "hello");
    vec_of_strings[1] = malloc(5 * sizeof(char));
    strcpy(vec_of_strings[1], "world");
    vec_of_strings[2] = malloc(5 * sizeof(char));
    strcpy(vec_of_strings[2], "zebra");

    assert(busca_string("hello", vec_of_strings, 2) == 0);
    assert(busca_string("world", vec_of_strings, 2) == 1);
    assert(busca_string("Um texto qualquer", vec_of_strings, 2) == -1);

    // 7.8.5
    aluno** vec_of_alunos = (aluno**)malloc(sizeof(aluno*));
    vec_of_alunos[0] = new(0, "Rafael");
    vec_of_alunos[1] = new(1, "Leafar");
    vec_of_alunos[2] = new(2, "Francisco");

    assert( strcmp(busca_aluno(1, vec_of_alunos, 3), "Leafar") == 0);
    assert( strcmp(busca_aluno(-1, vec_of_alunos, 3), "\0") == 0);
    assert( strcmp(busca_aluno(3, vec_of_alunos, 3), "\0") == 0);
    assert( strcmp(busca_aluno(2, vec_of_alunos, 3), "Francisco") == 0);

    // 7.8.6
    int v[4] = {-5, -2, 0, 3};
    assert(indice(v, 4) == 3);
    int vec[6] = {1,2,3,4,5,6};
    assert(indice(vec, 6) == -1);

    // 7.8.7
    assert(power(2,5) == 32);

    // 7.8.8
    int vec2[10] = {1,2,10,4,9,6,7,8,5,3};
    assert(max(0,10,vec2) == 10);

    // printa OK se passar nos testes
    printf("OK");


}