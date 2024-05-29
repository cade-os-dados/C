void intercala (int p, int q, int r, int v[]){
    int i, j, k, *w;
    w = malloc((r-p) * sizeof(int));
    i = p; j = q; k = 0;
    while (i < q && j < r){
        if (v[i] <= v[j]) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i < q) w[k++] = v[i++];
    while (j < r) w[k++] = v[j++];
    for (i = p; i < r; i++) v[i] = w[i-p];
    free (w);
}

void mergesort(int p, int r, int v[])
{
    if (p < r-1){
        int q = (p+r)/2;
        mergesort(p, q, v);
        mergesort(q, r, v);
        intercala(p, q, r, v);
    }
}

/* 9.2.1 Que acontece se trocarmos "(p+r)/2" por "(p+r-1)/2"
* no código de mergesort? Que acontece se trocarmos "(p+r)/2"
* por "(p+r+1)/2"? */

/*R: só vai mudar o tamanho individual dos vetores, porém o resultado
* será o mesmo */

/* 9.2.7 Critique a seguinte implementação da função Mergesort */
void criticaMergesort(int p, int r, int v[]){
    int q;
    if (p < r-1){
        q = r - 1;
        criticaMergesort(p, q, v);
        intercala(p, q, r, v);
    }
}

/* R: a função está ordenando elemento a elemento e não fazendo a junção
* de dois vetores em ordem crescente...*/