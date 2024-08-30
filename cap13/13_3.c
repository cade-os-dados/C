#include <stdio.h>
#include <assert.h>

typedef unsigned char* palavra;
typedef unsigned char* texto;

/*
    Recebe uma palavra a[1..m] e um texto b[1..n], com
    m >= 1 e n >= 0, e devolve o número de ocorrências
    de a em b. Supõe que cada elemento de a e b pertence
    ao conjunto de caracteres 0..255
*/
int BoyerMoore1 (palavra a, int m, texto b, int n)
{
    int T1[256], i, k, r, ocorrs;
    /*pre-processamento da palavra a*/
    for(i=0;i<256;i++) T1[i] = m;
    for(i=1;i<m;i++) T1[a[i]] = m - i;
    /*busca da palavra a no texto b*/
    ocorrs=0;k=m;
    while(k<=n)
    {
        r=0;
        while (m-r >= 1 && a[m-r] == b[k-r]) r+=1;
        if(m-r < 1) ocorrs += 1;
        if(k == n) k+= 1;
        else k += T1[b[k+1]] + 1;
    }
    return ocorrs;
}

/*
    13.3.3 Mostre que é possível eliminar o incômodo
    "if (k==n) k+=1; else" no código da função BoyerMoore1
    com o auxílio de uma sentinela postada em b[n+1]
*/
int BoyerMooreSentinela (palavra a, int m, texto b, int n)
{
    int T1[256], i, k, r, ocorrs;
    /*pre-processamento da palavra a*/
    for(i=0;i<256;i++) T1[i] = m;
    for(i=1;i<m;i++) T1[a[i]] = m - i;
    T1[b[n+1]] = 0;
    /*busca da palavra a no texto b*/
    ocorrs=0;k=m;
    while(k<=n)
    {
        r=0;
        while (m-r >= 1 && a[m-r] == b[k-r]) r+=1;
        if(m-r < 1) ocorrs += 1;
        k += T1[b[k+1]] + 1;
    }
    return ocorrs;
}

int main(void)
{
    palavra p = "gato";
    texto t = "Quem nao tem cao caca com gato";
    int total = BoyerMoore1(p, 4, t, 31);
    assert(total == 1);

    /*13.3.2*/
    texto t2 = "MatoRatoPatoatogato";
    assert(BoyerMoore1(p,4,t2,20) == 1);

    /*13.3.3*/
    assert(BoyerMooreSentinela(p,4,t,31) == 1);

    printf("OK");
}