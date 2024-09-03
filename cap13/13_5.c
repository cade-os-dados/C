#include <stdio.h>
#include <assert.h>

typedef unsigned char* palavra;
typedef unsigned char* texto;

#define MAX 256

/* 13.5.1 Escreva o código do terceiro algoritmo de Boyer-Moore */
int BoyerMoore3 (palavra a, int m, texto b, int n)
{
    int T1[256], T2[MAX], t1, t2, p, i, j, k, r, ocorrs;

    for(p=0;p<256;p++) T1[p] = m;
    for(p=1;p<m;p++) T1[a[p]] = m - p;

    for(i=m;i>=1;i--){
        j=m-1;r=0;
        while(m-r >= i && j-r>=1)
        {
            if(a[m-r] == a[j-r]) r+= 1;
            else j-=1, r=0;
        }
        T2[i] = m-j;
    }

    ocorrs=0;k=m;
    while(k<=n){
        r=0;
        while(m-r >= 1 && a[m-r] == b[k-r]) r+=1;
        if (m-r<1) ocorrs+=1;
        if (r==0) k+=1;
        else
        {
            t1 = T1[b[k+1]] + 1;
            t2 = T2[m-r+1];
            if(t1 >= t2) k+= t1;
            else k+= t2;
        }
    }
    return ocorrs;
}

int main(void)
{
    palavra p = (palavra)"gato";
    texto t = (texto)"Quem nao tem cao caca com gato";
    int total = BoyerMoore3(p, 4, t, 31);
    assert(total == 1);

    /*13.3.2*/
    texto t2 = (texto)"MatoRatoPatoatogato";
    assert(BoyerMoore3(p,4,t2,20) == 1);

    palavra p2 = (palavra)"aaaa";
    BoyerMoore3(p2, 4, t, 31);

    printf("OK");
}
