#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* Esta função devolve 1 se a string s contém uma sequência
bem-formada de parênteses e chaves e devolve 0 se
a sequência está malformada*/
int BemFormada (char s[]) {
    char *p; int t;
    int n, i;
    n = strlen(s);
    p = malloc(n * sizeof(char));
    t = 0;
    for (int i = 0; s[i] != '\0'; i++)
    /* p[0..t-1] é uma pilha */
    {
        switch (s[i])
        {
            case ')': 
                if (t != 0 && p[t-1] == '(') --t;
                else return 0; 
                break;
            case '}': 
                if (t != 0 && p[t-1] == '{') --t;
                else return 0;
                break;
            default:
                p[t++] = s[i];
        }
    }
    return t == 0;
}

/* 6.2.2 Mostre que o processo iterativo da função BemFormada tem o 
seguinte invariante: no início de cada iteração, a string s está bem-formada 
se e somente se a sequência p[0..t-1]s[i...], formada pela concatenação de 
p[0..t-1] com s[i...], estiver bem-formada*/

/* Prova (=>) "p[0..t-1]s[i...] bem formada, logo s bem formada"
Supondo X = p[0..t-1]s[i...] bem formada, então dado x E X, 
se x = ')' ou '}', supondo j seja a posição de x em X, então
X[j-1] = '(' ou '{' respectivamente. Supomos também y E s
como s é subsequência de X, então y E X, logo s é bem formada */

/* Prova (<=) "s bem formada, logo p[0..t-1]s[i...] bem formada"
(Redução a absurdo) Supondo s bem formada e supondo X = p[0..t-1]s[i...] 
mal formado então p[0..t-1] mal formado, tendo em vista que s é bem formada. 
Isto é, existe x E p[0..t-1] tal que x = '}' ou ')' e X[z-1] != '{' ou '(',
sendo z a posição de x em p[0..t-1]. Neste caso, a função retorna 0,
isto é, retorna que s não é bem formada, mas isto é um absurdo porque supomos
que s é bem formada. */

int main(){
    /* 6.2.1 A função BemFormada funciona corretamente 
    se s tem apenas dois elementos? apenas um? nenhum? */
    assert(BemFormada("{(})") == 0);
    assert(BemFormada("({})") == 1);
    assert(BemFormada("(}") == 0);
    assert(BemFormada("(") == 0);
    assert(BemFormada("()") == 1);
}