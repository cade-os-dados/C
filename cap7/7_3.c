#include <stdio.h>
#include <stdlib.h>

/* Esta função recebe um vetor crescente v[0..n-1] com
* n >= 1 e um inteiro x. Ela devolve um índice j
* em 0..n tal que v[j-1] < x <= v[j]. */
int BuscaBinaria(int x, int n, int v[]){
    int e, m, d;
    e = -1; d = n;
    while (e < d-1) {
        m = (e+d)/2;
        if (v[m] < x) e = m;
        else d = m;
    }
    return d;
}

/* 7.3.1 Discuta e critique a elegância
* da seguinte variante da função BuscaBinaria */ 
int VarianteBuscaBinaria(int x, int n, int v[]){
    int e, m, d;
    if (v[n-1] < x) return n;
    if (x <= v[0]) return 0;
    e = 0; d = n-1;
    while (e < d-1){
        m = (e + d)/2;
        if (v[m] < x) e = m;
        else d = m;
    }
    return d;
}

/* R: A função busca validar se x está no intervalo v[0]..v[n-1] 
* antes de executar o core da função. Porém como vemos
* na função de referência no livro, os casos em que
* x não pertence ao intervalo já estão sendo cobertos
* no core da função quando tomamos e = -1, d = n inicialmente*/

/* 7.3.2 Suponha que v[i] = i para todo i. 
* Execute a função BuscaBinaria com n = 9 e x = 3.
* Repita o exercício com n = 14 e x = 7. Repita
* o exercício com n = 15 e x = 7. */
int *repeat(int n){
    int *vetor = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        vetor[i] = i;
    }
    return vetor;
}

/* 7.3.3 Execute a função BuscaBinaria com n = 16. Quais
* os possíveis valores de m na primeira iteração? 
* Quais os possíveis valores de m na segunda iteração?
* Na terceira? Na quarta? */

/* R: na primeira iteracao, somente (n-1)/2.
* Já na segunda iteração, pode ser ((n-1)/2 + n)/2
* ou ((n-1)/2 - 1)/2 e assim por diante...*/

/* 7.3.4 Na função BuscaBinaria, verifique que m percente
* ao intervalo 0..n-1 (e portanto v[m] faz sentido)
* sempre que o fragmento de código "if (v[m] < x)" é executado*/

/* R: Na primeira iteracao temos que m = (n-1) / 2, portanto
* p/ todo n E [1, +inf) m >= 0 e m < n. Já na segunda iteração
* teremos m = (m-1) / 2 ou m = (m+n) / 2, logo m >= 0 e m < n,
* e assim por diante... lembrando que se m = d = 0, então a condicional
* while (e < d-1) não é satisfeita e portanto a função retorna 0*/

/* 7.3.5 Confira a validade da seguinte afirmação: quando n+1
* é uma potência de 2, o valor da expressão (e+d) é divisível
* por 2 em todas as iterações da função BuscaBinaria
* (quaisquer que sejam v e x). */

/* R: suponha n+1 = 2^y. Na primeira iteração, temos
* e = - 1, d = n = 2^y - 1, portanto e+d = 2^y - 2
* Como 2^y % 2 = 0, então 2 ^ y - 2 % 2 = 0.
* Na iteração seguinte, teremos  m = (2^y-2)/2
* logo as seguintes opcoes (e+d) = (m-1) ou
* (m+d) <=> (m+2^y-1), da opcao (e+d) = (m-1), temos
* m-1 % 2 != 0, logo a afirmação é falsa */

/* 7.3.6 Responda as seguintes perguntas sobre a função
* BuscaBinaria. Que acontece se "while (e < d-1)" for
* substituído por "while (e < d)"? Que acontece se 
* "if (v[m] < x)" for substituído por "if (v[m] <= x)"?
* Que acontece se "e = m" for substituído por "e = m+1"
* ou por "e = m-1"? Que acontece se "d = m" for substituído
* por "d = m+1" ou por "d = m-1"? */

/* R: Vamos por partes, pois são muitas perguntas.
* Se a primeira substituição ocorrer, então poderíamos ter
* um resultado de -1 caso d = 0, o que não faz sentido, pois
* nosso vetor é de 0..n-1. Se a segunda substituição ocorrer,
* aparentemente nenhum efeito colateral ocorreria, no exemplo
* v[i] = i, n = 6, com x = 3, ambos chegariam na resposta d = 2.
* Nas demais substituições pode levar a resultados incorretos,
* Como novamente no exemplo v[i] = i, n = 6, x = 3, caso e = m+1,
* teríamos como output 4 e a resposta verdadeira é 2 */
void deBug(int x, int n, int v[]){
    int e, m, d;
    e = -1; d = n;
    while (e < d-1) {
        m = (e+d)/2;
        if (v[m] < x) e = m+1;
        else d = m;
        printf("d: %d | m: %d\n", d, m);
    }
}

int main(){
    // exercicio 7.3.2
    int *v9 = repeat(9);
    int resultado1 = BuscaBinaria(3, 9, v9);
    int *v14 = repeat(14);
    int resultado2 = BuscaBinaria(7, 14, v14);
    int *v15 = repeat(15);
    int resultado3 = BuscaBinaria(7, 15, v15);
    printf("Resultado 1: %d\nResultado 2: %d\nResultado 3: %d\n", resultado1, resultado2, resultado3);

    // 7.3.6
    deBug(3, 6, repeat(6));
}