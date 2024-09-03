#include <stdio.h>
#include <assert.h>

typedef unsigned char* palavra;
typedef unsigned char* texto;

#define MAX 6

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
        while(m-r >= 1 && a[m-r] == b[k-r])
            r+=1;
        if (m-r<1) ocorrs+=1;
        if (r==0) k+=1;
        else k += T2[m-r+1];
    }
    return ocorrs;
}

/* 
    Apenas por anotação:
    O algoritmo de Boyer-Moore tem duas heurísticas
    A heurística do caracter errado (13.3)
    e a heurística do bom sufixo (13.4)
    
    A heurística do bom sufixo vai procurar dentro
    da própria palavra padrões que casam entre si,
    sendo assim, se no texto casar com um padrão
    que dentro de si se repete, então deve-se
    pular para este padrão, caso contrário,
    pode pular a palavra toda
 */

/* 
    13.4.1 Calcule a tabela T2 no caso em que a[1] = a[2] = ... = a[m].
    Calcule a tabela T2 no caso em que os elementos de a[1..m] são distintos
    dois a dois.

    R: será tudo 1, no segundo caso será tudo 2
*/

/*
    13.4.2 Mostre que a fase de pré-processamento da função BoyerMoore2
    preenche corretamente a tabela T2.

    R: pelos testes unitários abaixo está correta, além disso
    está preenchendo corretamente, se não casar nenhum padrão
    na palavra, o valor será igual ao tamanho da palavra,
    caso contrário, a cada match que der (de trás para frente) 
    diminui em 1 unidade o valor do pulo
*/

/*
    13.4.3 Dê um exemplo em que a função BoyerMoore2 faz o maior número
    possível de comparações entre elementos de a e b. Descreva o exemplo
    com precisão.

    R: quando, na palavra, todos os caracteres forem iguais e quando,
    no texto, não tiver contido o caracter da palavra
*/




int main(void)
{
    palavra p = (palavra)"gato";
    texto t = (texto)"Quem nao tem cao caca com gato";
    int total = BoyerMoore2(p, 4, t, 31);
    assert(total == 1);

    /*13.3.2*/
    texto t2 = (texto)"MatoRatoPatoatogato";
    assert(BoyerMoore2(p,4,t2,20) == 1);

    palavra p2 = (palavra)"aaaa";
    BoyerMoore2(p2, 4, t, 31);

    printf("OK");
}