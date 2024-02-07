#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define     ITER_DEFAULT    200
#define     epsilon         0.001

int     checkLegal(int, int, int, int);

/*
    TO DO LIST
    create a points malloc array
    create a centroid malloc array
    for loop of points
    

    calculating distance of d dimension

*/

int main(int argc, char *argv[])
{
    // consts

    int k, n, d, iter; // consts
    double **points; // A list of vectors
    double **centroids; // A list of vectors
    int i; // for the for loops

    // Assisting methods
    void insertPointsFromStdin(double**);
    int checkLegal(int, int, int, int);


    // initializing and checking legality
    if (argc > 5 || argc < 4){
        printf("\nToo little/many arguments in command line!");
        return 0;
    }

    if (argc == 4){
        iter = ITER_DEFAULT;
    } else {
        iter = atoi(argv[4]);
    }
    k = atoi(argv[1]);
    n = atoi(argv[2]);
    d = atoi(argv[3]);
    if (checkLegal(k,n,d,iter) == 0){
        return 0;
    }
    printf("%d\n%d\n%d\n%d\nTESTING", k, n, d, iter);

    // Allocate memory for empty array of points
    // (represented as 'n' d-sized arrays)
    points = malloc(sizeof(double*) * n);
    for (i = 0; i < n ; i++) {
        points[i] = malloc(sizeof(double) * d);
    }
    
    // Allocate memory for empty array of centroids
    // (represented as 'k' d-sized arrays)
    centroids = malloc(sizeof(double*) * k);
    for (i = 0; i < k ; i++) {
        points[i] = malloc(sizeof(double) * d);
    }


    insertPointsFromStdin(points);

    // Insert first k points as centroids
    for (int i = 0 ; i < k ; i++){
        centroids[i] = points[i];
    }

    // FREE EVERYTHING BEFORE !
    return 0;
}

// Gets the points array and fills it according to input
void insertPointsFromStdin(double **points){
    char *line = NULL;
    size_t len = 0;
    int curr = 0;
    double *p = points[curr];

    while (getline(&line, &len, stdin) != -1){
        // ISSUES AND ALSO CANT RUN IT FROM WINDOWS TERMINAL
        printf("Line is\n%s", line);
    }
}

// Done
int checkLegal(int k, int n, int d, int iter){
    // Return 1 if legal, else 0
    // Function will print the error (if any)
    if (k <= 1 || k >= n){
        printf ("Invalid number of clusters!");
        return 0;
    }
    if (n <= 1){
        printf ("Invalid number of points!");
        return 0;
    }
    if (d < 1){
        printf ("Invalid dimension of point!");
        return 0;
    }
    if (iter <= 1 || iter >= 1000){
        printf ("Invalid maximum iteration!");
        return 0;
    }
    return 1;
}