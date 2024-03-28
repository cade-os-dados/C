// funcao prototipo
int BuscaBinária2(int x, int n, int v[]){
    return BuscaBinR(x, -1, n, v);
}

// funcao referencia
/* O vetor v[e+1..d-1] é crescente e o inteiro x é tal que
* v[e] < x <= v[d]. A função devolve um índice j no intervalo
* e+1..d tal que v[j-1] < x <= v[j] */
int BuscaBinR(int x, int e, int d, int v[]){
    if (e == d-1) return d;
    else {
        int m = (e+d)/2;
        if (v[m] < x)
            return BuscaBinR(x, m, d, v);
        else
            return BuscaBinR(x, e, m, v);
    }
}

// 7.7.1 Discute a seguinte variante da função BuscaBinária2:
int BuscaBinária2(int x, int n, int v[]){
    if (v[n-1] < x) return n;
    if (x <= v[0]) return 0;
    return BuscaBinR(x, 0, n-1, v);
}

/* R: a função dá um early return caso x seja maior que
* o último elemento ou menor que o primeiro elemento,
* evitando que chamadas de função desnecessárias ocorram */

/* 7.7.2 Mostre que as condicoes descritas na documentação
* da função BuscaBinR estão satisfeitas no momento em que
* BuscaBinR é invocada por BuscaBinária2 */ 

/* R: BuscaBinária2 garante que na primeira iteração
* v[e] < x <= v[d]. Do contrário não teria esta garantia */

/* 7.7.3 Considere a função BuscaBinR. Suponha que v[m] < x.
* Verifique que v[m] < x <= v[d], mostrando assim que a
* função BuscaBinR pode ser invocada com argumentos x, m,
* d, v. Agora suponha que v[m] >= x e verifique que v[e] < x <= v[m],
* mostrando assim que BuscaBinR pode ser invocada com argumentos
* x, e, m, v. */

/* Seja m = (e+d)/2 e v[m] < x então v[e] < v[m] < x. Como por definição,
* x E (v[e], v[d]], então v[e] < x <= v[d]. Do mesmo modo,
* se v[m] >= x, então v[e] < x <= v[m] */