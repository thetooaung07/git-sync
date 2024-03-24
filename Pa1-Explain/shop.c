#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct item {
    char* id;
    int count;
} Item;

char* removeNewLine (char* string) {
    int length = strlen(string);
    if (length > 0 && string[length-1] == '\n') {
        string[length-1] = '\0';
    }
    return string;
}

Item* pushArray (Item* array, int* size, int* capacity, char* id, int count) {
    if (*size >= *capacity) {
        if (*capacity == 0) (*capacity)++;
        else (*capacity) *= 2;
        array = (Item*)realloc(array, (*capacity)*(sizeof(Item)));
    }
    array[*size].count = count;
    array[*size].id = (char*)malloc(strlen(id)+1);
    strcpy(array[*size].id, id);
    (*size)++;
    return array;
} 

int isStringDigit (char* string) {
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        if (!isdigit(string[i])) {
            return 0;
        }
    }
    return 1;
}

int main () {
    Item* array = NULL;
    int size = 0;
    int capacity = 0;
    char sign;
    int itemCount;
    char id[101];

    printf("Goods:\n");
    while (scanf(" %c %dx %s", &sign, &itemCount, id) == 3) {
        int found = 0;
        int length = strlen(id);
        if ((sign != '+' && sign != '-') || itemCount < 0 || length < 5 || length > 100 || !isStringDigit(id)) {
            for (int i = 0; i < size; i++) {
                free(array[i].id);
            }
            free(array);
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }

        if (sign == '+') {
            for (int i = 0; i < size; i++) {
                if (strcmp(array[i].id, id) == 0) {
                    array[i].count += itemCount;
                    printf(">%dx\n", array[i].count);
                    found = 1;
                }
            }
            if (!found) {
                array = pushArray(array, &size, &capacity, id, itemCount);
                printf(">%dx\n", itemCount);
            }
        }

        if (sign == '-') {
            for (int i = 0; i < size; i++) {
                if (strcmp(array[i].id, id) == 0) {
                    found = 1;
                    if (itemCount > array[i].count) {
                        printf("Insufficient stock.\n");
                        continue;
                    }
                    array[i].count -= itemCount;
                    printf(">%dx\n", array[i].count);
                }
            }
            if (!found) {
                printf("The item was not found.\n");
            }
        } 
    }
    if (!feof(stdin)) {
        for (int i = 0; i < size; i++) {
            free(array[i].id);
        }
        free(array);
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        free(array[i].id);
    }
    free(array);
    return EXIT_SUCCESS;
}