// (7.2) v[e] < x <= v[d]

/* 7.4.1 Suponha que estamos no início de uma iteração
* (que não a última) da função BuscaBinaria. Suponha que vale
* a relação (7.2). Mostre que (7.2) vale no início da próxima iteração. */

/* R: vale 7.2, logo v[e] < x <= v[d], seja m = (e+d)/2, na proxima 
iteração teremos duas possibilidades:
* 1. se v[m] < x, então e = m, logo v[m] < x <= v[d] ainda é válido
* 2. se v[m] >= x, então d = m, logo v[e] < x <= v[m]*/

/* 7.4.2 Mostre que no início da última iteração da função BuscaBinaria
* temos e = d - 1. */

/* R: Supomos que k = inicio da última iteracao,
* e vamos supor e != d - 1, assim temos duas possibilidades
* e < d - 1 ou e > d - 1. No primeiro caso, é um absurdo,
* pois enquanto e < d - 1 segue o loop até k + 1. No segundo caso,
* teríamos em k - 1, v[m] < x, com m = (e+d)/2 !E (d-1, inf) <=> [d, inf).
* Supondo o primeiro caso em que (e+d)/2 = d, temos que e = d,
* mas isto é um absurdo já que de (7.2) v[e] < x <= v[d] */

/* 7.4.3 Na função BuscaBinaria, mostre que temos e < m < d imediatamente
depois da atribuicao "m = (e+d)/2" */

/* R: Supomos a iteração k com m < e, sendo m = (e+d)/2, 
* então (e+d) / 2 < e <=> e+d < 2e <=> d < e,
* mas isto é impossível, pois m não será atribuído
* se e > d - 1 */