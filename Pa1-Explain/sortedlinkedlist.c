#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem             * m_Next;
  char                     * m_Name;
  char                       m_Secret[24];
} TITEM;

int cmpName ( const TITEM * a,
              const TITEM * b )
{
  return strcmp ( a -> m_Name, b -> m_Name );
}

int cmpNameInsensitive ( const TITEM * a,
                         const TITEM * b )
{
  return strcasecmp ( a -> m_Name, b -> m_Name );
}

int cmpNameLen ( const TITEM * a,
                 const TITEM * b )
{
  size_t la = strlen ( a -> m_Name ), lb = strlen ( b -> m_Name );
  return ( lb < la ) - ( la < lb );
}
#endif /* __PROGTEST__ */

TITEM            * newItem      ( const char      * name,
                                  TITEM           * next )
{
  TITEM* new_node = (TITEM*)malloc(sizeof(TITEM));
  new_node->m_Name = (char*)malloc(strlen(name)+1);
  strcpy(new_node->m_Name ,name);

  if (next == NULL) {
    new_node->m_Next = NULL;
  }

  new_node->m_Next = next; 
  memset(new_node->m_Secret,'\0',24);
  return new_node;
}
TITEM            * sortListCmp  ( TITEM           * l,
                                  int               ascending,
                                  int            (* cmpFn) ( const TITEM *, const TITEM *) )
{
  if(l== NULL){
        return NULL;
    }
    if(l->m_Next==NULL){
        return l;
    }


    int constant = 1;
    if(ascending==0) constant = -1;
  int swapped = 1;

    do
    {
        TITEM *previous = NULL, *curr = l;

        swapped = 0;
        while(curr->m_Next)
        {
            if(constant * cmpFn(curr, curr->m_Next)>0)
            {   
                TITEM * swap;
                swap = curr->m_Next;
                curr->m_Next = swap->m_Next;
                swap->m_Next = curr;

                if (previous==NULL){
                    previous = swap;
                    l= previous;
                }

                else {
                    previous->m_Next = swap;
                    previous = swap;
                }
                swapped = 1;
            }

            else{
                if (previous==NULL){
                    previous = curr;
                    curr = curr->m_Next;
                    l = previous;
                }
                else {
                    previous = curr;
                    curr = curr->m_Next;
                }
            }
        }
    } while(swapped);
    return l;
}
void               freeList     ( TITEM           * src )
{
  TITEM* iter = src;
  while (iter!=NULL) {
    TITEM* temp = iter;
    iter = iter->m_Next;
    free(temp->m_Name);
    free(temp);
  }
  src = NULL;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TITEM * l;
  char tmp[50];

  assert ( sizeof ( TITEM ) == sizeof ( TITEM * ) + sizeof ( char * ) + 24 * sizeof ( char ) );
  l = NULL;
  l = newItem ( "BI-PA1", l );
  l = newItem ( "BIE-PA2", l );
  l = newItem ( "NI-PAR", l );
  l = newItem ( "lin", l );
  l = newItem ( "AG1", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpName );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameInsensitive );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameLen );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = newItem ( "AAG.3", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 0, cmpNameLen );
  assert ( l
           && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  l = NULL;
  strncpy ( tmp, "BI-PA1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "BIE-PA2", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "NI-PAR", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "lin", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpName );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameInsensitive );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameLen );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  strncpy ( tmp, "AAG.3", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 0, cmpNameLen );
  assert ( l
           && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */