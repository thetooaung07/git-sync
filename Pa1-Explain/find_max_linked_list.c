#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct Titem {
  struct Titem * m_Next;
  char m_Digit;
} TITEM;
 
TITEM * createItem ( char i ,TITEM * next ) {
  TITEM * l = (TITEM*) malloc ( sizeof(*l) ); 
  l->m_Digit = i;
  l->m_Next = next;
  return l;
}
TITEM * createList(const char * x) {
    int i = 0;
    TITEM * item = NULL;
    while(x[i]) {
     item = createItem (x[i], item);
     i++;
    }
    return item;
}
void delList ( TITEM * l ) {
  while (l) {
      TITEM * tmp = l->m_Next;
      free (l);
      l = tmp;
  }
}
#endif /* __PROGTEST__ */

void printList (TITEM* a) {
    TITEM* curr = a;

    while (curr) {
        printf("%c -> ", curr->m_Digit);
        curr = curr->m_Next;
    } 
    printf("\n");
}

TITEM* reverse (TITEM* a) {
    TITEM* curr = a;
    TITEM* prev = NULL; 

    while (curr) {
        TITEM* next = curr->m_Next;
        curr->m_Next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

int isGreater(TITEM* a, TITEM* b) {
    int lenA = 0;
    int lenB = 0;
 
    TITEM* iterA = a;
    TITEM* iterB = b;

    while (iterA) {
        lenA++;
        iterA = iterA->m_Next;
    }
    while (iterB) {
        lenB++;
        iterB = iterB->m_Next;
    }

    if (lenA != lenB) return (lenA > lenB);

    iterA = a;
    iterB = b;

    int stackA[1000], stackB[1000];
    int idx = 0;

    while (iterA) {
        stackA[idx] = iterA->m_Digit;
        idx++;
        iterA = iterA->m_Next;
    }

    idx = 0;

    while (iterB) {
        stackB[idx] = iterB->m_Digit;
        idx++;
        iterB = iterB->m_Next;
    }

    for (int i = lenA - 1; i >= 0; i--) {
        if (stackA[i] != stackB[i]) {
            return (stackA[i] > stackB[i]);
        }
    }

    return 0;
}
 
TITEM * maxOf ( TITEM ** x, int nr ) {
   if (nr <= 0) return NULL;
   if (x == NULL) return NULL;
   TITEM* result = NULL;

   for (int i = 0; i < nr; i++) {
    TITEM* curr = x[i];
    if (curr == NULL) {
        return NULL;
    }

    TITEM* iter = curr;
    while (iter) {
        if (!isdigit(iter->m_Digit)) {
            return NULL;
        }
        iter = iter->m_Next;
    }

    if (result == NULL || isGreater(curr, result)) {
        result = curr;
    }
    
   }
   return result;
}
 
#ifndef __PROGTEST__
int main ( void ) {
 
    TITEM * a[5];
    TITEM * res;
 
    //----- Zakladni test ----------------------------------------------
    a[0] = createList("191");
    a[1] = createList("113");
    a[2] = createList("197");
    res = maxOf(a, 3);
 
    assert(res == a[2]);
    printf("Passed\n");
 
    for(int i = 0; i < 3; i++) delList(a[i]);
 
    //----- Radove vyssi cislo -----------------------------------------
    a[0] = createList("313");
    a[1] = createList("1191");
    a[2] = createList("997");
    res = maxOf(a, 3);
 
    assert(res == a[1]);
    printf("Passed\n");
 
    for(int i = 0; i < 3; i++) delList(a[i]);
 
    //----- Chybny vstup -----------------------------------------------
    a[0] = createList("222");
    a[1] = NULL;
    a[2] = createList("4333");
    a[3] = createList("1");
    res = maxOf(a, 4);
 
    assert(res == NULL);
    printf("Passed\n");
 
    for(int i = 0; i < 4; i++) delList(a[i]);
 
    //----- Chybna hodnota ---------------------------------------------
    a[0] = createList("29a");
    a[1] = createList("11");
    res = maxOf(a, 2);
 
    assert(res == NULL);
    printf("Passed\n");
 
    for(int i = 0; i < 2; i++) delList(a[i]);
 
    //----- Stejna cisla -----------------------------------------------
    a[0] = createList("27986");
    printList(a[0]);
    a[1] = createList("3256");
    a[2] = createList("27986");
    a[3] = createList("17000");
    res = maxOf(a, 4);
 
    assert(res == a[0]);
    printf("Passed\n");
 
    for(int i = 0; i < 4; i++) delList(a[i]);
 
    //----- Nula -------------------------------------------------------
    a[0] = createList("0");
    a[1] = createList("0");
    a[2] = createList("0");
    a[3] = createList("0");
    a[4] = createList("0");
    res = maxOf(a, 5);
 
    assert(res == a[0]);
    printf("Passed\n");
 
    for(int i = 0; i < 5; i++) delList(a[i]);
 
    //----- Unsigned Long Long Int -------------------------------------
    a[0] = createList("0");
    a[1] = createList("18446744073709551615");
    a[2] = createList("1112367822345622");
    a[3] = createList("9991234530632948235");
    a[4] = createList("1213004921032");
    res = maxOf(a, 5);
 
    assert(res == a[1]);
    printf("Passed\n");
 
    for(int i = 0; i < 5; i++) delList(a[i]);
 
    //----- Vetsi jak Unsigned Long Long Int ---------------------------
    a[0] = createList("50230529401950984100481491404914091408580");
    a[1] = createList("50230529401950123123123234492492042044242");
    a[2] = createList("50230529401950984100480123032931110119944");
    a[3] = createList("50230529401950123123123234492400000000000");
    a[4] = createList("50230531000000000000000000000000000000000");
    res = maxOf(a, 5);
 
    assert(res == a[4]);
    printf("Passed\n");
 
    for(int i = 0; i < 5; i++) delList(a[i]);
 
    //----- Vetsi jak Unsigned Long Long Int ruzne dlouhe --------------
    a[0] = createList("253051330239013091349049023023");
    a[1] = createList("253051330239013091349049023024");
    a[2] = createList("2094241212100000000000100100");
    a[3] = createList("999919103904248923023");
    a[4] = createList("999999999999999999999999999");
    res = maxOf(a, 5);
 
    assert(res == a[1]);
    printf("Passed\n");
 
    for(int i = 0; i < 5; i++) delList(a[i]);
    return 0;
}
#endif /* __PROGTEST__ */