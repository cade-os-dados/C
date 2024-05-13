#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/vec.h"
#include "include/busca.h"

/* Código de referência */
void Insercao(int n, int v[]){
    int i, j, x;
    for (j=1; j < n; j++){
        x = v[j];
        for (i = j-1; i >= 0 && v[i] > x; i--){
            v[i+1] = v[i];
        }
        v[i+1] = x;
    }
}

/* 8.2.1 No código da função Inserção, troque
* "v[i] > x" por "v[i] >= x". A nova função
* continua produzindo uma ordenação crescente de
* v[0..n-1]? */

/* R: Sim, continua
* Segue a invariante v[i+1] >= v[i]
* Apenas se introduz um passo a mais desnecessariamente */

/* 8.2.2 No código da função Inserção, que acontece se trocarmos
* "for (j=1" por "for (j=0"? Que acontece se trocarmos "v[i+1] = x"
* por "v[i] = x"? */

/* R: Se j = 0 então i = j-1 na iteração 0 será -1, ocasionando
* um memory leak. Se v[i] = x, então não temos a garantia de que 
* v[i] < x */

/* 8.2.3 Critique a seguinte implementação do algoritmo de ordenação
* por inserção*/

/* R: Está acessando índices repetidamente desnecessariamente, 
* em comparação com a função de referência */
void insercaoCritica(int n, int v[])
{
    int i, j, x;
    for (j = 1; j < n; j++){
        for (i = j-1; i >= 0 && v[i] > v[i+1]; i--){
            x = v[i]; v[i] = v[i+1]; v[i+1] = x;
        }
    }
}

/* 8.2.4 Critique a seguinte implementação do algoritmo de
* ordenação por inserção: */

/* R: Foi inserido um loop a mais somente para calcular
* o índice h, o que é ineficiente */
void insercaoCritica2(int n, int v[]){
    int h, i, j, x;
    for (j = 1; j < n; j++){
        x = v[j];
        for (h = 0; h < j && v[h] <= x; h++);
        for (i = j-1; i >= h; i--) v[i+1] = v[i];
        v[h] = x;
    }
}

/* 8.2.5 Escreva uma versão do algoritmo de inserção que
* tenha o seguinte invariante: no início de cada
* iteração, o vetor v[j+1..n-1] é crescente */

void insercaoInvariante(int n, int v[])
{
    int i, j, x;
    for (j = n-1; j >= 0; j--){
        x = v[j];
        for (i = j+1; (i < n-1) && (v[i] < x); i++){
            v[i-1] = v[i];
        }
        v[i-1] = x;
    }
}

/* 8.2.6 BUSCA BINÁRIA. O for interno na função
* Inserção tem a missão de encontrar o ponto onde
* v[j] deve ser inserido em v[0..j-1], ou seja,
* encontrar o índice i tal que v[i] <= v[j] < v[i+1].
* Considere fazer isso com uma busca binária (veja Seção 7.3).
* Analise o resultado. */

void insercaoBinaria(int n, int v[])
{
    int i, x;
    for (int j = 0; j < n; j++){
        x = v[j];
        int posicao = busca.binaria(x, j+1, v);
        if (x > v[posicao]) posicao++;
        if (x < v[posicao]) posicao--;

        for (i = j-1; i > posicao && i >= 0; i--){
            v[i+1] = v[i];
        }
        v[i+1] = x;
    }
}

/* 8.2.7 ORDEM ESTRITAMENTE CRESCENTE. Escreva uma função que rearranje um
* vetor v[0..n-1] de modo que ele fique em ordem estritamente crescente. */

/* R: isto somente é possível removendo dados repetidos do vetor*/
int conta_repetidos(int n, int v[]){
    int repetidos = 0;
    for (int i = 1; i < n; i++){
        if (v[i-1] == v[i])
            repetidos += 1;
    }
    return repetidos;
}

int *ordenacaoEstrita(int n, int v[]){
    int repetidos = conta_repetidos(n, v);
    int *resultado = malloc(sizeof(int) * (n-repetidos));
    insercaoBinaria(n, v);
    libvec.unique_copy(n, v, resultado);
    return resultado;
}

/* 8.2.8 ORDEM DECRESCENTE. Escreva uma função que permute os elementos de
* um vetor v[0..n-1] de modo que eles fiquem em ordem decrescente. */
void insercaoDecrescente(int n, int v[])
{
    int i, j, x;
    for (j = n-1; j >= 0; j--){
        x = v[j];
        for (i = j+1; (i <= n-1) && (v[i] > x); i++){
            v[i-1] = v[i];
        }
        v[i-1] = x;
    }
}

/* 8.2.9 VERSÃO RECURSIVA. Escreva uma versão recursiva do algoritmo de
* ordenação por inserção */

/* R: essa eu desisti e copiei do livro*/
void insercaoRecursiva(int n, int v[]){
    if (n > 1) {
        // inserção anterior
        insercaoRecursiva(n-1, v);

        // seleção do elemento
        int x = v[n-1];

        // inserção
        int i;
        for (i = n-2; v[i] > x && i >= 0; i--)
            v[i+1] = v[i];
        v[i+1] = x;
    }
}

/* 8.2.10 ANIMAÇÕES. Veja animações do algoritmo de inserção nas páginas de
* Harrison [8] e Morin [13] na teia www. */

/* 8.2.11 Leia o verbete Insertion sort na Wikipedia [21]. */

int main(void){
    
    int v[6] = {5, 6, 12, 7, 3, 15};
    int v2[6], v3[6];
    int memoria = sizeof(int) * 6;
    memcpy(v2, v, memoria);
    memcpy(v3, v, memoria);
    int vetor_esperado[6] = {3, 5, 6, 7, 12, 15};

    insercaoInvariante(6, v);
    libvec.assert_eq(v, vetor_esperado, 6);


    insercaoBinaria(6, v2);
    libvec.assert_eq(v2, vetor_esperado, 6);
   
    int v4[5] = {2,1,2,5,4};
    int vetor_esperado2[4] = {1,2,4,5};
    int *resultado = ordenacaoEstrita(5, v4);
    libvec.assert_eq(resultado, vetor_esperado2, 4);

    int vetor_esperado3[6] = {15, 12, 7, 6, 5, 3};
    insercaoDecrescente(6, v);
    libvec.assert_eq(v, vetor_esperado3, 6);
    
    insercaoRecursiva(6, v3);
    libvec.assert_eq(v3, vetor_esperado, 6);
    printf("OK");
}
