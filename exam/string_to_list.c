#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Titem{
    char * word;
    struct Titem * next;
    struct Titem * next_word;
    struct Titem * prev_word;
}TITEM;


TITEM * insert_end (TITEM * l , char * string){
    TITEM * new_node = (TITEM *) malloc(sizeof(TITEM));
    new_node->word = (char *) malloc(strlen(string)+1);
    strcpy(new_node->word,string);
    new_node->next = NULL;
    new_node->next_word = NULL;
    if(l==NULL){
        new_node->next_word = NULL;
        new_node->prev_word = NULL;
        return new_node;
    }
    TITEM * current = l;
    int connected = 0;
    while (current->next)
    {
        if(strcmp(current->word,new_node->word)==0){
            if(current->next_word==NULL){
            current->next_word = new_node;
            }
            new_node->prev_word = current;
            connected = 1;
        }
        current = current->next;
    }
    if(strcmp(current->word,new_node->word)==0){
        current->next_word = new_node;
        new_node->prev_word = current;
        connected = 1;
    }
    if(!connected){
        new_node->prev_word = NULL;
    }
    current->next = new_node;
    return l;
}


void print_list(TITEM * l){
    while (l)
    {
        printf("%s\n",l->word);
        if(l->next_word){
            printf("%s\n",l->next_word->word);
        }
        else{
            printf("next: NULL\n");
        }
        if(l->prev_word){
            printf("%s\n",l->prev_word->word);
        }
        else{
            printf("previous: NULL\n");
        }
        printf("_______\n");
        l = l->next;
    }
    
}


int main(){
    TITEM * list = NULL;
    printf("Enter the string\n");
    char * string = NULL;
    size_t string_size = 0;
    while(getline(&string,&string_size,stdin)!=EOF){
        char * temp = string;
        while(*temp){
            if(isspace(*temp)){
                temp++;
                continue;
            }
            char * word = (char *) malloc(string_size+1);
            char * head = word;
            while(!isspace(*temp)){
                *word++ = *temp++;
            }
            *word = '\0';
            list = insert_end(list,head);
            free(head);
        }
    }

    print_list(list);


}

