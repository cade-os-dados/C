#include <stdlib.h>
#include <string.h>

# ifndef BEM_FORMADA
# define BEM_FORMADA


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
            case '{':
            case '(':
                p[t++] = s[i];
                break;
            default:
                continue;
        }
    }
    return t == 0;
}

#endif