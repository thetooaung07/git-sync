#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct wage {
    int wage;
    char region;
} Wage;

int intCompare (int* a, int* b) {
    return (*a < *b) - (*b < *a); 
}

char* removeNewLine (char* string) {
    size_t stringLen = strlen(string);
    if (stringLen > 0 && string[stringLen-1] == '\n') {
        string[stringLen-1] = '\0';
    }
    return string;
}

Wage* pushArray (Wage* array, int* size, int* capacity, int wage, int region) {
    if (*size >= *capacity) {
        if (*capacity == 0) {
            (*capacity)++;
        }
        else {
            (*capacity) *= 2;
        }
        array = (Wage*)realloc(array, (*capacity)*(sizeof(Wage)));
    }

    array[*size].wage = wage;
    array[*size].region = region;
    (*size)++;
    return array;
}

void handleQuery (char* string, Wage* wages, int size) {
    size_t stringLen = strlen(string);
    char usedChars[256] = {0};
    int count = 0;
    int* temp = (int*)malloc(size * sizeof(int));

    for(int i = 0; i < (int)stringLen; i++) {
        if (!usedChars[(int)(string[i])]){
            for (int j = 0; j < size; j++) {
                if (wages[j].region == string[i]) {
                    temp[count] = wages[j].wage;
                    count++;
                }
            }
            usedChars[(int)(string[i])] = 1;
        }
    }

    if (count == 0) {
        printf("= N/A\n");
        free(temp);
        return;
    }
    else {
        qsort(temp, count, sizeof(int), (int(*)(const void*, const void*))intCompare);
        printf("= %6f\n", count % 2 == 0 ? (temp[(count-1)/2] + temp[(count-1)/2+1])  / 2.0 : temp[count/2]);
        free(temp);
    }
}

int main () {
    char bracket, delim;
    int wage;
    char region;

    Wage* wages = NULL;
    int size = 0;
    int capacity = 0;
    int end = 0;

    char* input = NULL;
    size_t inputSize = 0;

    printf("Enter wages:\n");

    if (scanf(" %c", &bracket) == 1 && bracket == '{') {
        while (scanf (" %d %c %c", &wage, &region, &delim) == 3 && isupper(region) && wage > 0 
                        && (delim == ',' || delim == '}')) {
            wages = pushArray(wages, &size, &capacity, wage, region);
            if (delim == '}') {
                end = 1;
                break;
            }
        }

        if (!feof(stdin) && !end) {
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < size; i++) {
            printf("%d, %c\n", wages[i].wage, wages[i].region);
        }
    }
    else {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    getline(&input, &inputSize, stdin);

    while (getline(&input, &inputSize, stdin) != EOF) {
        input = removeNewLine(input);
        handleQuery(input, wages, size);
    }

    free(input);
    free(wages);

}