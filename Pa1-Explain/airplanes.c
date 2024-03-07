#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 200

typedef struct point {
    double x;
    double y;
    char name[MAX_SIZE];
} Point;

Point *pusharray(Point *array, size_t *size, size_t *capacity, double x, double y, char *name) {
    if (*size >= *capacity) {
            if (*capacity == 0)
                (*capacity)++;
            else  
                *capacity *=2;
            array = (Point *)realloc(array, (*capacity)*sizeof(*array));
        }
        array[*size].x = x;
        array[*size].y = y;
        strcpy(array[*size].name, name);
        (*size)++;
        return array;
}

double distance(double x, double y, double x1, double y1) {
    return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
}

int main () {
    double x, y;
    char name[MAX_SIZE];
    size_t size= 0;
    size_t capacity= 0;
    Point *points = NULL;
    double d;
    size_t index=0;
    int count=0;
    int in;

    printf("Plane coordinates:\n");

    while ((in=scanf(" %lf , %lf : %199s", &x, &y, name))!=EOF) {
    if (in != 3) {
        free(points);
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    points=pusharray(points, &size, &capacity, x, y, name);
          
    }
    if (size<2)
    {
        free(points);
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    double *Distances = (double *)malloc((size*(size-1)/2)*sizeof(double));
    
    for (size_t i=0; i<size; i++){
        for (size_t j=i+1; j<size; j++){
            d=distance(points[i].x, points[i].y, points[j].x, points[j].y);
            Distances[index]=d;
            index++;
        }
    }

    double min=Distances[0];

    for (size_t i=0; i<index; i++) {
        if (Distances[i]<min) {
            min = Distances[i];
        }
    }
    printf("Minimum airplane distance: %lf\n",min);


     for (size_t i=0; i<size; i++){
        for (size_t j=i+1; j<size; j++){
            d=distance(points[i].x, points[i].y, points[j].x, points[j].y);
            if(d-min<=__DBL_EPSILON__*d*min*1000){
                count++;
            }
        }
    }
    printf("Pairs found: %d\n", count);

    for (size_t i=0; i<size; i++){
        for (size_t j=i+1; j<size; j++){
            d=distance(points[i].x, points[i].y, points[j].x, points[j].y);
            if(d-min<=__DBL_EPSILON__*d*min*1000){
                printf("%s - %s\n", points[i].name, points[j].name);
            }
        }
    }

    free(Distances);
    free(points);
}