#include <stdio.h>
#include <assert.h>

/* 7.5.1 Faça uma tabela de valores [log_2 n] para 
* n = 10^1, 10^2, 10^3, 10^4, 10^5. (Veja exercício 1.2.4.)*/
/* R: 3.32, 6.64, 9.96, 13.28, 16.60 */

/* 7.5.2 Se t segundos são necessários para fazer uma busca
binária em um vetor com n elementos, quantos segundos serão
necessários para fazer uma busca em n^2 elementos? */ 

/* R: O tempo de execução t = f(n) = O(log(n))
então t_2 = f(n^2) = O(log(n^2)) = O(2*log(n))
= 2*t */

/* 7.5.3 OVERFLOW ARITMÉTICO Se o número de elementos
do vetor v[0..n-1] estiver próximo de INT_MAX (veja Seção K.5),
o código da função BuscaBinária pode descarrilar ao calcular
o valor da expressão (e+d)/2, em virtude de um overflow aritmetico.
Como evitar isso? */

/* R: podemos contornar a situação dividindo 'e' e 'd'
por 2 individualmente depois somando os resultados
que chegará no mesmo resultado e evitará o overflow */

int buscaBinariaOverflow(int x, int n, int v[]){
    int e, m, d;
    e = -1; d = n;
    while (e < d-1) {
        m = (e+d)/2;
        if (v[m] < x) e = m;
        else d = m;
    }
    return d;
}

// avoid overflow
int buscaBinariaSafe(int x, int n, int v[]){
    int e, m, d;
    e = -1; d = n;
    while (e < d-1) {
        m = e/2;
        m += d/2;
        if (v[m] < x) e = m;
        else d = m;
    }
    return d;
}

int main(){
    int n = __INT_MAX__;
    int overflow = n+1;
    int e = n/2;
    int d = n-1;
    int resultado = e/2 + d/2;
    assert(resultado == 1610612734);
    assert(overflow == -2147483648);
    assert(n == 2147483647);
    printf("OK");
}