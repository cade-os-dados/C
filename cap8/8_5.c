/* 8.5.1 O algoritmo de ordenação por inserção (Seção 8.2) 
é estável? */

/* Sim, pois só irá inserir em uma posição em que o valor
seja estritamente maior que o valor que está na posição anterior */

/* 8.5.2 No código da função Inserção (Seção 8.2), troque a comparação
"v[i] > x" por "v[i] >= x". A nova função faz uma ordenação estável
de v[0..n-1]? */

/* Não, ela irá trocar a ordem quando dois valores forem iguais */

/* 8.5.3 O algoritmo de ordenação por seleção (Seção 8.3) é estável? */
/* Não, pois ele sempre troca posição com o menor valor adjacente. */