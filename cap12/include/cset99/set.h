#pragma once
#include "stdlib.h"
#include "cset99/safearray.h"
#include "math.h"

struct node
{
    safeArray chave;
    struct node* e;
    struct node* d;
};

typedef struct node no;
typedef no* set;

set begin(safeArray s);
set search(set r, safeArray s);
set searchCloser(set r, safeArray s);
int altura(set r);
/*https://www.geeksforgeeks.org/insertion-in-an-avl-tree/*/
set leftRotation(set r);
set rightRotation(set r);
set balance(set r, safeArray s);
set insert(set r, safeArray s);