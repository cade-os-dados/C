/* 
    Definição:
    Uma árvore binária é um conjunto A de nós tal que (1) os filhos de cada elemento 
    de A pertencem a A, (2) todo elemento de A tem no máximo um pai, (3) um e 
    apenas um dos elementos de A não tem pai em A, (4) os filhos esquerdo e 
    direito de cada elemento de A são distintos e (5) não há ciclos em A.


    14.1.1 Dado o endereço x de um nó em uma árvore binária, considere
    a sequência de endereços que se obtém pela iteração das atribuições
    x = x -> esq e x = x -> dir em qualquer ordem. Mostre que esta sequência
    descreve um caminho.

    R: seja x = y0, se y1 = x -> esq então y1 é filho de y0,
    caso contrário, se y1 = x -> dir então y1 é filho de y0
    por indução, segue que qualquer iteração aleatória é um caminho 
*/

/*
    14.1.3 Sejam X e Z dois nós de uma árvore binária. Mostre que existe
    no máximo um caminho com origem X e término Z.

    R: 
    
    (1) Se A é uma árvore binária, então para todo
    
    seja C1 e C2 caminhos distintos, (YC[0] = X, YC[1], YC[2], ..., YC[k] = Z)
    e (YCC[0] = X, YCC[1], ..., YCC[i] = Z) suas respectivas sequências e
    Neste caso, YCC[i] = YC[k] = Z, portanto YCC[i-1] = YC[k-1] (2),
    YCC[i-2] = YC[i-2], ... YCC[0] = YC[0]
    Logo C1 = C2, cqd.

*/