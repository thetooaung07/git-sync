#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct domino {
    char id;
    int* numbers;
    int duplicated;
    int numItems;
} Domino;

Domino* pushArray (Domino* array, int* size, int* capacity, char id) {
    if (*size >= *capacity) {
        if (*capacity == 0) (*capacity)++;
        else (*capacity) *= 2;
        array = (Domino*)realloc(array, (*capacity)*(sizeof(Domino)));
    }
    array[*size].id = id;
    array[*size].numbers = NULL;
    array[*size].duplicated = 0;
    array[*size].numItems = 0;
    (*size)++;
    return array;
}

Domino* pushNumArray (Domino* array, int* size, int* capacity, int number, int arrSize) {
    if (*size >= *capacity) {
        if (*capacity == 0) (*capacity)++;
        else (*capacity) *= 2;
        array[arrSize].numbers = (int*)realloc(array[arrSize].numbers, (*capacity)*(sizeof(int)));
    }

    array[arrSize].numbers[*size] = number;
    array[arrSize].numItems++;
    (*size)++;
    return array;
}

int areEqual (int* array1, int* array2, int size1, int size2) {
    if (size1 != size2) {
        return 0;
    }

    for (int rotation = 0; rotation < size1; rotation++) {
        int equal = 1;
        for (int i = 0; i < size1; i++) {
            if (array1[i] != array2[(i+rotation)%size1]) {
                equal = 0;
                break;
            }
        }
        if (equal) {
            return 1;
        }
    }
    return 0;
}

int main () {
    Domino* array = NULL;
    int size = 0;
    int capacity = 0;
    char delim;
    char id;
    int num;

    while (scanf(" %c %c", &id, &delim) == 2 && delim == '[') {
        array = pushArray(array, &size, &capacity, id);
        int numSize = 0;
        int numCap = 0;
        while (scanf(" %d %c", &num, &delim) == 2 && (delim == ',' || delim == ']') && num > 0) {
            pushNumArray(array, &numSize, &numCap, num, size-1);
            if (delim == ']') {
                break;
            }
        }
    }

    if (!feof(stdin)) {
        for (int i = 0; i < size; i++) {
            free(array[i].numbers);
        }
        free(array);
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < array[i].numItems; j++) {
            printf("%d, ", array[i].numbers[j]);
        }
        printf("\n");
    }

    int duplicate = 1;
    for (int i = 0; i < size; i++) {
        int found = 0;
        if (!array[i].duplicated) {
            for (int j = i + 1; j < size; j++) {
                if (areEqual(array[i].numbers, array[j].numbers, array[i].numItems, array[j].numItems)) {
                    array[i].duplicated = duplicate;
                    array[j].duplicated = duplicate;
                    found = 1;
                }
            }
            if (found) {
                duplicate++;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i].duplicated == 0) {
            count++;
        }
    }

    printf("Unique: %d\n", count + duplicate - 1);

    for (int i = 1; i < duplicate; i++) {
        int start = 1;
        for (int j = 0; j < size; j++) {
            if (array[j].duplicated == i) {
                if (start) {
                    printf("%c", array[j].id);
                    start = 0;
                }
                else {
                    printf(" = %c", array[j].id);
                }
            }
        }
        printf("\n");
    }

    // for (int i = 0; i < size; i++) {
    //     printf("%d\n", array[i].duplicated);
    // }

    for (int i = 0; i < size; i++) {
            free(array[i].numbers);
        }
    free(array);
}