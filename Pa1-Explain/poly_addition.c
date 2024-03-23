#ifndef __PROGTEST__ 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>
 
typedef  struct TItem
 { 
    struct TItem * m_Next ; 
    int m_Mul ; 
    int m_Pow ; 
} TITEM ;
 
TITEM * createItem (  int mul ,  int  pow , TITEM * next ) 
{ 
    TITEM * n =  ( TITEM * )  malloc  ( sizeof  (  * n ) ) ; 
    n -> m_Mul = mul ; 
    n -> m_Pow =  pow ; 
    n -> m_Next = next ; 
    return n ; 
}
 
void deleteList ( TITEM * l ) 
{ 
    while  ( l ) 
    { 
        TITEM * tmp = l -> m_Next ; 
        free  ( l ) ; 
        l = tmp ; 
    } 
} 
#endif /* __PROGTEST__ */

void printList (TITEM* a) {
    TITEM* curr = a;

    while (curr) {
        printf("%dx^%d -> ", curr->m_Mul, curr->m_Pow);
        curr = curr->m_Next;
    } 
    printf("\n");
}

TITEM* reverseList (TITEM* list) {
    TITEM* curr = list;
    TITEM* prev = NULL;

    while (curr) {
        TITEM* next = curr->m_Next;
        curr->m_Next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int check (TITEM* a) {
    TITEM* iter = a;
    a = a->m_Next;

    while (a) {
        if (a->m_Pow <= iter->m_Pow) {
            return 0;
        }
        iter = iter->m_Next;
        a = a->m_Next;
    }
    return 1;
}
 
TITEM * addPoly ( TITEM * a , TITEM * b ) 
{ 
    if (a == NULL || b == NULL) {
        return NULL;
    }

    if (!check(a) || !check(b)) {
        return NULL;
    }

    TITEM* result = NULL;

    while (a && b) {
        if (a->m_Mul == 0) {
            a = a->m_Next;
            continue;
        }

        if (b->m_Mul == 0) {
            b = b->m_Next;
            continue;
        }

        if (a->m_Pow < b->m_Pow) {
            result = createItem(a->m_Mul, a->m_Pow, result);
            a = a->m_Next;
        }

        else if (a->m_Pow > b->m_Pow) {
            result = createItem(b->m_Mul, b->m_Pow, result);
            b = b->m_Next;
        }

        else if (a->m_Pow == b->m_Pow) {
            result = createItem(a->m_Mul + b->m_Mul, a->m_Pow, result);
            a = a->m_Next;
            b = b->m_Next;
        }
    }

    while (a) {
        if (a->m_Mul == 0) {
            a = a->m_Next;
            continue;
        }

        result = createItem(a->m_Mul, a->m_Pow, result);
        a = a->m_Next;
    }

    while (b) {
        if (b->m_Mul == 0) {
            b = b->m_Next;
            continue;
        }

        result = createItem(b->m_Mul, b->m_Pow, result);
            b = b->m_Next;
    }

    TITEM* curr = result;

    result = reverseList(result);
    printList(result);

    while (curr->m_Next) {
        if (curr->m_Next->m_Mul == 0) {
            TITEM* toRemove = curr->m_Next;
            curr->m_Next = curr->m_Next->m_Next;
            free(toRemove);
        }
        else {
            curr = curr->m_Next;
        }
    }

    if (result->m_Mul == 0) {
        TITEM* temp = result;
        result = result->m_Next;
        free(temp);
    }

    if (result == NULL) {
        TITEM* new_node = (TITEM*)malloc(sizeof(TITEM));
        new_node->m_Mul = 0;
        new_node->m_Pow = 0;
        new_node->m_Next = NULL;
        result = new_node;
    }

    return result;
}
 
#ifndef __PROGTEST__ 
int main (  int argc ,  char  * argv [ ]  ) 
{ 
    TITEM * a ,  * b ; 
    TITEM * res ;
 
    a = createItem ( 2 , 1 , NULL ) ; 
    b = createItem ( 0 , 0 , NULL ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res -> m_Mul ==  2  ) ; 
    assert  ( res -> m_Pow ==  1  ) ; 
    assert  ( res -> m_Next == NULL ) ; 
    printf("Passed\n");
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    a = createItem ( 2 , 1 , NULL ) ; 
    b = createItem ( 3 , 1 , createItem ( 4 , 2 , createItem ( 2 , 3 , createItem ( 1 , 0 , NULL ) ) ) ); 
    res = addPoly ( a , b ) ; 
    assert  ( res == NULL ) ;
    printf("Passed\n"); 
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    a = createItem ( 2 , 1 , NULL ) ; 
    b = createItem ( 3 , 1 , createItem ( 4 , 1 , NULL ) ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res == NULL ) ; 
    printf("Passed\n");
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    // a = createItem ( 3 , 0 , createItem ( 2 , 1 , createItem ( 9 , 3 , NULL ) ) ) ; 
    // b = createItem ( 0 , 0 , createItem ( 4 , 2 , createItem ( - 1 , 3 , NULL ) ) ) ; 
    // res = addPoly ( a , b ) ; 
    // assert  ( res == NULL ) ; 
    // deleteList ( a ) ; 
    // deleteList ( b ) ; 
    // deleteList ( res ) ;
 
    a = createItem ( 3 , 0 , createItem ( 2 , 1 , createItem ( 5 , 3 , NULL ) ) ) ; 
    b = createItem ( - 7 , 0 , createItem ( - 2 , 1 , createItem ( - 5 , 3 , NULL ) ) ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res -> m_Mul ==  - 4  ) ; 
    assert  ( res -> m_Pow ==  0  ) ; 
    assert  ( res -> m_Next == NULL ) ; 
    printf("Passed\n");
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    a = createItem ( 3 , 1 , createItem ( - 2 , 2 , createItem ( 4 , 3 , NULL ) ) ) ; 
    b = createItem ( - 3 , 1 , createItem ( 2 , 2 , createItem ( - 4 , 3 , NULL ) ) ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res -> m_Mul ==  0  ) ; 
    assert  ( res -> m_Pow ==  0  ) ; 
    assert  ( res -> m_Next == NULL ) ; 
    printf("Passed\n");
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    return  0 ; 
} 
#endif /* __PROGTEST__ */