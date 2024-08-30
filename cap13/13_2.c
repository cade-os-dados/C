#include <stdio.h>
#include <assert.h>

typedef unsigned char* palavra;
typedef unsigned char* texto;

/*
    Recebe uma palavra a[1..m] e um texto b[1..n],
    com m >= 1 e n >= 0, e devolve o numero de
    ocorrencias de a em b
*/
int trivial(palavra a, int m, texto b, int n)
{
    int k,r,ocorrs;
    ocorrs = 0;
    for(k=m;k<=n;k++)
    {
        r = 0;
        while(r<m && a[m-r] == b[k-r]) r+=1;
        if(r>=m) ocorrs += 1;
    }
    return ocorrs;
}

/*
    13.2.1 Dê um exemplo em que o algoritmo trivial faz o
    maior número possível de comparações entre elementos de
    a e b. Descreva o exemplo com precisão.
*/

int main(void)
{
    palavra p = "gato";
    texto t = "Quem nao tem cao caca com gato";
    int total = trivial(p, 4, t, 31);
    assert(total == 1);

    /*
        Pior caso abaixo
        pois faz todas as comparacoes sempre que
        a palavra termina em ato 
    */
    texto t2 = "MatoRatoPatoatogato";
    assert(trivial(p,4,t2,20) == 1);

    printf("OK");
}