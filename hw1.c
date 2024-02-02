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

    int k, n, d, iter;
    double **points;
    double **centroids;

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

    // Creating the array of points(represented as d-arrays)

    points = malloc(sizeof(double) * n * d);
    centroids = malloc(sizeof(double) * k * d);

    for (int i = 0 ; i < k ; i++){
        if (i < k){
            centroids[i] = points[i];
            continue;
        }
        // MAKE THE FUNC checkClosestCentroid(points[i])
    }

    


    return 0;
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