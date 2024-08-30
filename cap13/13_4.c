#include <stdio.h>
#include <assert.h>

typedef unsigned char* palavra;
typedef unsigned char* texto;

#define MAX 200

/*
    Recebe uma palavra a[1..m] com 1 <= m <= MAX e um texto
    b[1..n] e devolve o número de ocorrências de a em b
*/
int BoyerMoore2 (palavra a, int m, texto b, int n)
{
    int T2[MAX], i, j, k, r, ocorrs;
    /*pre-processamento da palavra a*/
    for(i=m;i>=1;i--){
        j=m-1;r=0;
        while(m-r >= i && i-r>=1)
            if(a[m-r] == a[j-r]) r+= 1;
            else j-=1, r=0;
        T2[i] = m-j;
    }
    ocorrs=0;k=m;
    while(k<=n){
        r=0;
        while(m-r >= 1 && a[m-r] == b[k-r]) r+=1;
        if (m-r<1) ocorrs+=1;
        if (r==0) k+=1;
        else k += T2[m-r+1];
    }
    return ocorrs;
}

int main(void)
{
    palavra p = "gato";
    texto t = "Quem nao tem cao caca com gato";
    int total = BoyerMoore2(p, 4, t, 31);
    assert(total == 1);

    /*13.3.2*/
    texto t2 = "MatoRatoPatoatogato";
    assert(BoyerMoore2(p,4,t2,20) == 1);

    printf("OK");
}