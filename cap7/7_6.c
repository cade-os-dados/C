#include <assert.h>
#include <stdio.h>

/* 7.6.1 Mostre que a seguinte variante da função 
BuscaBinária funciona corretamente (Esta versão é 
quase tão elegante quanto a versão discutida na Seção 
7.3.) Que acontece se trocarmos "while (e < d)" por 
"while (e <= d)"? Que acontece se trocarmos "(e+d)/2"
por "(e-1+d)/2"? */

/* R: se trocar a condição do while, entrará em loop
infinito. Se trocar (e+d)/2 por (e-1+d)/2 o programa
funcionará corretamente, porém eventualmente poderá
executar mais instruções para chegar no resultado */

// Funcao do exercicio 7.6.1
int BuscaBinaria(int x, int n, int v[]){
    int e, m, d;
    e = 0; d = n;
    while (e < d) { /* v[e-1] < x <= v[d] */
        m = (e-1+d)/2;
        if (v[m] < x) e = m+1;
        else d = m;
    } /* e == d */
    return d;
}

/* 7.6.2 Mostre que a seguinte versão da BuscaBinária
funciona corretamente. Ela é um pouco menos elegante
que as versões anteriores*/
int BuscaBinariaMenosElegante(int x, int n, int v[]){
    int e, m, d;
    e = 0; d = n-1;
    while (e <= d) { /* v[e-1] < x <= v[d+1] */
        m = (e+d)/2;
        if (v[m] < x) e = m+1;
        else d = m-1;
    } /* e == d+1 */
    return d+1;
}

/* 7.6.3 A seguinte alternativa para a função BuscaBinária
funciona corretamente? Que acontece se trocarmos "(e+d)/2"
por "(e+d+1)/2"? */

/* R: pelo assert está funcionando corretamente. Se trocar
a instrução, irá funcionar do mesmo jeito, porém poderá
adicionar instruções desnecessárias*/

int BuscaBinariaDuvidosa(int x, int n, int v[]){
    int e, m, d;
    e = -1; d = n-1;
    while (e < d) { /* v[e] < x <= v[d] */
        m = (e+d+1)/2;
        if (v[m] < x) e = m;
        else d = m-1;
    }
    return d+1;
}

int main(){
    // teste 7.6.1
    int vetor[6] = {1, 12, 36, 98, 112, 136};
    int index = BuscaBinaria(99, 6, vetor);
    assert(index == 4);
    // teste 7.6.2
    int idx = BuscaBinariaMenosElegante(99, 6, vetor);
    assert(idx == 4);
    // teste 7.6.3
    int indx = BuscaBinariaDuvidosa(99, 6, vetor);
    assert(indx == 4);

    // printa OK se passar nos testes
    printf("OK");
}